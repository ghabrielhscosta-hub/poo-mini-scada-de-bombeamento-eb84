# AI_LOG — Mini-SCADA EB-84

Este arquivo registra o uso de IA no desenvolvimento do projeto Mini-SCADA da Estação de Bombeamento `EB-84`.

---

## Registro 01 — Organização inicial do projeto

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #01 — Planejamento inicial e assinatura da dupla
**Responsável principal:** dupla

### Pedido feito à IA

Foi solicitado apoio para organizar o projeto Mini-SCADA, definir a divisão de responsabilidades, issues, milestones, labels e estrutura inicial do repositório.

### Aceito

* Definição do tema da estação `EB-84`.
* Organização das issues do projeto.
* Divisão de responsabilidades entre C++ e Python.
* Definição inicial das pastas do repositório.
* Uso de branches por issue.

### Rejeitado

* Criar issues excessivas ou fora do escopo.
* Implementar funcionalidades antes da organização inicial.
* Fechar issues sem evidência de código, documentação ou revisão.

### Justificativa técnica

A organização inicial ajudou a separar as responsabilidades da dupla e a manter o desenvolvimento controlado por issues, commits e pull requests.

---

## Registro 02 — Contrato JSON

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #02 — Definir contrato JSON
**Responsável principal:** dupla

### Pedido feito à IA

Foi solicitado apoio para definir o contrato JSON usado na comunicação entre o dispositivo C++ e o supervisor Python.

### Aceito

* Uso do formato JSON Lines.
* Definição dos campos obrigatórios: `tag`, `valor`, `unidade`, `timestamp` e `status`.
* Definição de campos opcionais: `estacao`, `tipo`, `qualidade`, `acao`, `alarmes` e `comandos`.
* Exemplos de leitura normal, leitura com alarme e estado de bomba.
* Uso do identificador `EB-84`.
* Inclusão da regra extra `pressao_alta_persistente`.

### Rejeitado

* Usar banco de dados nesta etapa.
* Criar um formato diferente para cada tipo de evento.
* Usar exemplos com `EB-17`, pois a estação da dupla é `EB-84`.

### Justificativa técnica

O contrato JSON padroniza a comunicação entre C++ e Python e permite que o supervisor leia os eventos gerados pelo dispositivo sem depender de detalhes internos da implementação em C++.

---

## Registro 03 — README inicial

**Data:** 2026-06-27
**Ferramenta:** ChatGPT
**Issue relacionada:** #15 — Atualizar README e AI_LOG
**Responsável principal:** dupla

### Pedido feito à IA

Foi solicitado apoio para montar a estrutura do README do projeto.

### Aceito

* Descrição do projeto.
* Arquitetura em duas camadas.
* Assinatura operacional da dupla.
* Divisão de responsabilidades.
* Explicação do contrato JSON.
* Explicação dos padrões de projeto.
* Instruções iniciais de execução.

### Rejeitado

* README genérico sem mencionar a estação `EB-84`.
* README sem assinatura operacional.
* Documentação de padrões de projeto que ainda não estivessem ligados ao código.

### Justificativa técnica

O README precisa registrar as decisões principais do projeto e servir como guia para execução, avaliação e defesa técnica.

---

## Registro 04 — Padrões de projeto

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #05 e #10
**Responsável principal:** dupla

### Pedido feito à IA

Foi solicitado apoio para escolher e justificar dois padrões de projeto.

### Aceito

* Uso do padrão **Strategy** nas regras de controle do dispositivo C++.
* Uso do padrão **Repository** na persistência do histórico CSV do supervisor Python.
* Atualização da Issue 05 para deixar o Strategy restrito às regras de controle.
* Atualização da Issue 10 para incluir o Repository no histórico CSV.

### Rejeitado

* Usar apenas um padrão de projeto.
* Usar padrões mais complexos sem necessidade, como State ou Observer, nesta fase.
* Declarar padrões que não aparecem de forma clara no código.

### Justificativa técnica

O Strategy separa as regras de controle da classe principal da estação. O Repository separa a persistência CSV da interface Streamlit. Assim, os dois padrões resolvem problemas reais do projeto e podem ser explicados na defesa.

---

## Registro 05 — Bombas e atuadores

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #04 — Implementar bombas e atuadores
**Responsável principal:** @Kavanell

### Pedido feito à IA

Foi solicitado apoio para criar a classe de bomba em C++ sem avançar para comandos, alarmes ou geração completa de JSON Lines.

### Aceito

* Criação da classe `Bomba`.
* Criação do enum `EstadoBomba`.
* Estados: `Desligada`, `Ligada`, `Bloqueada` e `Falha`.
* Métodos para ligar, desligar, bloquear, falhar e resetar.
* Método para gerar uma representação JSON do estado da bomba.
* Separação em `Bomba.h` e `Bomba.cpp`.

### Rejeitado

* Implementar comandos completos nesta issue.
* Implementar alarmes nesta issue.
* Salvar arquivo `.jsonl` nesta issue.
* Misturar Issue 04 com Issue 06 ou Issue 07.

### Justificativa técnica

A Issue 04 deveria focar apenas na modelagem das bombas e atuadores. A geração completa de comandos, alarmes e JSON Lines pertence a issues posteriores.

---

## Registro 06 — Testes do dispositivo C++

**Data:** 2026-06-29
**Ferramenta:** ChatGPT
**Issue relacionada:** #12 — Criar testes do dispositivo C++
**Responsável principal:** @Kavanell

### Pedido feito à IA

Foi solicitado apoio para criar testes do dispositivo C++ cobrindo as regras principais e os parâmetros da dupla.

### Aceito

* Criação do arquivo `tests/test_dispositivo_cpp.cpp`.
* Teste da regra de nível baixo com limite de 24%.
* Teste da regra de nível alto com limite de 84%.
* Teste da regra de pressão alta com limite de 6.4 bar.
* Teste da regra extra de pressão alta persistente por 3 ciclos consecutivos.
* Teste dos estados da bomba.
* Teste de comando bloqueado.
* Instruções de compilação e execução dos testes no README.

### Rejeitado

* Usar framework externo de testes nesta etapa.
* Criar testes dependentes do Streamlit.
* Misturar testes C++ com testes Python no mesmo arquivo.
* Avançar a lógica de comandos além do necessário para a Issue 12.

### Justificativa técnica

Os testes C++ verificam regras importantes do dispositivo e usam os parâmetros específicos da dupla `EB-84`. Isso ajuda a demonstrar funcionamento, rastreabilidade e domínio técnico durante a defesa.

---

## Registro 07 — Supervisor Streamlit

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #08 — Criar supervisor Streamlit
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Foi solicitado apoio para criar a tela inicial do supervisor Python usando Streamlit.

### Aceito

* Criação do arquivo `supervisor_python/app.py`.
* Exibição do título do Mini-SCADA.
* Identificação da estação `EB-84`.
* Tabela de leituras atuais.
* Tabela de estado das bombas.
* Uso de `streamlit` e `pandas`.

### Rejeitado

* Criar gráficos nesta etapa.
* Implementar histórico CSV nesta etapa.
* Implementar comandos reais no Streamlit nesta etapa.

### Justificativa técnica

A Issue 08 ficou limitada à criação da interface inicial do supervisor, mantendo o desenvolvimento incremental.

---

## Registro 08 — Leitura e validação JSON Lines

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #09 — Ler e validar JSON Lines no Python
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Foi solicitado apoio para fazer o supervisor Python ler e validar um arquivo JSON Lines.

### Aceito

* Criação do módulo `validator.py`.
* Criação do módulo `json_reader.py`.
* Validação dos campos obrigatórios do contrato JSON.
* Tratamento de arquivo ausente.
* Tratamento de JSON inválido.
* Tratamento de tipo de dado incorreto.
* Separação entre registros válidos e inválidos.
* Exibição de erros compreensíveis no Streamlit.

### Rejeitado

* Fazer integração completa com o C++ nesta etapa.
* Implementar histórico CSV nesta etapa.
* Usar biblioteca externa de validação.

### Justificativa técnica

A validação foi separada em módulos próprios para organizar o código e permitir que o Streamlit trate erros sem quebrar a aplicação.

---

## Registro 09 — Histórico CSV com Repository

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #10 — Implementar histórico em CSV com Repository
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Foi solicitado apoio para implementar o histórico em CSV usando o padrão Repository.

### Aceito

* Criação do `HistoricoRepository`.
* Separação da persistência CSV da interface Streamlit.
* Salvamento de leituras.
* Salvamento de alarmes.
* Salvamento de comandos.
* Consulta do histórico no Streamlit.
* Prevenção simples contra registros duplicados.

### Rejeitado

* Fazer o `app.py` acessar o CSV diretamente.
* Usar SQLite nesta etapa.
* Versionar o arquivo `data/historico.csv`.

### Justificativa técnica

O Repository foi usado para isolar a persistência do histórico e deixar o Streamlit responsável apenas pela interface. O CSV foi escolhido por ser simples e suficiente para o escopo do projeto.

---

## Registro 10 — Gráficos, alarmes e comandos no Streamlit

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #11 — Criar gráficos, alarmes e comandos no Streamlit
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Foi solicitado apoio para complementar o supervisor Streamlit com gráficos históricos, visualização de alarmes, comandos e destaque da regra extra da dupla.

### Aceito

* Gráfico histórico de nível do reservatório.
* Gráfico histórico de pressão da linha.
* Exibição de alarmes lidos do JSON Lines.
* Exibição de comandos lidos do JSON Lines.
* Destaque para a falha simulada do sensor de nível travado.
* Inclusão do alarme `pressao_alta_persistente`.

### Rejeitado

* Implementar a contagem real dos ciclos no Streamlit.
* Mudar todo o visual da interface.
* Colocar a regra de controle principal no Python.

### Justificativa técnica

A lógica da regra extra pertence ao dispositivo C++. O Streamlit apenas exibe o resultado recebido pelo JSON Lines, mantendo a separação entre dispositivo e supervisor.

---

## Registro 11 — Testes do supervisor Python

**Data:** 2026-06-28
**Ferramenta:** ChatGPT
**Issue relacionada:** #13 — Criar testes do supervisor Python
**Responsável principal:** @ghabrielhscosta-hub

### Pedido feito à IA

Foi solicitado apoio para criar testes automatizados para o supervisor Python.

### Aceito

* Criação de testes com `pytest`.
* Teste de JSON válido.
* Teste de campo obrigatório ausente.
* Teste de tipo inválido.
* Teste de arquivo JSON Lines inexistente.
* Teste de linha JSON corrompida.
* Ajuste do caminho de importação dos módulos da pasta `supervisor_python`.

### Rejeitado

* Testar componentes visuais do Streamlit diretamente.
* Criar testes complexos de interface.
* Usar bibliotecas adicionais além do `pytest`.

### Justificativa técnica

Os testes foram focados na lógica do supervisor Python, principalmente na validação e leitura do JSON Lines. Isso garante que entradas inválidas sejam tratadas sem quebrar a aplicação.

---

## Registro 12 — Atualização final de documentação

**Data:** 2026-06-29
**Ferramenta:** ChatGPT
**Issue relacionada:** #15 — Atualizar README e AI_LOG
**Responsável principal:** dupla

### Pedido feito à IA

Foi solicitado apoio para atualizar o README com as informações do projeto e consolidar o AI_LOG.

### Aceito

* Atualização do README com arquitetura, assinatura operacional, sensores, bombas, regras, comandos, alarmes, padrões, contrato JSON, execução e testes.
* Inclusão do Strategy e Repository como padrões usados.
* Inclusão da regra extra `pressao_alta_persistente`.
* Inclusão da seção de testes do dispositivo C++.
* Consolidação do AI_LOG com registros das principais decisões e implementações.

### Rejeitado

* Deixar o README genérico.
* Omitir os parâmetros específicos da estação `EB-84`.
* Declarar funcionalidades que não fazem parte do projeto.
* Substituir o entendimento técnico da dupla por texto pronto sem revisão.

### Justificativa técnica

A documentação final precisa estar compatível com o código entregue, com as issues e com a defesa técnica. O README e o AI_LOG ajudam a demonstrar organização, autoria, rastreabilidade e entendimento das decisões tomadas no projeto.

---

## Registro 13 — Correção do fluxo principal e integração

**Data:** 2026-06-30  
**Ferramenta:** ChatGPT  
**Issue relacionada:** #14 — Testar integração C++ com Python  
**Responsável:** @Kavanell e @ghabrielhscosta-hub  

**Pedido:**  
Apoio para corrigir problemas encontrados na integração entre o dispositivo C++ e o supervisor Python/Streamlit.

**Aceito:**  
Foram aceitas correções na geração e leitura do arquivo `data/leituras_dispositivo.jsonl`, ajuste do caminho usado pelo supervisor, remoção de duplicações no `app.py`, correção dos gráficos históricos para usar dados do `historico.csv`, retirada de `sensor_nivel_travado` da lista de comandos, registro correto da falha como alarme, e prevenção de comandos duplicados no dispositivo C++.

**Rejeitado:**  
Foi rejeitada a ideia de tratar `sensor_nivel_travado` como comando, pois ele representa uma falha/alarme. Também foi evitado versionar arquivos gerados automaticamente, como executáveis, `historico.csv` e pastas `__pycache__`.

**Justificativa:**  
As alterações melhoraram a coerência entre o dispositivo C++ e o supervisor Python, mantendo o fluxo principal do projeto: dispositivo gera JSON Lines, supervisor lê o arquivo, exibe leituras, alarmes, comandos e salva histórico via Repository. A correção também deixou os dados mais adequados para apresentação e validação da integração.