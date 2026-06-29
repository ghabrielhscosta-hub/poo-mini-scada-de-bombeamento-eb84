#ifndef ESTACAO_BOMBEAMENTO_H
#define ESTACAO_BOMBEAMENTO_H

#include "Alarme.h"
#include "Bomba.h"
#include "LeituraEstacao.h"

#include <string>
#include <vector>

class RegraControle;

class EstacaoBombeamento {
private:
    LeituraEstacao leituraAtual;
    Bomba bomba1;
    Bomba bomba2;
    int ciclosPressaoAlta = 0;
    bool pressaoAltaPersistente = false;
    bool modoManutencao = false;
    bool sensorNivelTravado = false;
    std::vector<Alarme> alarmesAtivos;
    std::vector<std::string> comandosRegistrados;
    std::vector<std::string> eventosDasRegras;

public:
    EstacaoBombeamento();

    void atualizarLeituras(double nivel, double pressao, double vazao, double temperatura);
    const LeituraEstacao& getLeituraAtual() const;
    double getNivelReservatorio() const;
    double getPressaoLinha() const;
    Bomba& getBomba1();
    Bomba& getBomba2();
    const Bomba& getBomba1() const;
    const Bomba& getBomba2() const;
    void adicionarAlarme(const Alarme& alarme);
    const std::vector<Alarme>& getAlarmesAtivos() const;
    void resetarAlarmes();
    void registrarComando(const std::string& comando);
    const std::vector<std::string>& getComandosRegistrados() const;
    void registrarEventoRegra(const std::string& evento);
    const std::vector<std::string>& getEventosDasRegras() const;
    void limparEventosDasRegras();
    void simularFalhaSensorNivelTravado();
    bool isSensorNivelTravado() const;
    bool alternarBombaPrincipal();
    void ativarManutencao(bool ativo = true);
    bool isModoManutencao() const;
    void incrementarCicloPressaoAlta();
    void resetarCiclosPressaoAlta();
    int getCiclosPressaoAlta() const;
    void ativarPressaoAltaPersistente();
    bool isPressaoAltaPersistente() const;
    void executarRegras(const std::vector<RegraControle*>& regras);
};

#endif
