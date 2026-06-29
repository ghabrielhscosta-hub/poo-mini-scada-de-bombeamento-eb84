#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../dispositivo_cpp/Bomba.h"

const double LIMITE_NIVEL_BAIXO = 24.0;
const double LIMITE_NIVEL_ALTO = 84.0;
const double LIMITE_PRESSAO_ALTA = 6.4;
const int CICLOS_PRESSAO_PERSISTENTE = 3;

void verificar(bool condicao, const std::string& mensagem) {
    if (!condicao) {
        throw std::runtime_error(mensagem);
    }
}

bool regraNivelBaixo(double nivel) {
    return nivel < LIMITE_NIVEL_BAIXO;
}

bool regraNivelAlto(double nivel) {
    return nivel > LIMITE_NIVEL_ALTO;
}

bool regraPressaoAlta(double pressao) {
    return pressao > LIMITE_PRESSAO_ALTA;
}

bool regraPressaoAltaPersistente(const std::vector<double>& pressoes) {
    int ciclosConsecutivos = 0;

    for (double pressao : pressoes) {
        if (pressao > LIMITE_PRESSAO_ALTA) {
            ciclosConsecutivos++;
        } else {
            ciclosConsecutivos = 0;
        }

        if (ciclosConsecutivos >= CICLOS_PRESSAO_PERSISTENTE) {
            return true;
        }
    }

    return false;
}

void testarRegraNivelBaixo() {
    verificar(regraNivelBaixo(23.0), "Nivel abaixo de 24% deveria acionar regra de nivel baixo.");
    verificar(!regraNivelBaixo(24.0), "Nivel igual a 24% nao deveria acionar regra de nivel baixo.");
    verificar(!regraNivelBaixo(30.0), "Nivel acima de 24% nao deveria acionar regra de nivel baixo.");
}

void testarRegraNivelAlto() {
    verificar(regraNivelAlto(85.0), "Nivel acima de 84% deveria acionar regra de nivel alto.");
    verificar(!regraNivelAlto(84.0), "Nivel igual a 84% nao deveria acionar regra de nivel alto.");
    verificar(!regraNivelAlto(70.0), "Nivel abaixo de 84% nao deveria acionar regra de nivel alto.");
}

void testarRegraPressaoAlta() {
    verificar(regraPressaoAlta(6.5), "Pressao acima de 6.4 bar deveria gerar pressao alta.");
    verificar(!regraPressaoAlta(6.4), "Pressao igual a 6.4 bar nao deveria gerar pressao alta.");
    verificar(!regraPressaoAlta(5.8), "Pressao abaixo de 6.4 bar nao deveria gerar pressao alta.");
}

void testarRegraExtraPressaoPersistente() {
    std::vector<double> pressoesComAlarme = {6.1, 6.5, 6.7, 6.8};
    std::vector<double> pressoesSemAlarme = {6.5, 6.7, 6.1, 6.8};

    verificar(
        regraPressaoAltaPersistente(pressoesComAlarme),
        "Pressao acima de 6.4 bar por 3 ciclos consecutivos deveria gerar pressao_alta_persistente."
    );

    verificar(
        !regraPressaoAltaPersistente(pressoesSemAlarme),
        "Pressao alta sem 3 ciclos consecutivos nao deveria gerar pressao_alta_persistente."
    );
}

void testarEstadoDaBomba() {
    Bomba bomba("bomba_1");

    verificar(bomba.getEstado() == EstadoBomba::Desligada, "Bomba deveria iniciar desligada.");

    bomba.ligar();
    verificar(bomba.getEstado() == EstadoBomba::Ligada, "Bomba deveria ficar ligada apos ligar().");

    bomba.desligar();
    verificar(bomba.getEstado() == EstadoBomba::Desligada, "Bomba deveria ficar desligada apos desligar().");

    bomba.bloquear();
    verificar(bomba.getEstado() == EstadoBomba::Bloqueada, "Bomba deveria ficar bloqueada apos bloquear().");

    bomba.resetar();
    verificar(bomba.getEstado() == EstadoBomba::Desligada, "Bomba deveria voltar para desligada apos resetar().");
}

void testarComandoBloqueado() {
    Bomba bomba("bomba_1");

    bomba.bloquear();
    bomba.ligar();

    verificar(
        bomba.getEstado() == EstadoBomba::Bloqueada,
        "Bomba bloqueada nao deveria ligar."
    );
}

int main() {
    try {
        testarRegraNivelBaixo();
        testarRegraNivelAlto();
        testarRegraPressaoAlta();
        testarRegraExtraPressaoPersistente();
        testarEstadoDaBomba();
        testarComandoBloqueado();

        std::cout << "Todos os testes do dispositivo C++ passaram." << std::endl;
        return 0;
    } catch (const std::exception& erro) {
        std::cerr << "Teste falhou: " << erro.what() << std::endl;
        return 1;
    }
}
