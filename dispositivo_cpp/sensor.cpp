#include <iostream>;
#include <string>;
#include <vector>;
#include <optional>;

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
}

class Sensor {
    protected:
        string tag;
        optional<double> valor;
        string status "Normal";
        string tipo = "Sensor";

    public:
        virtual Leitura ler() = 0;

        virtual ~Sensor() {} = defaullt;
    
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



/*
int () {
  Sensor* s;
  SensorNivel sn;
  s = &sn;
  s->ler();
}
*/