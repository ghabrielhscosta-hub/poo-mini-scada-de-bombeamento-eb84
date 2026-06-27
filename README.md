# poo-mini-scada-de-bombeamento-eb84
Projeto final de POO: Mini-SCADA para simulação e supervisão de uma estação de bombeamento inteligente.
## Assinatura operacional da dupla

| Item | Valor |
|---|---|
| ID_DUPLA | 84 |
| Identificador da estação | EB-84 |
| Nível baixo | 24% |
| Nível alto | 84% |
| Pressão alta | 6.4 bar |
| Falha simulada | Sensor de nível travado por 10 ciclos |
| Regra extra | (Nulo) |

## Divisão de responsabilidades

| Integrante | GitHub | Responsabilidade principal |
|---|---|---|
| Integrante A | @Kavanell | Dispositivo C++, sensores, bombas, regras, comandos e testes C++ |
| Integrante B | @ghabrielhscosta-hub | Supervisor Python/Streamlit, JSON, histórico CSV e testes Python |
| Ambos | @Kavanell e @ghabrielhscosta-hub | Contrato JSON, README, AI_LOG, integração e defesa |
