#ifndef JSON_WRITER_H
#define JSON_WRITER_H

#include "Alarme.h"
#include "Bomba.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class JsonWriter {
private:
    std::filesystem::path caminhoArquivo;
    std::ofstream arquivo;

    void escreverLinha(const std::string& linha);

public:
    explicit JsonWriter(const std::filesystem::path& caminho = "data/leituras_dispositivo.jsonl");
    ~JsonWriter();

    void escreverSensor(const std::string& tag,
                        double valor,
                        const std::string& unidade,
                        const std::string& status,
                        const std::string& qualidade,
                        const std::vector<Alarme>& alarmes,
                        const std::vector<std::string>& comandos);

    void escreverBomba(const Bomba& bomba,
                       const std::vector<Alarme>& alarmes,
                       const std::vector<std::string>& comandos);

    void escreverEvento(const std::string& tipo,
                        const std::string& tag,
                        double valor,
                        const std::string& unidade,
                        const std::string& status,
                        const std::string& qualidade,
                        const std::string& acao,
                        const std::vector<Alarme>& alarmes,
                        const std::vector<std::string>& comandos);
};

#endif
