#ifndef BOMBA_H
#define BOMBA_H

#include <string>

enum class EstadoBomba {
    Desligada,
    Ligada,
    Bloqueada,
    Falha
};

class Bomba {
private:
    std::string tag;
    EstadoBomba estado = EstadoBomba::Desligada;

    std::string estadoComoTexto() const;

public:
    Bomba(const std::string& tagInicial);

    void ligar();
    void desligar();
    void bloquear();
    void falhar();
    void resetar();

    const std::string& getTag() const;
    EstadoBomba getEstado() const;

    std::string gerarJsonEstado() const;
};