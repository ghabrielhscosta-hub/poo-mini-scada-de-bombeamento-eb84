#include "ComandoAtuacao.h"

#include "Alarme.h"
#include "EstacaoBombeamento.h"

namespace {
void registrarResultado(EstacaoBombeamento& estacao,
                         const std::string& comando,
                         bool executado) {
    estacao.registrarComando(comando + ":" + (executado ? "executado" : "bloqueado"));

    if (!executado) {
        estacao.adicionarAlarme(Alarme(
            "comando_bloqueado",
            "Comando de atuacao bloqueado",
            "alerta"));
    }
}
}

std::string ComandoLigarBomba1::getNome() const {
    return "ligar_bomba_1";
}

bool ComandoLigarBomba1::executar(EstacaoBombeamento& estacao) {
    bool executado = !estacao.isModoManutencao() && estacao.getBomba1().ligar();
    registrarResultado(estacao, getNome(), executado);
    return executado;
}

std::string ComandoDesligarBomba1::getNome() const {
    return "desligar_bomba_1";
}

bool ComandoDesligarBomba1::executar(EstacaoBombeamento& estacao) {
    bool executado = estacao.getBomba1().desligar();
    registrarResultado(estacao, getNome(), executado);
    return executado;
}

std::string ComandoAlternarBomba::getNome() const {
    return "alternar_bomba";
}

bool ComandoAlternarBomba::executar(EstacaoBombeamento& estacao) {
    bool executado = !estacao.isModoManutencao() && estacao.alternarBombaPrincipal();
    registrarResultado(estacao, getNome(), executado);
    return executado;
}

std::string ComandoResetarAlarmes::getNome() const {
    return "resetar_alarme";
}

bool ComandoResetarAlarmes::executar(EstacaoBombeamento& estacao) {
    estacao.resetarAlarmes();
    registrarResultado(estacao, getNome(), true);
    return true;
}

std::string ComandoAtivarManutencao::getNome() const {
    return "ativar_manutencao";
}

bool ComandoAtivarManutencao::executar(EstacaoBombeamento& estacao) {
    estacao.ativarManutencao(true);
    registrarResultado(estacao, getNome(), true);
    return true;
}
