#include "Bomba.h"

Bomba::Bomba(const std::string& tagInicial) : tag(tagInicial) {}

bool Bomba::ligar() {
    if (estado == EstadoBomba::Bloqueada || estado == EstadoBomba::Falha) {
        return false;
    }

    estado = EstadoBomba::Ligada;
    return true;
}

bool Bomba::desligar() {
    if (estado == EstadoBomba::Falha) {
        return false;
    }

    estado = EstadoBomba::Desligada;
    return true;
}

bool Bomba::bloquear() {
    if (estado == EstadoBomba::Falha) {
        return false;
    }

    estado = EstadoBomba::Bloqueada;
    return true;
}

void Bomba::falhar() {
    estado = EstadoBomba::Falha;
}

void Bomba::resetar() {
    estado = EstadoBomba::Desligada;
}

const std::string& Bomba::getTag() const {
    return tag;
}

EstadoBomba Bomba::getEstado() const {
    return estado;
}

std::string Bomba::estadoComoTexto() const {
    switch (estado) {
        case EstadoBomba::Ligada:
            return "ligada";
        case EstadoBomba::Bloqueada:
            return "bloqueada";
        case EstadoBomba::Falha:
            return "falha";
        case EstadoBomba::Desligada:
        default:
            return "desligada";
    }
}
