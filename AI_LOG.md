# AI_LOG.md

# Registro de Uso de IA — Mini-SCADA EB-84

Este arquivo registra o uso de IA durante o desenvolvimento do projeto.
As sugestões aceitas foram revisadas pela dupla antes de serem aplicadas no repositório.

---

## Registro 01 — Organização inicial do projeto

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #01 — Planejamento inicial e assinatura da dupla
**Responsáveis:** @Kavanell, @ghabrielhscosta-hub

### Pedido feito à IA

Solicitamos ajuda para organizar o projeto, definir a divisão de responsabilidades da dupla, montar milestones, labels e issues no GitHub.

### Aceito

* Divisão principal entre dispositivo C++ e supervisor Python/Streamlit.
* Uso do identificador da estação `EB-84`.
* Organização do projeto em milestones.
* Separação das tarefas em issues pequenas.
* Criação de labels como `cpp`, `python`, `streamlit`, `json`, `testes`, `documentacao`, `integrante-a`, `integrante-b` e `ambos`.

### Rejeitado

* Criar issues separadas para ensaio da defesa.
* Criar muitas issues pequenas para tarefas que poderiam ficar agrupadas.
* Deixar apresentação e ensaio como partes centrais do GitHub.

### Justificativa técnica

A dupla decidiu manter o GitHub focado nas entregas técnicas do projeto: código C++, supervisor Python, contrato JSON, testes, README e AI_LOG. A preparação da defesa será tratada como tarefa de organização, sem necessidade de issue separada.

---

## Registro 02 — Contrato JSON

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #02 — Definir contrato JSON do sistema
**Responsáveis:** @Kavanell, @ghabrielhscosta-hub

### Pedido feito à IA

Solicitamos ajuda para revisar e corrigir o contrato JSON usado entre o dispositivo C++ e o supervisor Python.

### Aceito

* Uso de JSON Lines como formato de comunicação.
* Campos obrigatórios:

  * `tag`
  * `valor`
  * `unidade`
  * `timestamp`
  * `status`
* Campos opcionais:

  * `estacao`
  * `tipo`
  * `qualidade`
  * `alarmes`
  * `comandos`
  * `acao`
* Padronização da estação como `EB-84`.
* Exemplos de leitura normal, leitura com alarme e registro de comando.

### Rejeitado

* Manter exemplos com `EB-17`, pois a estação correta da dupla é `EB-84`.
* Usar `"valor": "ligar"` no exemplo de comando, porque o contrato define `valor` como número.
* Deixar JSON sem vírgula entre campos obrigatórios.

### Justificativa técnica

As alterações foram aceitas para manter consistência entre contrato, README, código C++ e supervisor Python. O campo `valor` foi mantido como numérico para facilitar validação no Python, e a ação textual do comando foi registrada no campo `acao`.

---

## Registro 03 — Tela inicial do supervisor Streamlit

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #08 — Criar supervisor Streamlit
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Solicitamos ajuda para criar a primeira versão do supervisor Streamlit, com foco apenas na tela inicial da Issue 08.

### Aceito

* Criação do arquivo `supervisor_python/app.py`.
* Uso de `streamlit` para montar a interface.
* Uso de `pandas` para organizar as tabelas.
* Exibição da estação `EB-84`.
* Exibição de resumo operacional.
* Exibição de tabela com leituras atuais.
* Exibição de tabela com estado das bombas.
* Uso de dados temporários para validar a interface inicial.

### Rejeitado

* Implementar gráficos já na Issue 08.
* Implementar leitura real de JSON Lines nesta etapa.
* Implementar histórico CSV nesta etapa.
* Implementar alarmes e comandos completos nesta etapa.
* Criar uma interface visual complexa antes da integração com os dados reais.

### Justificativa técnica

A decisão foi manter a Issue 08 limitada à criação da tela inicial do supervisor. Os dados temporários seguem os campos principais do contrato JSON, mas ainda não representam a leitura real do C++. A leitura do arquivo JSON Lines será feita na Issue 09, o histórico CSV na Issue 10 e os gráficos, alarmes e comandos completos na Issue 11.

---

## Registro 04 — Leitura e validação de JSON Lines

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #09 — Ler e validar JSON Lines no Python
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Solicitamos ajuda para fazer o supervisor Python ler e validar um arquivo JSON Lines.

### Aceito

* Criação dos arquivos `validator.py` e `json_reader.py`.
* Leitura de arquivo `.jsonl`.
* Validação dos campos obrigatórios: `tag`, `valor`, `unidade`, `timestamp` e `status`.
* Tratamento de arquivo ausente, JSON inválido e tipo de dado incorreto.
* Separação entre registros válidos e inválidos.
* Exibição dos erros no Streamlit.
* Criação de `data/leituras_exemplo.jsonl`.

### Rejeitado

* Fazer integração completa com o C++ nesta etapa.
* Implementar histórico CSV, gráficos, comandos e alarmes completos agora.
* Usar biblioteca externa de validação.

### Justificativa técnica

A Issue 09 ficou limitada à leitura e validação do JSON Lines. A validação foi separada em módulos próprios para organizar o código e permitir que o Streamlit trate erros sem quebrar a aplicação.

---

## Registro 05 — Histórico CSV com Repository

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #10 — Implementar histórico em CSV com Repository
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Solicitamos ajuda para implementar o histórico em CSV usando o padrão Repository.

### Aceito

* Criação da classe `HistoricoRepository`.
* Salvamento de leituras, alarmes e comandos no CSV.
* Consulta do histórico pelo Streamlit.
* Prevenção de registros duplicados.
* Separação entre interface e persistência.

### Rejeitado

* Acesso direto ao CSV dentro do `app.py`.
* Uso de SQLite nesta etapa.
* Alterações visuais desnecessárias no botão.

### Justificativa técnica

O Repository foi usado para organizar a persistência do histórico. O `app.py` cuida da interface, enquanto o `HistoricoRepository` salva e carrega os dados do CSV.
