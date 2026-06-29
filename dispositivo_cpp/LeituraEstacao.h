#ifndef LEITURA_ESTACAO_H
#define LEITURA_ESTACAO_H

#include <string>

struct LeituraEstacao {
    double nivelReservatorio = 0.0;
    double pressaoLinha = 0.0;
    double vazao = 0.0;
    double temperatura = 0.0;
    std::string qualidade = "valida";
};

#endif
