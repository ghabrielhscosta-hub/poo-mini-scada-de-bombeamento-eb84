CAMPOS_OBRIGATORIOS = {
    "tag": str,
    "valor": (int, float),
    "unidade": str,
    "timestamp": str,
    "status": str,
}

CAMPOS_OPCIONAIS = {
    "estacao": str,
    "tipo": str,
    "qualidade": str,
    "acao": str,
    "alarmes": list,
    "comandos": list,
}


def validar_registro(registro):
    
    if not isinstance(registro, dict):
        return False, "O registro não é um objeto JSON válido."

    for campo, tipo_esperado in CAMPOS_OBRIGATORIOS.items():
        if campo not in registro:
            return False, f"Campo obrigatório ausente: {campo}"

        if not isinstance(registro[campo], tipo_esperado):
            return False, f"O campo '{campo}' possui tipo inválido."

    for campo, tipo_esperado in CAMPOS_OPCIONAIS.items():
        if campo in registro and not isinstance(registro[campo], tipo_esperado):
            return False, f"O campo opcional '{campo}' possui tipo inválido."

    return True, "Registro válido."