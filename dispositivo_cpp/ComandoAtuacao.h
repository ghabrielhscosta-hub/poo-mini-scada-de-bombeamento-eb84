#ifndef COMANDO_ATUACAO_H
#define COMANDO_ATUACAO_H

#include <string>

class EstacaoBombeamento;

class ComandoAtuacao {
public:
    virtual ~ComandoAtuacao() = default;

    virtual std::string getNome() const = 0;
    virtual bool executar(EstacaoBombeamento& estacao) = 0;
};

class ComandoLigarBomba1 : public ComandoAtuacao {
public:
    std::string getNome() const override;
    bool executar(EstacaoBombeamento& estacao) override;
};

class ComandoDesligarBomba1 : public ComandoAtuacao {
public:
    std::string getNome() const override;
    bool executar(EstacaoBombeamento& estacao) override;
};

class ComandoAlternarBomba : public ComandoAtuacao {
public:
    std::string getNome() const override;
    bool executar(EstacaoBombeamento& estacao) override;
};

class ComandoResetarAlarmes : public ComandoAtuacao {
public:
    std::string getNome() const override;
    bool executar(EstacaoBombeamento& estacao) override;
};

class ComandoAtivarManutencao : public ComandoAtuacao {
public:
    std::string getNome() const override;
    bool executar(EstacaoBombeamento& estacao) override;
};

#endif
