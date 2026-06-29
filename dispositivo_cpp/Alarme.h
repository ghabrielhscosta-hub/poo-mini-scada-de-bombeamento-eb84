#ifndef ALARME_H
#define ALARME_H

#include <string>

class Alarme {
private:
    std::string codigo;
    std::string descricao;
    std::string severidade;

public:
    Alarme(const std::string& codigo,
           const std::string& descricao,
           const std::string& severidade);

    const std::string& getCodigo() const;
    const std::string& getDescricao() const;
    const std::string& getSeveridade() const;
};

#endif
