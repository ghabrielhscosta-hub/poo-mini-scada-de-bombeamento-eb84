#include "JsonWriter.h"

#include "ParametrosOperacionais.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::string timestampAtual() {
    auto agora = std::chrono::system_clock::now();
    std::time_t tempo = std::chrono::system_clock::to_time_t(agora);
    std::tm tempoLocal{};

#ifdef _WIN32
    localtime_s(&tempoLocal, &tempo);
#else
    localtime_r(&tempo, &tempoLocal);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tempoLocal, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

std::string escaparJson(const std::string& texto) {
    std::string resultado;

    for (char c : texto) {
        if (c == '"') {
            resultado += "\\\"";
        } else if (c == '\\') {
            resultado += "\\\\";
        } else {
            resultado += c;
        }
    }

    return resultado;
}

std::string alarmesParaJson(const std::vector<Alarme>& alarmes) {
    std::ostringstream json;
    json << "[";

    for (size_t i = 0; i < alarmes.size(); i++) {
        if (i > 0) {
            json << ",";
        }

        json << "\"" << escaparJson(alarmes[i].getCodigo()) << "\"";
    }

    json << "]";
    return json.str();
}

std::string comandosParaJson(const std::vector<std::string>& comandos) {
    std::ostringstream json;
    json << "[";

    for (size_t i = 0; i < comandos.size(); i++) {
        if (i > 0) {
            json << ",";
        }

        json << "\"" << escaparJson(comandos[i]) << "\"";
    }

    json << "]";
    return json.str();
}
}

JsonWriter::JsonWriter(const std::filesystem::path& caminho)
    : caminhoArquivo(caminho) {
    std::filesystem::path pasta = caminhoArquivo.parent_path();

    if (!pasta.empty()) {
        std::filesystem::create_directories(pasta);
    }

    arquivo.open(caminhoArquivo, std::ios::out | std::ios::trunc);

    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel criar o arquivo JSON Lines.");
    }
}

JsonWriter::~JsonWriter() {
    if (arquivo.is_open()) {
        arquivo.close();
    }
}

void JsonWriter::escreverLinha(const std::string& linha) {
    arquivo << linha << '\n';

    if (!arquivo.good()) {
        throw std::runtime_error("Erro ao escrever no arquivo JSON Lines.");
    }
}

void JsonWriter::escreverSensor(const std::string& tag,
                                double valor,
                                const std::string& unidade,
                                const std::string& status,
                                const std::string& qualidade,
                                const std::vector<Alarme>& alarmes,
                                const std::vector<std::string>& comandos) {
    escreverEvento("sensor", tag, valor, unidade, status, qualidade, "", alarmes, comandos);
}

void JsonWriter::escreverBomba(const Bomba& bomba,
                               const std::vector<Alarme>& alarmes,
                               const std::vector<std::string>& comandos) {
    int valor = bomba.getEstado() == EstadoBomba::Ligada ? 1 : 0;
    escreverEvento(
        "bomba",
        bomba.getTag(),
        valor,
        "estado",
        "normal",
        "valida",
        bomba.estadoComoTexto(),
        alarmes,
        comandos);
}

void JsonWriter::escreverEvento(const std::string& tipo,
                                const std::string& tag,
                                double valor,
                                const std::string& unidade,
                                const std::string& status,
                                const std::string& qualidade,
                                const std::string& acao,
                                const std::vector<Alarme>& alarmes,
                                const std::vector<std::string>& comandos) {
    std::ostringstream json;

    json << "{";
    json << "\"estacao\":\"" << escaparJson(ParametrosOperacionais::ESTACAO) << "\",";
    json << "\"tipo\":\"" << escaparJson(tipo) << "\",";
    json << "\"tag\":\"" << escaparJson(tag) << "\",";
    json << "\"valor\":" << valor << ",";
    json << "\"unidade\":\"" << escaparJson(unidade) << "\",";
    json << "\"timestamp\":\"" << timestampAtual() << "\",";
    json << "\"status\":\"" << escaparJson(status) << "\",";
    json << "\"qualidade\":\"" << escaparJson(qualidade) << "\",";

    if (!acao.empty()) {
        json << "\"acao\":\"" << escaparJson(acao) << "\",";
    }

    json << "\"alarmes\":" << alarmesParaJson(alarmes) << ",";
    json << "\"comandos\":" << comandosParaJson(comandos);
    json << "}";

    escreverLinha(json.str());
}
