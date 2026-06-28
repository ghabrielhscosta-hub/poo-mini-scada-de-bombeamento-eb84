import pandas as pd
import streamlit as st


st.set_page_config(
    page_title="Mini-SCADA EB-84",
    layout="wide"
)

st.title("Mini-SCADA da Estação de Bombeamento — EB-84")

st.write(
    "Supervisor inicial em Python/Streamlit para visualização "
    "das leituras atuais da estação de bombeamento."
)

# Dados temporários apenas para a Issue 08.
# Nas próximas issues, esses dados serão lidos do arquivo JSON Lines gerado pelo C++.
leituras = [
    {
        "estacao": "EB-84",
        "tipo": "sensor",
        "tag": "nivel_reservatorio",
        "valor": 72.5,
        "unidade": "%",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    },
    {
        "estacao": "EB-84",
        "tipo": "sensor",
        "tag": "pressao_linha",
        "valor": 5.8,
        "unidade": "bar",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    },
    {
        "estacao": "EB-84",
        "tipo": "sensor",
        "tag": "vazao_saida",
        "valor": 18.2,
        "unidade": "L/s",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    },
    {
        "estacao": "EB-84",
        "tipo": "sensor",
        "tag": "temperatura_motor",
        "valor": 62.0,
        "unidade": "°C",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    },
]

bombas = [
    {
        "bomba": "Bomba 1",
        "estado": "ligada",
        "status": "normal",
    },
    {
        "bomba": "Bomba 2",
        "estado": "desligada",
        "status": "normal",
    },
]

df_leituras = pd.DataFrame(leituras)
df_bombas = pd.DataFrame(bombas)

st.subheader("Resumo operacional")

col1, col2, col3 = st.columns(3)

with col1:
    st.metric("Estação", "EB-84")

with col2:
    st.metric("Status geral", "Normal")

with col3:
    st.metric("Bombas ligadas", "1")

st.subheader("Leituras atuais")

st.dataframe(
    df_leituras,
    use_container_width=True
)

st.subheader("Estado das bombas")

st.dataframe(
    df_bombas,
    use_container_width=True
)

st.info(
    "Esta é a tela inicial do supervisor. "
    "A leitura real do arquivo JSON Lines será implementada na Issue 09."
)