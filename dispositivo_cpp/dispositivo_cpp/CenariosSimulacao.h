#ifndef CENARIOS_SIMULACAO_H
#define CENARIOS_SIMULACAO_H

#include <vector>

struct CicloSimulado {
    double nivel;
    double pressao;
    double vazao;
    double temperatura;
};

inline std::vector<CicloSimulado> criarCenariosSimulacaoEB84() {
    return {
        {20.0, 5.2, 18.0, 31.0},
        {86.0, 6.8, 16.0, 32.0},
        {70.0, 6.9, 15.0, 33.0},
        {65.0, 7.0, 14.0, 34.0}
    };
}

#endif