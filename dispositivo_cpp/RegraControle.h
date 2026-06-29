#ifndef REGRA_CONTROLE_H
#define REGRA_CONTROLE_H

#include <string>

class EstacaoBombeamento;

class RegraControle {
public:
    virtual ~RegraControle() = default;

    virtual std::string getNome() const = 0;
    virtual void executar(EstacaoBombeamento& estacao) = 0;
};

class RegraNivelBaixo : public RegraControle {
public:
    std::string getNome() const override;
    void executar(EstacaoBombeamento& estacao) override;
};

class RegraNivelAlto : public RegraControle {
public:
    std::string getNome() const override;
    void executar(EstacaoBombeamento& estacao) override;
};

class RegraPressaoAlta : public RegraControle {
public:
    std::string getNome() const override;
    void executar(EstacaoBombeamento& estacao) override;
};

class RegraPressaoAltaPersistente : public RegraControle {
public:
    std::string getNome() const override;
    void executar(EstacaoBombeamento& estacao) override;
};

#endif
