import pandas as pd
import streamlit as st

from json_reader import carregar_jsonl


ESTACAO_ID = "EB-84"
CAMINHO_JSONL = "data/leituras_exemplo.jsonl"


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

st.info(
    "Nesta etapa, o supervisor já lê e valida um arquivo JSON Lines. "
    "O histórico CSV será implementado na Issue 10."
)