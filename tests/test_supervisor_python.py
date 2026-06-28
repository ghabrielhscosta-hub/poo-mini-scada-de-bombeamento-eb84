import sys
from pathlib import Path

sys.path.append(str(Path(__file__).resolve().parents[1] / "supervisor_python"))

from validator import validar_registro
from json_reader import carregar_jsonl


def test_json_valido():
    registro = {
        "tag": "nivel_reservatorio",
        "valor": 72.5,
        "unidade": "%",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    }

    valido, mensagem = validar_registro(registro)

    assert valido is True
    assert mensagem == "Registro válido."


def test_json_sem_campo_obrigatorio():
    registro = {
        "tag": "nivel_reservatorio",
        "valor": 72.5,
        "unidade": "%",
        "timestamp": "2026-06-27T15:30:00",
    }

    valido, mensagem = validar_registro(registro)

    assert valido is False
    assert "status" in mensagem


def test_json_com_tipo_invalido():
    registro = {
        "tag": "pressao_linha",
        "valor": "alto",
        "unidade": "bar",
        "timestamp": "2026-06-27T15:30:00",
        "status": "normal",
    }

    valido, mensagem = validar_registro(registro)

    assert valido is False
    assert "valor" in mensagem


def test_arquivo_inexistente():
    registros_validos, registros_invalidos = carregar_jsonl("data/arquivo_inexistente.jsonl")

    assert registros_validos == []
    assert len(registros_invalidos) == 1
    assert "Arquivo não encontrado" in registros_invalidos[0]["erro"]


def test_linha_json_corrompida(tmp_path):
    arquivo = tmp_path / "corrompido.jsonl"
    arquivo.write_text(
        '{"tag":"nivel_reservatorio","valor":72.5}\n'
        '{"tag": "pressao_linha", "valor": }\n',
        encoding="utf-8"
    )

    registros_validos, registros_invalidos = carregar_jsonl(arquivo)

    assert len(registros_invalidos) >= 1