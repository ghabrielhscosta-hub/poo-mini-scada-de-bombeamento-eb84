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

class Sensor{
    protected:
        string tag;
        optional<double> valor;
        string status = "Normal";
        string tipo = "Sensor";
        string unidade ="";

    public:


        Sensor(string tag_inicial) : tag(tag_inicial) {}

        virtual Leitura ler()=0;

        const string& getTag() const { return tag; }
        const string& getStatus() const { return status; }
        const string& getTipo() const { return tipo; }
        

        virtual ~Sensor() = default;
    
};

class SensorNivel : public Sensor {
        public:
        SensorNivel() : Sensor("SN-01"){
            unidade = "%";
            tipo = "Nivel";       
        }

        double getValor() const { return valor.value_or(0.0); }

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
   public:

        SensorTemperatura() : Sensor("ST-01") {
            unidade = "°C";
            tipo = "Temperatura";       
        }

        double getValor() const { return valor.value_or(10.0); } 

        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(10.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }
};

class SensorVazao : public Sensor {
   
    public:
         SensorVazao() : Sensor("SV-01") {
            unidade = "L/s"; 
            tipo = "Vazao";      
        }

        double getValor() const { return valor.value_or(1.0); }

        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(1.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }
};

class SensorPressao : public Sensor {
    public:

        SensorPressao() : Sensor("SP-01") {
            unidade = "bar";
            tipo = "Pressao";
        }


        double getValor() const { return valor.value_or(2.0); }

        Leitura ler() override {
          Leitura l;
          l.valor = valor.value_or(2.0);
          l.tag = tag;
          l.status = status;
          l.tipo = tipo;
          l.unidade = unidade;
          return l;
    }

    
};