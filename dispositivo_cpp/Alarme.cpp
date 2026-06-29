#include "Alarme.h"

Alarme::Alarme(const std::string& codigo,
               const std::string& descricao,
               const std::string& severidade)
    : codigo(codigo), descricao(descricao), severidade(severidade) {}

const std::string& Alarme::getCodigo() const {
    return codigo;
}

const std::string& Alarme::getDescricao() const {
    return descricao;
}

const std::string& Alarme::getSeveridade() const {
    return severidade;
}
