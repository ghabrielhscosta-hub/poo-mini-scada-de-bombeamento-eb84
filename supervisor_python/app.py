import pandas as pd
import streamlit as st

from json_reader import carregar_jsonl
from historico_repository import HistoricoRepository

ESTACAO_ID = "EB-84"
CAMINHO_JSONL = "data/leituras_dispositivo.jsonl"
CAMINHO_HISTORICO = "data/historico.csv"

st.set_page_config(
    page_title="Mini-SCADA EB-84",
    layout="wide"
)

historico_repository = HistoricoRepository(CAMINHO_HISTORICO)

st.title("Mini-SCADA da Estação de Bombeamento — EB-84")

st.write(
    "Supervisor em Python/Streamlit para visualização "
    "das leituras atuais da estação de bombeamento."
)

registros_validos, registros_invalidos = carregar_jsonl(CAMINHO_JSONL)

leituras = [
    registro
    for registro in registros_validos
    if registro.get("tipo") == "sensor"
]

bombas = [
    registro
    for registro in registros_validos
    if registro.get("tipo") == "bomba"
]

df_leituras = pd.DataFrame(leituras)
df_bombas = pd.DataFrame(bombas)

historico = historico_repository.carregar_historico()

st.subheader("Resumo operacional")

col1, col2, col3 = st.columns(3)

with col1:
    st.metric("Estação", ESTACAO_ID)

with col2:
    if registros_invalidos:
        st.metric("Status da validação", "Com erros")
    else:
        st.metric("Status da validação", "OK")

with col3:
    st.metric("Registros válidos", len(registros_validos))


st.subheader("Leituras atuais")

if df_leituras.empty:
    st.warning("Nenhuma leitura de sensor válida foi encontrada.")
else:
    st.dataframe(
        df_leituras,
        use_container_width=True
    )


st.subheader("Estado das bombas")

if df_bombas.empty:
    st.warning("Nenhum registro de bomba válido foi encontrado.")
else:
    st.dataframe(
        df_bombas,
        use_container_width=True
    )


st.subheader("Gráficos históricos")

if historico:
    df_grafico = pd.DataFrame(historico)

    if "valor" in df_grafico.columns and "tag" in df_grafico.columns:
        df_grafico["valor"] = pd.to_numeric(
            df_grafico["valor"],
            errors="coerce"
        )

        df_grafico = df_grafico.dropna(subset=["valor"])

        dados_nivel = df_grafico[
            df_grafico["tag"] == "nivel_reservatorio"
        ].reset_index(drop=True)

        dados_pressao = df_grafico[
            df_grafico["tag"] == "pressao_linha"
        ].reset_index(drop=True)

        col_grafico1, col_grafico2 = st.columns(2)

        with col_grafico1:
            st.write("Nível do reservatório")

            if dados_nivel.empty:
                st.info("Não há dados de nível disponíveis.")
            else:
                st.line_chart(dados_nivel["valor"])

        with col_grafico2:
            st.write("Pressão da linha")

            if dados_pressao.empty:
                st.info("Não há dados de pressão disponíveis.")
            else:
                st.line_chart(dados_pressao["valor"])
    else:
        st.info("O histórico ainda não possui colunas suficientes para gerar gráficos.")
else:
    st.info("O histórico CSV ainda não possui registros para gerar gráficos.")


st.subheader("Alarmes")

alarmes_encontrados = []

for registro in registros_validos:
    alarmes = registro.get("alarmes", [])

    if not isinstance(alarmes, list):
        continue

    for alarme in alarmes:
        alarmes_encontrados.append({
            "timestamp": registro.get("timestamp", ""),
            "tag": registro.get("tag", ""),
            "alarme": alarme,
            "status": registro.get("status", ""),
        })

if alarmes_encontrados:
    df_alarmes = pd.DataFrame(alarmes_encontrados)
    df_alarmes = df_alarmes.drop_duplicates()

    st.dataframe(
        df_alarmes,
        use_container_width=True
    )

    if "sensor_nivel_travado" in df_alarmes["alarme"].values:
        st.warning("Falha simulada detectada: sensor de nível travado.")

    if "pressao_alta_persistente" in df_alarmes["alarme"].values:
        st.error("Regra extra acionada: pressão alta por vários ciclos.")
else:
    st.success("Nenhum alarme encontrado.")


st.subheader("Comandos")

comandos_encontrados = []

for registro in registros_validos:
    comandos = registro.get("comandos", [])

    if not isinstance(comandos, list):
        continue

    for comando in comandos:
        comandos_encontrados.append({
            "timestamp": registro.get("timestamp", ""),
            "tag": registro.get("tag", ""),
            "comando": comando,
            "status": registro.get("status", ""),
            "acao": registro.get("acao", ""),
        })

if comandos_encontrados:
    df_comandos = pd.DataFrame(comandos_encontrados)
    df_comandos = df_comandos.drop_duplicates()

    st.dataframe(
        df_comandos,
        use_container_width=True
    )
else:
    st.info("Nenhum comando encontrado.")


st.subheader("Validação do arquivo JSON Lines")

if registros_invalidos:
    st.error(f"Foram encontrados {len(registros_invalidos)} registro(s) inválido(s).")

    df_invalidos = pd.DataFrame(registros_invalidos)

    st.dataframe(
        df_invalidos,
        use_container_width=True
    )
else:
    st.success("Todos os registros do arquivo JSON Lines são válidos.")


st.subheader("Histórico CSV")

st.write("O histórico é salvo usando o padrão Repository.")

if st.button("Salvar registros válidos no histórico"):
    resultado = historico_repository.salvar_registros(registros_validos)

    total_salvo = (
        resultado["leituras"]
        + resultado["alarmes"]
        + resultado["comandos"]
    )

    if total_salvo > 0:
        st.success(
            f"{total_salvo} novo(s) registro(s) salvo(s): "
            f"{resultado['leituras']} leitura(s), "
            f"{resultado['alarmes']} alarme(s), "
            f"{resultado['comandos']} comando(s)."
        )
    else:
        st.info("Nenhum registro novo foi salvo. Os dados já estavam no histórico.")

historico = historico_repository.carregar_historico()

if historico:
    df_historico = pd.DataFrame(historico)

    st.write("Histórico salvo:")
    st.dataframe(
        df_historico,
        use_container_width=True
    )
else:
    st.info("O histórico CSV ainda não possui registros.")