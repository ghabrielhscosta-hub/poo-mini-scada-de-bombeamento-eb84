#include "RegraControle.h"

#include "Alarme.h"
#include "EstacaoBombeamento.h"
#include "ParametrosOperacionais.h"

std::string RegraNivelBaixo::getNome() const {
    return "regra_nivel_baixo";
}

void RegraNivelBaixo::executar(EstacaoBombeamento& estacao) {
    if (estacao.getNivelReservatorio() < ParametrosOperacionais::NIVEL_BAIXO) {
        estacao.getBomba1().ligar();
        estacao.adicionarAlarme(Alarme(
            "nivel_baixo",
            "Nivel abaixo do limite operacional",
            "alerta"));
        estacao.registrarComando("ligar_bomba_1");
        estacao.registrarEventoRegra(getNome());
    }
}

std::string RegraNivelAlto::getNome() const {
    return "regra_nivel_alto";
}

void RegraNivelAlto::executar(EstacaoBombeamento& estacao) {
    if (estacao.getNivelReservatorio() > ParametrosOperacionais::NIVEL_ALTO) {
        estacao.getBomba1().desligar();
        estacao.getBomba2().desligar();
        estacao.adicionarAlarme(Alarme(
            "nivel_alto",
            "Nivel acima do limite operacional",
            "alerta"));
        estacao.registrarComando("desligar_bombas");
        estacao.registrarEventoRegra(getNome());
    }
}

std::string RegraPressaoAlta::getNome() const {
    return "regra_pressao_alta";
}

void RegraPressaoAlta::executar(EstacaoBombeamento& estacao) {
    if (estacao.getPressaoLinha() > ParametrosOperacionais::PRESSAO_ALTA) {
        estacao.getBomba1().desligar();
        estacao.adicionarAlarme(Alarme(
            "pressao_alta",
            "Pressao acima do limite operacional",
            "alarme"));
        estacao.registrarComando("desligar_bomba_1");
        estacao.registrarEventoRegra(getNome());
    }
}

std::string RegraPressaoAltaPersistente::getNome() const {
    return "regra_pressao_alta_persistente";
}

void RegraPressaoAltaPersistente::executar(EstacaoBombeamento& estacao) {
    if (estacao.getPressaoLinha() > ParametrosOperacionais::PRESSAO_ALTA) {
        estacao.incrementarCicloPressaoAlta();
    } else {
        estacao.resetarCiclosPressaoAlta();
        return;
    }

    if (estacao.getCiclosPressaoAlta() >= ParametrosOperacionais::CICLOS_PRESSAO_ALTA_PERSISTENTE) {
        estacao.ativarPressaoAltaPersistente();
        estacao.adicionarAlarme(Alarme(
            "pressao_alta_persistente",
            "Pressao alta persistente por tres ciclos",
            "alarme"));
        estacao.registrarEventoRegra(getNome());
    }
}
