# Contrato JSON

O dispositivo em C++ gera leituras, comandos e eventos em formato JSON Lines (`.jsonl`).
Cada linha do arquivo representa uma leitura ou evento da estação de bombeamento `EB-84`.

A comunicação segue o fluxo:

```text
Dispositivo C++ → arquivo JSON Lines → Supervisor Python/Streamlit
```

## Campos obrigatórios

| Campo       | Tipo   | Descrição                                     |
| ----------- | ------ | --------------------------------------------- |
| `tag`       | texto  | Identificador do sensor, bomba ou ativo       |
| `valor`     | número | Valor da leitura ou código numérico do evento |
| `unidade`   | texto  | Unidade da leitura ou tipo do evento          |
| `timestamp` | texto  | Data e hora da leitura ou evento              |
| `status`    | texto  | Estado operacional                            |

## Campos opcionais

| Campo       | Tipo            | Descrição                                                  |
| ----------- | --------------- | ---------------------------------------------------------- |
| `estacao`   | texto           | Identificador da estação, neste projeto `EB-84`            |
| `tipo`      | texto           | Tipo do registro: `sensor`, `bomba`, `comando` ou `alarme` |
| `qualidade` | texto           | Qualidade da leitura: `valida`, `ruidosa` ou `travada`     |
| `alarmes`   | lista de textos | Alarmes ativos no ciclo                                    |
| `comandos`  | lista de textos | Comandos executados ou solicitados                         |
| `acao`      | texto           | Ação executada em um comando                               |

## Unidades usadas

| Variável              | Unidade   |
| --------------------- | --------- |
| Nível do reservatório | `%`       |
| Pressão da linha      | `bar`     |
| Vazão                 | `L/s`     |
| Temperatura           | `°C`      |
| Comando               | `comando` |

## Status possíveis

| Status      | Significado                          |
| ----------- | ------------------------------------ |
| `normal`    | Leitura dentro dos limites esperados |
| `alerta`    | Situação que exige atenção           |
| `alarme`    | Situação crítica ou fora do limite   |
| `falha`     | Falha simulada ou leitura inválida   |
| `executado` | Comando executado com sucesso        |
| `bloqueado` | Comando recusado por alguma regra    |

## Alarmes possíveis

| Alarme                     | Significado                                      |
| -------------------------- | ------------------------------------------------ |
| `nivel_baixo`              | Nível abaixo do limite de 24%                    |
| `nivel_alto`               | Nível acima do limite de 84%                     |
| `pressao_alta`             | Pressão acima de 6.4 bar em um ciclo             |
| `pressao_alta_persistente` | Pressão acima de 6.4 bar por 3 ciclos consecutivos |
| `sensor_nivel_travado`     | Sensor de nível travado por 10 ciclos            |

## Regra extra da dupla

A regra extra da dupla é `Pressão alta por vários ciclos`.

Neste projeto, a regra será considerada ativa quando a pressão da linha ficar acima de `6.4 bar` por 3 ciclos consecutivos.

Quando isso ocorrer, o dispositivo C++ deve gerar o alarme:

```text
pressao_alta_persistente
```

## Comandos possíveis

| Comando            | Significado                             |
| ------------------ | --------------------------------------- |
| `ligar_bomba_1`    | Liga a bomba 1                          |
| `desligar_bomba_1` | Desliga a bomba 1                       |
| `alternar_bomba`   | Alterna a bomba principal               |
| `resetar_alarme`   | Reseta alarmes ativos, quando permitido |

## Exemplo de leitura normal

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

## Exemplo com alarme

```json
{
  "estacao": "EB-84",
  "tipo": "sensor",
  "tag": "pressao_linha",
  "valor": 6.8,
  "unidade": "bar",
  "timestamp": "2026-06-27T15:31:00",
  "status": "alarme",
  "alarmes": ["pressao_alta", "pressao_alta_persistente"],
  "qualidade": "valida",
  "comandos": ["desligar_bomba_1"]
}
```

## Exemplo com comando

```json
{
  "estacao": "EB-84",
  "tipo": "comando",
  "tag": "bomba_1",
  "valor": 1,
  "unidade": "comando",
  "timestamp": "2026-06-27T15:32:00",
  "status": "executado",
  "acao": "ligar",
  "comandos": ["ligar_bomba_1"]
}
```

## Parâmetros da dupla

| Item                     | Valor                                 |
| ------------------------ | ------------------------------------- |
| ID_DUPLA                 | 84                                    |
| Identificador da estação | EB-84                                 |
| Nível baixo              | 24%                                   |
| Nível alto               | 84%                                   |
| Pressão alta             | 6.4 bar                               |
| Falha simulada           | Sensor de nível travado por 10 ciclos |
| Regra extra              | Pressão alta por vários ciclos        |

## Frequência de gravação

O dispositivo em C++ deve gerar uma nova linha no arquivo `.jsonl` a cada ciclo de simulação.

O supervisor Python/Streamlit deve ler esse arquivo, validar os campos obrigatórios e salvar o histórico em CSV.
