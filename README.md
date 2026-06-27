# POO Mini-SCADA de Bombeamento — EB-84

Projeto final de Programação Orientada a Objetos: Mini-SCADA para simulação e supervisão de uma estação de bombeamento inteligente.

O sistema é dividido em duas camadas:

```text
Dispositivo C++ → JSON Lines → Supervisor Python/Streamlit → Histórico CSV
```

O dispositivo em C++ simula sensores, bombas, comandos, regras de controle, alarmes e falhas.
O supervisor em Python/Streamlit lê os dados gerados, valida o contrato JSON, salva o histórico em CSV e apresenta as informações em uma interface web.

## Assinatura operacional da dupla

| Item                     | Valor                                 |
| ------------------------ | ------------------------------------- |
| ID_DUPLA                 | 84                                    |
| Identificador da estação | EB-84                                 |
| Nível baixo              | 24%                                   |
| Nível alto               | 84%                                   |
| Pressão alta             | 6.4 bar                               |
| Falha simulada           | Sensor de nível travado por 10 ciclos |
| Regra extra              | Pressão alta por vários ciclos        |

## Divisão de responsabilidades

| Integrante   | GitHub                           | Responsabilidade principal                                                         |
| ------------ | -------------------------------- | ---------------------------------------------------------------------------------- |
| Integrante A | @Kavanell                        | Dispositivo C++, sensores, bombas, regras, comandos, alarmes e testes C++          |
| Integrante B | @ghabrielhscosta-hub             | Supervisor Python/Streamlit, leitura JSON, histórico CSV, gráficos e testes Python |
| Ambos        | @Kavanell e @ghabrielhscosta-hub | Contrato JSON, README, AI_LOG, integração e defesa                                 |

## Estrutura inicial do projeto

```text
poo-mini-scada-de-bombeamento-eb84/
├── dispositivo_cpp/
├── supervisor_python/
├── data/
├── tests/
├── docs/
├── README.md
├── AI_LOG.md
└── contrato_json.md
```

## Contrato JSON

A comunicação entre o dispositivo C++ e o supervisor Python é feita por JSON Lines.

A documentação completa do contrato está no arquivo:

```text
contrato_json.md
```

Campos obrigatórios usados na comunicação:

| Campo       | Descrição                                     |
| ----------- | --------------------------------------------- |
| `tag`       | Identificador do sensor, bomba ou ativo       |
| `valor`     | Valor da leitura ou código numérico do evento |
| `unidade`   | Unidade da leitura                            |
| `timestamp` | Data e hora da leitura ou evento              |
| `status`    | Estado operacional                            |

## Padrão de projeto utilizado

O padrão de projeto usado no projeto será o **Strategy**, aplicado nas regras de controle do dispositivo em C++.

Cada regra de controle será separada da classe principal da estação, permitindo que as regras sejam executadas por uma interface comum.

Exemplos de regras:

* regra de nível baixo;
* regra de nível alto;
* regra de pressão alta;
* regra específica da dupla.

## Histórico

O histórico será salvo em arquivos CSV dentro da pasta `data/`.

O supervisor Python será responsável por registrar leituras, comandos e alarmes para consulta posterior.

## Uso de IA

O uso de IA será documentado no arquivo:

```text
AI_LOG.md
```

Esse arquivo registra os pedidos feitos à IA, o que foi aceito, o que foi rejeitado e a justificativa técnica da dupla.
