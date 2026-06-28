import csv
from pathlib import Path


class HistoricoRepository:
    """
    Repository responsável por salvar e consultar o histórico CSV.

    o Streamlit não deve acessar o CSV diretamente.
    ele deve usar esta classe.
    """

    CABECALHO = [
        "categoria",
        "estacao",
        "tipo",
        "tag",
        "valor",
        "unidade",
        "timestamp",
        "status",
        "qualidade",
        "acao",
        "descricao",
    ]

    def __init__(self, caminho_csv):
        self.caminho_csv = Path(caminho_csv)

    def _garantir_arquivo(self):
        """
        cria a pasta e o arquivo CSV, caso ainda não existam.
        """

        self.caminho_csv.parent.mkdir(parents=True, exist_ok=True)

        if not self.caminho_csv.exists():
            with self.caminho_csv.open("w", encoding="utf-8", newline="") as arquivo:
                escritor = csv.DictWriter(arquivo, fieldnames=self.CABECALHO)
                escritor.writeheader()

    def _chave_registro(self, linha):
        """
        chave usada para evitar registros duplicados.
        """

        return (
            linha.get("categoria", ""),
            linha.get("timestamp", ""),
            linha.get("tag", ""),
            str(linha.get("valor", "")),
            linha.get("descricao", ""),
        )

    def _carregar_chaves_existentes(self):
        """
        lê o CSV e retorna as chaves dos registros já salvos.
        """

        chaves = set()

        if not self.caminho_csv.exists():
            return chaves

        with self.caminho_csv.open("r", encoding="utf-8", newline="") as arquivo:
            leitor = csv.DictReader(arquivo)

            for linha in leitor:
                chaves.add(self._chave_registro(linha))

        return chaves

    def _salvar_linhas(self, linhas):
        """
        salva linhas no CSV evitando duplicações.
        """

        self._garantir_arquivo()

        chaves_existentes = self._carregar_chaves_existentes()
        novas_linhas = []

        for linha in linhas:
            chave = self._chave_registro(linha)

            if chave not in chaves_existentes:
                novas_linhas.append(linha)
                chaves_existentes.add(chave)

        with self.caminho_csv.open("a", encoding="utf-8", newline="") as arquivo:
            escritor = csv.DictWriter(arquivo, fieldnames=self.CABECALHO)
            escritor.writerows(novas_linhas)

        return len(novas_linhas)

    def salvar_leituras(self, registros):
        """
        salva leituras de sensores no histórico.
        """

        linhas = []

        for registro in registros:
            if registro.get("tipo") != "sensor":
                continue

            linhas.append({
                "categoria": "leitura",
                "estacao": registro.get("estacao", ""),
                "tipo": registro.get("tipo", ""),
                "tag": registro.get("tag", ""),
                "valor": registro.get("valor", ""),
                "unidade": registro.get("unidade", ""),
                "timestamp": registro.get("timestamp", ""),
                "status": registro.get("status", ""),
                "qualidade": registro.get("qualidade", ""),
                "acao": registro.get("acao", ""),
                "descricao": "leitura de sensor",
            })

        return self._salvar_linhas(linhas)

    def salvar_alarmes(self, registros):
        """
        salva alarmes encontrados nos registros.
        """

        linhas = []

        for registro in registros:
            alarmes = registro.get("alarmes", [])

            if not isinstance(alarmes, list):
                continue

            for alarme in alarmes:
                linhas.append({
                    "categoria": "alarme",
                    "estacao": registro.get("estacao", ""),
                    "tipo": registro.get("tipo", ""),
                    "tag": registro.get("tag", ""),
                    "valor": registro.get("valor", ""),
                    "unidade": registro.get("unidade", ""),
                    "timestamp": registro.get("timestamp", ""),
                    "status": registro.get("status", ""),
                    "qualidade": registro.get("qualidade", ""),
                    "acao": "",
                    "descricao": alarme,
                })

        return self._salvar_linhas(linhas)

    def salvar_comandos(self, registros):
        """
        salva comandos encontrados nos registros.
        """

        linhas = []

        for registro in registros:
            comandos = registro.get("comandos", [])

            if not isinstance(comandos, list):
                continue

            for comando in comandos:
                linhas.append({
                    "categoria": "comando",
                    "estacao": registro.get("estacao", ""),
                    "tipo": registro.get("tipo", ""),
                    "tag": registro.get("tag", ""),
                    "valor": registro.get("valor", ""),
                    "unidade": registro.get("unidade", ""),
                    "timestamp": registro.get("timestamp", ""),
                    "status": registro.get("status", ""),
                    "qualidade": registro.get("qualidade", ""),
                    "acao": registro.get("acao", ""),
                    "descricao": comando,
                })

        return self._salvar_linhas(linhas)

    def salvar_registros(self, registros):
        """
        salva leituras, alarmes e comandos no histórico.
        """

        leituras_salvas = self.salvar_leituras(registros)
        alarmes_salvos = self.salvar_alarmes(registros)
        comandos_salvos = self.salvar_comandos(registros)

        return {
            "leituras": leituras_salvas,
            "alarmes": alarmes_salvos,
            "comandos": comandos_salvos,
        }

    def carregar_historico(self):
        """
        carrega todos os registros do histórico CSV.
        """

        if not self.caminho_csv.exists():
            return []

        with self.caminho_csv.open("r", encoding="utf-8", newline="") as arquivo:
            leitor = csv.DictReader(arquivo)
            return list(leitor)