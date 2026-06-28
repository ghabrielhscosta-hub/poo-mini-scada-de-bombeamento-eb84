import pandas as pd
import streamlit as st

from json_reader import carregar_jsonl
from historico_repository import HistoricoRepository

ESTACAO_ID = "EB-84"
CAMINHO_JSONL = "data/leituras_exemplo.jsonl"
CAMINHO_HISTORICO = "data/historico.csv"

historico_repository = HistoricoRepository(CAMINHO_HISTORICO)

st.set_page_config(
    page_title="Mini-SCADA EB-84",
    layout="wide"
)

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

st.write(
    "O histórico é salvo usando o padrão Repository. "
    )

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