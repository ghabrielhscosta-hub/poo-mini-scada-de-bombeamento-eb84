#include "ComandoAtuacao.h"
#include "EstacaoBombeamento.h"
#include "JsonWriter.h"
#include "RegraControle.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace {
std::string statusSensor(double nivel, double pressao) {
    if (nivel < 24.0 || nivel > 84.0 || pressao > 6.4) {
        return "alarme";
    }

    return "normal";
}

void escreverLeiturasDoCiclo(EstacaoBombeamento& estacao, JsonWriter& writer) {
    const LeituraEstacao& leitura = estacao.getLeituraAtual();
    const std::vector<Alarme>& alarmes = estacao.getAlarmesAtivos();
    const std::vector<std::string>& comandos = estacao.getComandosRegistrados();
    std::string status = statusSensor(leitura.nivelReservatorio, leitura.pressaoLinha);

    writer.escreverSensor("nivel_reservatorio", leitura.nivelReservatorio, "%", status, leitura.qualidade, alarmes, comandos);
    writer.escreverSensor("pressao_linha", leitura.pressaoLinha, "bar", status, "valida", alarmes, comandos);
    writer.escreverSensor("vazao", leitura.vazao, "L/s", "normal", "valida", alarmes, comandos);
    writer.escreverSensor("temperatura", leitura.temperatura, u8"\u00B0C", "normal", "valida", alarmes, comandos);
    writer.escreverBomba(estacao.getBomba1(), alarmes, comandos);
    writer.escreverBomba(estacao.getBomba2(), alarmes, comandos);
}

void imprimirResumo(const EstacaoBombeamento& estacao) {
    std::cout << "Alarmes ativos:" << std::endl;
    for (const Alarme& alarme : estacao.getAlarmesAtivos()) {
        std::cout << "- " << alarme.getCodigo() << " (" << alarme.getSeveridade() << ")" << std::endl;
    }

    std::cout << "Comandos registrados:" << std::endl;
    for (const std::string& comando : estacao.getComandosRegistrados()) {
        std::cout << "- " << comando << std::endl;
    }
}
}

int main() {
    try {
        EstacaoBombeamento estacao;
        JsonWriter writer;

        RegraNivelBaixo regraNivelBaixo;
        RegraNivelAlto regraNivelAlto;
        RegraPressaoAlta regraPressaoAlta;
        RegraPressaoAltaPersistente regraPressaoAltaPersistente;

        std::vector<RegraControle*> regras = {
            &regraNivelBaixo,
            &regraNivelAlto,
            &regraPressaoAlta,
            &regraPressaoAltaPersistente
        };

        std::vector<std::unique_ptr<ComandoAtuacao>> comandos;
        comandos.push_back(std::make_unique<ComandoLigarBomba1>());
        comandos.push_back(std::make_unique<ComandoDesligarBomba1>());
        comandos.push_back(std::make_unique<ComandoAlternarBomba>());
        comandos.push_back(std::make_unique<ComandoResetarAlarmes>());
        comandos.push_back(std::make_unique<ComandoAtivarManutencao>());

        estacao.atualizarLeituras(20.0, 5.2, 18.0, 31.0);
        estacao.executarRegras(regras);
        comandos[0]->executar(estacao);
        escreverLeiturasDoCiclo(estacao, writer);

        estacao.atualizarLeituras(86.0, 6.8, 16.0, 32.0);
        estacao.executarRegras(regras);
        comandos[1]->executar(estacao);
        escreverLeiturasDoCiclo(estacao, writer);

        estacao.atualizarLeituras(70.0, 6.9, 15.0, 33.0);
        estacao.executarRegras(regras);
        comandos[2]->executar(estacao);
        escreverLeiturasDoCiclo(estacao, writer);

        estacao.simularFalhaSensorNivelTravado();
        estacao.atualizarLeituras(65.0, 7.0, 14.0, 34.0);
        estacao.executarRegras(regras);
        comandos[4]->executar(estacao);
        comandos[0]->executar(estacao);
        escreverLeiturasDoCiclo(estacao, writer);

        estacao.registrarComando("sensor_nivel_travado");
        writer.escreverEvento("alarme", "sensor_nivel_travado", 1, "evento", "executado", "travada", "", estacao.getAlarmesAtivos(), estacao.getComandosRegistrados());

        imprimirResumo(estacao);
        std::cout << "Arquivo gerado: data/leituras_dispositivo.jsonl" << std::endl;
    } catch (const std::exception& erro) {
        std::cerr << "Erro: " << erro.what() << std::endl;
        return 1;
    }

    return 0;
}
