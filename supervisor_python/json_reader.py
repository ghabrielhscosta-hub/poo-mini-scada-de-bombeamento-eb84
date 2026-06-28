import json
from pathlib import Path

from validator import validar_registro


def carregar_jsonl(caminho_arquivo):
    """
    Lê um arquivo JSON Lines e separa registros válidos e inválidos.

    Cada linha do arquivo deve conter um objeto JSON.
    """

    caminho = Path(caminho_arquivo)

    registros_validos = []
    registros_invalidos = []

    if not caminho.exists():
        return registros_validos, [
            {
                "linha": 0,
                "erro": f"Arquivo não encontrado: {caminho}",
                "conteudo": "",
            }
        ]

    with caminho.open("r", encoding="utf-8") as arquivo:
        for numero_linha, linha in enumerate(arquivo, start=1):
            linha = linha.strip()

            if not linha:
                continue

            try:
                registro = json.loads(linha)
            except json.JSONDecodeError as erro:
                registros_invalidos.append(
                    {
                        "linha": numero_linha,
                        "erro": f"JSON inválido: {erro}",
                        "conteudo": linha,
                    }
                )
                continue

            valido, mensagem = validar_registro(registro)

            if valido:
                registros_validos.append(registro)
            else:
                registros_invalidos.append(
                    {
                        "linha": numero_linha,
                        "erro": mensagem,
                        "conteudo": linha,
                    }
                )

    return registros_validos, registros_invalidos