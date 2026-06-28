#include <string>
#include <vector>
#include <iostream>

enum class EstadoBomba {
    Desligada,
    Ligada,
    Bloqueada,
    Falha
};

class Bomba {
protected:
    string tag;
    EstadoBomba estado = EstadoBomba::Desligada;

public:
    Bomba(string tagInicial) : tag(tagInicial) {}

    void ligar() {
        estado = EstadoBomba::Ligada;
    }

    void desligar() {
        estado = EstadoBomba::Desligada;
    }

    void bloquear() {
        estado = EstadoBomba::Bloqueada;
    }

    void falhar() {
        estado = EstadoBomba::Falha;
    }

    void resetar() {
        estado = EstadoBomba::Desligada;
    }

    const string& getTag() const {
        return tag;
    }

    EstadoBomba getEstado() const {
        return estado;
    }
};