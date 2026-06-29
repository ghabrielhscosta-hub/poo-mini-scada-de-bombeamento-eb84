#include "Bomba.h"

Bomba::Bomba(const std::string& tagInicial) : tag(tagInicial) {}

void Bomba::ligar() {
    estado = EstadoBomba::Ligada;
}

void Bomba::desligar() {
    estado = EstadoBomba::Desligada;
}

void Bomba::bloquear() {
    estado = EstadoBomba::Bloqueada;
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
        case EstadoBomba::Desligada:
            return "desligada";
        case EstadoBomba::Ligada:
            return "ligada";
        case EstadoBomba::Bloqueada:
            return "bloqueada";
        case EstadoBomba::Falha:
            return "falha";
        default:
            return "desconhecido";
    }
}

std::string Bomba::gerarJsonEstado() const {
    int valorEstado = 0;

    if (estado == EstadoBomba::Ligada) {
        valorEstado = 1;
    }

    return "{"
           "\"estacao\":\"EB-84\","
           "\"tipo\":\"bomba\","
           "\"tag\":\"" + tag + "\","
           "\"valor\":" + std::to_string(valorEstado) + ","
           "\"unidade\":\"estado\","
           "\"status\":\"normal\","
           "\"acao\":\"" + estadoComoTexto() + "\""
           "}";
}