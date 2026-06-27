# Contrato JSON

O dispositivo em C++ gera leituras em formato JSON Lines.  
Cada linha do arquivo representa uma leitura ou evento da estação.

## Campos obrigatórios

| Campo | Tipo | Descrição |
|---|---|---|
| tag | texto | Identificador do sensor ou ativo |
| valor | número | Valor da leitura |
| unidade | texto | Unidade da leitura |
| timestamp | texto | Data e hora da leitura |
| status | texto | Estado operacional |

## Exemplo de leitura normal

```json
{
  "estacao": "EB-17",
  "tipo": "sensor",
  "tag": "nivel_reservatorio",
  "valor": 72.5,
  "unidade": "%",
  "timestamp": "2026-06-27T15:30:00",
  "status": "normal"
  "qualidade": "valida"
}
```
## Exemplo com alarme
```json
{
  "estacao": "EB-17",
  "tipo": "sensor",
  "tag": "pressao_linha",
  "valor": 7.2,
  "unidade": "bar",
  "timestamp": "2026-06-27T15:31:00",
  "status": "alarme",
  "alarmes": ["pressao_alta"],
  "qualidade": "valida"
}
```
## Exemplo com comando
```json
{
  "estacao": "EB-17",
  "tipo": "comando",
  "tag": "bomba_1",
  "valor": "ligar",
  "unidade": "comando",
  "timestamp": "2026-06-27T15:32:00",
  "status": "executado",
  "comandos": ["ligar_bomba_1"]
}
```
