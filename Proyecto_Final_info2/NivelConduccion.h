#ifndef NIVELCONDUCCION_H
#define NIVELCONDUCCION_H

#include "nivel.h"
#include <vector>
using namespace std;

class Rigby;
class Pelota;
class Rival;
class Obstaculo;
class Potenciador;

enum class Dificultad
{
    FACIL,
    DIFICIL
};

class NivelConduccion : public Nivel
{
private:
    Rigby* rigby;
    Pelota* pelota;
    vector<Rival*> rivales;
    vector<Obstaculo*> obstaculos;
    vector<Potenciador*> potenciadores;

    Dificultad dificultad;
    float tiempoRestante;

    void comprobarColisiones();

public:
    NivelConduccion();
    ~NivelConduccion() override;

    void actualizar(float dt) override;
    void generarObstaculos();
    void generarPotenciadores();
    bool comprobarVictoria();
    void finalizar() override;

    //Getters
    Rigby* getRigby() const;
    Pelota* getPelota() const;

    const vector<Rival*>& getRivales() const; //getters devuelven refs constantes para no copiar todo el vector y que no se modifique la colecciom
    const vector<Obstaculo*>& getObstaculos() const;
    const vector<Potenciador*>& getPotenciadores() const;

    Dificultad getDificultad() const;
    float getTiempoRestante() const;

    //Setters
    void setRigby(Rigby* rigby);
    void setPelota(Pelota* pelota);
    void setDificultad(Dificultad dificultad);
    void setTiempoRestante(float tiempoRestante);
};

#endif // NIVELCONDUCCION_H