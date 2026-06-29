#include "EstacaoBombeamento.h"

#include "RegraControle.h"

#include <algorithm>

EstacaoBombeamento::EstacaoBombeamento()
    : bomba1("bomba_1"), bomba2("bomba_2") {}

void EstacaoBombeamento::atualizarLeituras(double nivel,
                                           double pressao,
                                           double vazao,
                                           double temperatura) {
    if (!sensorNivelTravado) {
        leituraAtual.nivelReservatorio = nivel;
    }

    leituraAtual.pressaoLinha = pressao;
    leituraAtual.vazao = vazao;
    leituraAtual.temperatura = temperatura;
    leituraAtual.qualidade = sensorNivelTravado ? "travada" : "valida";
}

const LeituraEstacao& EstacaoBombeamento::getLeituraAtual() const {
    return leituraAtual;
}

double EstacaoBombeamento::getNivelReservatorio() const {
    return leituraAtual.nivelReservatorio;
}

double EstacaoBombeamento::getPressaoLinha() const {
    return leituraAtual.pressaoLinha;
}

Bomba& EstacaoBombeamento::getBomba1() {
    return bomba1;
}

Bomba& EstacaoBombeamento::getBomba2() {
    return bomba2;
}

const Bomba& EstacaoBombeamento::getBomba1() const {
    return bomba1;
}

const Bomba& EstacaoBombeamento::getBomba2() const {
    return bomba2;
}

void EstacaoBombeamento::adicionarAlarme(const Alarme& alarme) {
    auto existente = std::find_if(alarmesAtivos.begin(), alarmesAtivos.end(),
        [&alarme](const Alarme& item) {
            return item.getCodigo() == alarme.getCodigo();
        });

    if (existente == alarmesAtivos.end()) {
        alarmesAtivos.push_back(alarme);
    }
}

const std::vector<Alarme>& EstacaoBombeamento::getAlarmesAtivos() const {
    return alarmesAtivos;
}

void EstacaoBombeamento::resetarAlarmes() {
    alarmesAtivos.clear();
    pressaoAltaPersistente = false;
    resetarCiclosPressaoAlta();
}

void EstacaoBombeamento::registrarComando(const std::string& comando) {
    comandosRegistrados.push_back(comando);
}

const std::vector<std::string>& EstacaoBombeamento::getComandosRegistrados() const {
    return comandosRegistrados;
}

void EstacaoBombeamento::registrarEventoRegra(const std::string& evento) {
    eventosDasRegras.push_back(evento);
}

const std::vector<std::string>& EstacaoBombeamento::getEventosDasRegras() const {
    return eventosDasRegras;
}

void EstacaoBombeamento::limparEventosDasRegras() {
    eventosDasRegras.clear();
}

void EstacaoBombeamento::simularFalhaSensorNivelTravado() {
    sensorNivelTravado = true;
    leituraAtual.qualidade = "travada";
    adicionarAlarme(Alarme(
        "sensor_nivel_travado",
        "Sensor de nivel travado",
        "falha"));
}

bool EstacaoBombeamento::isSensorNivelTravado() const {
    return sensorNivelTravado;
}

bool EstacaoBombeamento::alternarBombaPrincipal() {
    if (bomba1.getEstado() == EstadoBomba::Falha || bomba2.getEstado() == EstadoBomba::Falha) {
        return false;
    }

    bool desligouBomba1 = bomba1.desligar();
    bool ligouBomba2 = bomba2.ligar();
    return desligouBomba1 && ligouBomba2;
}

void EstacaoBombeamento::ativarManutencao(bool ativo) {
    modoManutencao = ativo;
}

bool EstacaoBombeamento::isModoManutencao() const {
    return modoManutencao;
}

void EstacaoBombeamento::incrementarCicloPressaoAlta() {
    ciclosPressaoAlta++;
}

void EstacaoBombeamento::resetarCiclosPressaoAlta() {
    ciclosPressaoAlta = 0;
}

int EstacaoBombeamento::getCiclosPressaoAlta() const {
    return ciclosPressaoAlta;
}

void EstacaoBombeamento::ativarPressaoAltaPersistente() {
    pressaoAltaPersistente = true;
}

bool EstacaoBombeamento::isPressaoAltaPersistente() const {
    return pressaoAltaPersistente;
}

void EstacaoBombeamento::executarRegras(const std::vector<RegraControle*>& regras) {
    limparEventosDasRegras();

    for (RegraControle* regra : regras) {
        if (regra != nullptr) {
            regra->executar(*this);
        }
    }
}
