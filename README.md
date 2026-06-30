# POO Mini-SCADA de Bombeamento — EB-84

Projeto final de Programação Orientada a Objetos: Mini-SCADA para simulação e supervisão de uma estação de bombeamento inteligente.

O sistema simula uma estação de bombeamento usando duas camadas principais:

```text
Dispositivo C++ → JSON Lines → Supervisor Python/Streamlit → Histórico CSV
```

O dispositivo em C++ simula sensores, bombas, comandos, regras de controle, alarmes e falhas.
O supervisor em Python/Streamlit lê os dados gerados pelo dispositivo, valida o contrato JSON, salva histórico em CSV e apresenta as informações em uma interface web.

---

## Integrantes

| Integrante   | GitHub                           | Responsabilidade principal                                                         |
| ------------ | -------------------------------- | ---------------------------------------------------------------------------------- |
| Integrante A | @Kavanell                        | Dispositivo C++, sensores, bombas, regras, comandos, alarmes e testes C++          |
| Integrante B | @ghabrielhscosta-hub             | Supervisor Python/Streamlit, leitura JSON, histórico CSV, gráficos e testes Python |
| Ambos        | @Kavanell e @ghabrielhscosta-hub | Contrato JSON, README, AI_LOG, integração, revisão e defesa                        |

---

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

A regra extra da dupla é chamada de **pressão alta persistente**.

Ela ocorre quando a pressão da linha fica acima de **6.4 bar por 3 ciclos consecutivos**.
Quando isso acontece, o sistema pode gerar o alarme:

```text
pressao_alta_persistente
```

e também pode registrar o comando:

```text
desligar_bomba_1
```

Esses parâmetros devem aparecer no código, no contrato JSON, nos testes, no supervisor e na defesa do projeto.

---

## Objetivo do projeto

O objetivo do projeto é aplicar conceitos de Programação Orientada a Objetos em um sistema simulado de supervisão industrial.

O projeto contempla:

* simulação de sensores em C++;
* modelagem de bombas e atuadores;
* regras de controle da estação;
* comandos de atuação;
* alarmes operacionais;
* falha simulada específica da dupla;
* comunicação por JSON Lines;
* supervisor em Streamlit;
* histórico em CSV;
* testes do dispositivo e do supervisor;
* documentação e registro do uso de IA.

---

## Arquitetura do sistema

O projeto foi organizado em duas camadas.

### 1. Dispositivo C++

O dispositivo em C++ é responsável pela simulação da estação.

Ele contém:

* sensores;
* bombas;
* regras de controle;
* comandos;
* alarmes;
* falhas simuladas;
* geração de registros em JSON Lines.

### 2. Supervisor Python/Streamlit

O supervisor em Python/Streamlit é responsável pela visualização e persistência dos dados.

Ele contém:

* leitura do arquivo `.jsonl`;
* validação do contrato JSON;
* exibição de leituras atuais;
* exibição do estado das bombas;
* exibição de alarmes;
* exibição de comandos;
* gráficos históricos;
* histórico em CSV usando Repository.

---

## Estrutura do projeto

```text
poo-mini-scada-de-bombeamento-eb84/
├── dispositivo_cpp/
│   ├── Alarme.cpp
│   ├── Alarme.h
│   ├── Bomba.cpp
│   ├── Bomba.h
│   ├── bombas.h
│   ├── CenariosSimulacao.h
│   ├── ComandoAtuacao.cpp
│   ├── ComandoAtuacao.h
│   ├── estacao.cpp
│   ├── EstacaoBombeamento.cpp
│   ├── EstacaoBombeamento.h
│   ├── JsonWriter.cpp
│   ├── JsonWriter.h
│   ├── LeituraEstacao.h
│   ├── main.cpp
│   ├── ParametrosOperacionais.h
│   ├── RegraControle.cpp
│   ├── RegraControle.h
│   └── sensor.cpp
├── supervisor_python/
│   ├── app.py
│   ├── historico_repository.py
│   ├── json_reader.py
│   └── validator.py
├── data/
│   └── leituras_dispositivo.jsonl
├── tests/
│   ├── test_dispositivo_cpp.cpp
│   └── test_supervisor_python.py
├── docs/
│   └── contrato_json.md
├── README.md
├── AI_LOG.md
├── requirements.txt
└── .gitignore
```

A estrutura pode variar conforme a evolução dos arquivos `.h` e `.cpp`, mas a separação principal deve ser mantida:

* `dispositivo_cpp/` para o código C++;
* `supervisor_python/` para o supervisor Streamlit;
* `data/` para arquivos de exemplo e dados gerados;
* `tests/` para testes;
* `docs/` para documentação auxiliar.

---

## Requisitos atendidos

| Requisito                                | Implementação prevista                                                     |
| ---------------------------------------- | -------------------------------------------------------------------------- |
| Pelo menos 4 sensores                    | Nível, pressão, vazão e temperatura ou corrente                            |
| Pelo menos 2 bombas ou 1 bomba + atuador | Bombas `bomba_1` e `bomba_2`                                               |
| Pelo menos 4 regras de controle          | Nível baixo, nível alto, pressão alta e pressão alta persistente           |
| Pelo menos 4 comandos                    | Ligar bomba, desligar bomba, alternar bomba e resetar alarme ou manutenção |
| Pelo menos 3 alarmes                     | `nivel_baixo`, `nivel_alto`, `pressao_alta`, além de falhas                |
| Falha simulada                           | Sensor de nível travado por 10 ciclos                                      |
| Contrato JSON                            | Documentado em `contrato_json.md`                                          |
| Herança                                  | Classe base `Sensor` e sensores especializados                             |
| Polimorfismo                             | Coleção de sensores e regras tratadas por interface comum                  |
| Encapsulamento                           | Atributos protegidos/privados e métodos de acesso                          |
| 2 padrões de projeto                     | Strategy e Repository                                                      |
| Supervisor Streamlit                     | Interface em `supervisor_python/app.py`                                    |
| Histórico                                | CSV em `data/historico.csv`                                                |
| Testes                                   | Testes de JSON, leitura, validação e integração                            |

---

## Sensores simulados

| Sensor                            | Tag sugerida                            | Unidade     | Descrição                         |
| --------------------------------- | --------------------------------------- | ----------- | --------------------------------- |
| Sensor de nível                   | `nivel_reservatorio`                    | `%`         | Mede o nível do reservatório      |
| Sensor de pressão                 | `pressao_linha`                         | `bar`       | Mede a pressão da linha           |
| Sensor de vazão                   | `vazao_linha`                           | `L/s`       | Mede a vazão da estação           |
| Sensor de temperatura ou corrente | `temperatura_motor` ou `corrente_motor` | `°C` ou `A` | Mede condição auxiliar do sistema |

A classe base `Sensor` permite que os sensores especializados sejam tratados de forma polimórfica.

---

## Bombas e atuadores

O sistema modela bombas da estação de bombeamento.

Bombas previstas:

```text
bomba_1
bomba_2
```

Estados possíveis das bombas:

| Estado      | Significado              |
| ----------- | ------------------------ |
| `desligada` | Bomba parada             |
| `ligada`    | Bomba em funcionamento   |
| `bloqueada` | Bomba impedida de partir |
| `falha`     | Bomba em estado de falha |

A modelagem das bombas fica no dispositivo C++ e o estado delas é enviado ao supervisor por meio do JSON Lines.

---

## Regras de controle

As regras de controle avaliam as leituras da estação e podem gerar comandos ou alarmes.

Regras previstas:

| Regra                    | Condição                                           | Ação esperada                                                       |
| ------------------------ | -------------------------------------------------- | ------------------------------------------------------------------- |
| Nível baixo              | Nível abaixo de 24%                                | Ligar bomba ou gerar alarme                                         |
| Nível alto               | Nível acima de 84%                                 | Desligar bomba ou gerar alarme                                      |
| Pressão alta             | Pressão acima de 6.4 bar                           | Gerar alarme `pressao_alta`                                         |
| Pressão alta persistente | Pressão acima de 6.4 bar por 3 ciclos consecutivos | Gerar `pressao_alta_persistente` e possível comando de desligamento |

---

## Alarmes

Alarmes previstos no projeto:

| Alarme                     | Descrição                                               |
| -------------------------- | ------------------------------------------------------- |
| `nivel_baixo`              | Nível do reservatório abaixo do limite de 24%           |
| `nivel_alto`               | Nível do reservatório acima do limite de 84%            |
| `pressao_alta`             | Pressão da linha acima de 6.4 bar                       |
| `pressao_alta_persistente` | Pressão acima de 6.4 bar por 3 ciclos consecutivos      |
| `sensor_nivel_travado`     | Falha simulada do sensor de nível travado por 10 ciclos |

---

## Comandos

Comandos previstos no projeto:

| Comando             | Descrição                                 |
| ------------------- | ----------------------------------------- |
| `ligar_bomba_1`     | Liga a bomba 1                            |
| `desligar_bomba_1`  | Desliga a bomba 1                         |
| `alternar_bomba`    | Alterna a bomba principal                 |
| `resetar_alarme`    | Reseta alarmes ativos quando permitido    |
| `ativar_manutencao` | Ativa modo de manutenção, se implementado |

---

## Padrões de projeto utilizados

O projeto utiliza dois padrões de projeto principais:

* **Strategy**, aplicado nas regras de controle do dispositivo C++;
* **Repository**, aplicado na persistência do histórico CSV no supervisor Python.

---

### Strategy

O padrão **Strategy** é aplicado no dispositivo em C++, na parte das regras de controle da estação.

Cada regra de controle fica separada da classe principal da estação, permitindo que as regras sejam executadas por uma interface comum.

Exemplos de regras implementadas ou previstas:

* regra de nível baixo;
* regra de nível alto;
* regra de pressão alta;
* regra específica da dupla: pressão alta persistente.

Esse padrão evita concentrar todas as decisões dentro de um único método e facilita manutenção, testes e explicação na defesa.

### Onde aparece no código

O Strategy aparece na estrutura das regras de controle, por exemplo:

```text
RegraControle
├── RegraNivelBaixo
├── RegraNivelAlto
├── RegraPressaoAlta
└── RegraPressaoAltaPersistente
```

A estação executa as regras por meio de uma coleção, permitindo polimorfismo.

---

### Repository

O padrão **Repository** é aplicado no supervisor Python, na parte de persistência do histórico em CSV.

A classe ou módulo `HistoricoRepository` é responsável por salvar e carregar dados do histórico.
Com isso, o arquivo principal do Streamlit (`app.py`) não acessa o CSV diretamente.

Funções previstas no Repository:

* salvar leituras;
* salvar alarmes;
* salvar comandos;
* carregar histórico;
* evitar duplicação desnecessária de registros.

### Onde aparece no código

O Repository aparece no arquivo:

```text
supervisor_python/historico_repository.py
```

O Streamlit deve usar o Repository assim:

```text
app.py → HistoricoRepository → data/historico.csv
```

Essa separação melhora a organização do código e facilita testes.

---

## Contrato JSON

A comunicação entre o dispositivo C++ e o supervisor Python é feita por JSON Lines (`.jsonl`).

A documentação completa do contrato está no arquivo:

```text
contrato_json.md
```

Cada linha do arquivo representa uma leitura ou evento da estação.

### Campos obrigatórios

| Campo       | Tipo   | Descrição                                     |
| ----------- | ------ | --------------------------------------------- |
| `tag`       | texto  | Identificador do sensor, bomba ou ativo       |
| `valor`     | número | Valor da leitura ou código numérico do evento |
| `unidade`   | texto  | Unidade da leitura ou do estado               |
| `timestamp` | texto  | Data e hora da leitura ou evento              |
| `status`    | texto  | Estado operacional                            |

### Campos opcionais

| Campo       | Tipo  | Descrição                                        |
| ----------- | ----- | ------------------------------------------------ |
| `estacao`   | texto | Identificador da estação, neste projeto `EB-84`  |
| `tipo`      | texto | Tipo do registro, como `sensor` ou `bomba`       |
| `qualidade` | texto | Qualidade da leitura, como `valida` ou `travada` |
| `acao`      | texto | Ação relacionada ao evento                       |
| `alarmes`   | lista | Lista de alarmes ativos                          |
| `comandos`  | lista | Lista de comandos executados ou sugeridos        |

### Exemplo de leitura normal

```json
{
  "estacao": "EB-84",
  "tipo": "sensor",
  "tag": "nivel_reservatorio",
  "valor": 72.5,
  "unidade": "%",
  "timestamp": "2026-06-27T15:30:00",
  "status": "normal",
  "qualidade": "valida",
  "alarmes": [],
  "comandos": []
}
```

### Exemplo com alarme

```json
{
  "estacao": "EB-84",
  "tipo": "sensor",
  "tag": "pressao_linha",
  "valor": 6.8,
  "unidade": "bar",
  "timestamp": "2026-06-27T15:33:00",
  "status": "alarme",
  "qualidade": "valida",
  "alarmes": ["pressao_alta", "pressao_alta_persistente"],
  "comandos": ["desligar_bomba_1"]
}
```

### Exemplo de estado de bomba

```json
{
  "estacao": "EB-84",
  "tipo": "bomba",
  "tag": "bomba_1",
  "valor": 1,
  "unidade": "estado",
  "timestamp": "2026-06-27T15:33:00",
  "status": "normal",
  "acao": "ligada",
  "alarmes": [],
  "comandos": ["ligar_bomba_1"]
}
```

---

## Histórico CSV

O histórico é salvo em arquivo CSV dentro da pasta:

```text
data/
```

Arquivo gerado:

```text
data/historico.csv
```

O histórico registra:

* leituras dos sensores;
* alarmes;
* comandos.

O arquivo `data/historico.csv` é gerado durante a execução e não precisa ser versionado no GitHub.

O arquivo de exemplo `data/leituras_exemplo.jsonl` deve ser mantido no repositório, pois ajuda nos testes e na demonstração do supervisor antes da integração completa com o C++.

---

## Supervisor Streamlit

O supervisor é desenvolvido em Python com Streamlit.

Funcionalidades previstas:

* exibir resumo operacional da estação;
* exibir leituras atuais;
* exibir estado das bombas;
* exibir gráficos históricos de nível e pressão;
* exibir alarmes;
* exibir comandos;
* validar registros JSON;
* salvar e consultar histórico CSV.

Arquivos principais:

```text
supervisor_python/app.py
supervisor_python/json_reader.py
supervisor_python/validator.py
supervisor_python/historico_repository.py
```

Ordem sugerida da interface:

```text
Resumo operacional
Leituras atuais
Estado das bombas
Gráficos históricos
Alarmes
Comandos
Validação do arquivo JSON Lines
Histórico CSV
```

---

## Como executar o projeto no WSL/Ubuntu

Os comandos abaixo devem ser executados a partir da raiz do projeto.

### 1. Preparar o ambiente

Instale os pacotes necessários no WSL:

```bash
sudo apt update
sudo apt install python3-full python3-venv python3-pip g++ -y
```

Crie o ambiente virtual:

```bash
python3 -m venv ~/.venvs/scada-eb84
```

Ative o ambiente virtual:

```bash
source ~/.venvs/scada-eb84/bin/activate
```

Instale as dependências do supervisor:

```bash
python -m pip install --upgrade pip setuptools wheel
python -m pip install -r requirements.txt
```

No WSL/Ubuntu, o comando `python3` é usado para criar a venv. Depois da ativação, o comando `python` passa a usar o Python do ambiente virtual.


### 2. Compilar o dispositivo C++

Compile o dispositivo a partir da raiz do projeto:

```bash
g++ -std=c++17 dispositivo_cpp/*.cpp -o dispositivo_cpp/mini_scada
```


### 3. Executar o dispositivo C++

Execute o simulador do dispositivo:

```bash
./dispositivo_cpp/mini_scada
```

A execução gera o arquivo:

```text
data/leituras_dispositivo.jsonl
```

Esse arquivo contém as leituras, estados das bombas, alarmes e comandos gerados pelo dispositivo C++.

Para conferir o conteúdo (Se quiser):

```bash
head data/leituras_dispositivo.jsonl
```


### 4. Executar o supervisor Streamlit

Com o ambiente virtual ativado, execute:

```bash
python -m streamlit run supervisor_python/app.py
```

O supervisor lê o arquivo:

```text
data/leituras_dispositivo.jsonl
```

e salva o histórico em:

```text
data/historico.csv
```


## Fluxo principal do sistema

```text
Dispositivo C++ -> data/leituras_dispositivo.jsonl -> Supervisor Streamlit -> data/historico.csv
```


## Execução resumida

Depois que o ambiente já estiver preparado, execute:

```bash
source ~/.venvs/scada-eb84/bin/activate
g++ -std=c++17 dispositivo_cpp/*.cpp -o dispositivo_cpp/mini_scada
./dispositivo_cpp/mini_scada
python -m streamlit run supervisor_python/app.py
```

---

## Como executar os testes

### Testes Python

Os testes Python validam a leitura do arquivo JSON Lines e o contrato esperado pelo supervisor.

Os testes cobrem:

* JSON válido;
* JSON sem campo obrigatório;
* JSON com tipo inválido;
* arquivo inexistente;
* linha JSON corrompida;
* leitura e validação do contrato JSON.

Execute a partir da raiz do projeto, com o ambiente virtual ativado:

```bash
python -m pytest tests/
```

Resultado esperado:

```text
tests/test_supervisor_python.py ... passed
```

### Testes C++

O projeto possui testes simples para validar regras e comportamentos principais do dispositivo C++.

Os testes cobrem:

* regra de nível baixo;
* regra de nível alto;
* regra de pressão alta;
* regra extra da dupla: pressão alta persistente;
* estados básicos da bomba;
* bloqueio de comando inválido em bomba bloqueada;
* parâmetros operacionais da EB-84.

Para compilar os testes C++, execute a partir da raiz do projeto:

```bash
g++ -std=c++17 tests/test_dispositivo_cpp.cpp dispositivo_cpp/Bomba.cpp -o tests/test_dispositivo_cpp
```

Para executar:

```bash
./tests/test_dispositivo_cpp
```

Resultado esperado:

```text
Todos os testes do dispositivo C++ passaram.
```

---

## Issues do projeto

O projeto foi organizado em issues para facilitar a divisão de trabalho e a rastreabilidade.

| Nº | Issue                                           | Responsável                     |
| -- | ----------------------------------------------- | ------------------------------- |
| 01 | Planejamento inicial e assinatura da dupla      | @Kavanell, @ghabrielhscosta-hub |
| 02 | Definir contrato JSON                           | @Kavanell, @ghabrielhscosta-hub |
| 03 | Implementar sensores em C++                     | @Kavanell                       |
| 04 | Implementar bombas e atuadores                  | @Kavanell                       |
| 05 | Implementar regras de controle com Strategy     | @Kavanell                       |
| 06 | Implementar comandos e alarmes no C++           | @Kavanell                       |
| 07 | Gerar JSON Lines no C++                         | @Kavanell                       |
| 08 | Criar supervisor Streamlit                      | @ghabrielhscosta-hub            |
| 09 | Ler e validar JSON Lines no Python              | @ghabrielhscosta-hub            |
| 10 | Implementar histórico em CSV com Repository     | @ghabrielhscosta-hub            |
| 11 | Criar gráficos, alarmes e comandos no Streamlit | @ghabrielhscosta-hub            |
| 12 | Criar testes do dispositivo C++                 | @Kavanell                       |
| 13 | Criar testes do supervisor Python               | @ghabrielhscosta-hub            |
| 14 | Testar integração C++ com Python                | @Kavanell, @ghabrielhscosta-hub |
| 15 | Atualizar README e AI_LOG                       | @Kavanell, @ghabrielhscosta-hub |

---

## Uso de IA

O uso de IA será documentado no arquivo:

```text
AI_LOG.md
```

Esse arquivo registra:

* data;
* ferramenta utilizada;
* pedido feito à IA;
* o que foi aceito;
* o que foi rejeitado;
* justificativa técnica da dupla.

O objetivo do AI_LOG é mostrar que a IA foi usada como apoio, mas que as decisões foram revisadas e compreendidas pela dupla.

---

## Apresentação técnica

A apresentação técnica será realizada durante a defesa do trabalho.

Ela deve abordar:

* objetivo do projeto;
* arquitetura em duas camadas;
* assinatura operacional da dupla;
* contrato JSON;
* dispositivo C++;
* supervisor Streamlit;
* histórico CSV;
* padrões Strategy e Repository;
* testes;
* uso de IA;
* limitações conhecidas.

Cada integrante deve conseguir explicar uma parte que implementou e uma parte que revisou.

---

## Limitações conhecidas

* O sistema é uma simulação acadêmica e não controla equipamentos reais.
* A comunicação é feita por arquivo JSON Lines, não por rede TCP.
* O histórico usa CSV para manter a implementação simples.
* O supervisor Streamlit tem foco funcional, não visual.
* A falha do sensor travado é simulada por código.
* O arquivo `data/historico.csv` é gerado durante a execução e não deve ser tratado como base fixa do projeto.

---

## Arquivos que não devem ser versionados

Arquivos gerados ou temporários não devem ir para o GitHub:

```text
.venv/
__pycache__/
.pytest_cache/
*.pyc
data/historico.csv
dispositivo_cpp/mini_scada
dispositivo_cpp/mini_scada.exe
```

O arquivo de exemplo abaixo deve ser mantido:

```text
data/leituras_exemplo.jsonl
```

---

## Status da entrega

Checklist final:

* [x] Dispositivo C++ compila.
* [x] C++ gera registros compatíveis com o contrato JSON.
* [x] Supervisor Streamlit executa.
* [x] Python lê JSON Lines.
* [x] Python valida campos obrigatórios.
* [x] Histórico CSV é salvo via Repository.
* [x] Gráficos históricos aparecem no Streamlit.
* [x] Alarmes aparecem no Streamlit.
* [x] Comandos aparecem no Streamlit.
* [x] Falha simulada aparece na demonstração.
* [x] Strategy aparece no C++.
* [x] Repository aparece no Python.
* [x] Testes foram executados.
* [x] README está atualizado.
* [x] AI_LOG está preenchido.
