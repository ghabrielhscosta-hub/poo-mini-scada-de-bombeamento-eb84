#include <iostream>
#include <string>
#include <vector>
#include <optional>

using namespace std;

class Leitura {

    public :

        string tag;
        double valor;
        string unidade;
        string timestamp;
        string status;
        string tipo;
        vector<string> alarmes;
};

class Sensor {
    protected:
        string tag;
        optional<double> valor;
        string status = "normal";
        string tipo = "sensor";

    public:
        virtual Leitura ler() = 0;

        virtual ~Sensor() = default;
    
};

class SensorNivel : public Sensor {
    protected:
        string unidade = "%";
    public:
        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(0.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }
};

class SensorTemperatura : public Sensor {
    protected:
        string unidade = u8"\u00B0C";
    public:
        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(0.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }
};

class SensorVazao : public Sensor {
    protected:
        string unidade = "L/s";
    public:
        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(0.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }
};

class SensorPressao : public Sensor {
    protected:
        string unidade = "bar";
    public:
        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(0.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }

    
};



/*
int () {
  Sensor* s;
  SensorNivel sn;
  s = &sn;
  s->ler();
}
*/
