
#ifndef NIVELCONDUCCION_H
#define NIVELCONDUCCION_H

#include "Nivel.h"
#include <memory>
#include <vector>

using namespace std;

class Rigby;
class Pelota;
class RivalPerseguidor;
class RivalLanzador;
class Proyectil;
class ZonaLodosa;
class Hueco;
class Potenciador;

enum class Dificultad
{
    FACIL,
    DIFICIL
};

class NivelConduccion : public Nivel
{
    //esta clase será la propietaria exclusiva de los objetos, (conoce los objetos de su nivel)

private:
    // Personajes y objetos principales
    unique_ptr<Rigby> rigby;
    unique_ptr<Pelota> pelota;
    unique_ptr<RivalPerseguidor> rivalPerseguidor;

    // Rivales y proyectiles
    vector<unique_ptr<RivalLanzador>> rivalesLanzadores;
    vector<unique_ptr<Proyectil>> proyectiles;

    // Obstáculos
    vector<unique_ptr<ZonaLodosa>> zonasLodosas;
    vector<unique_ptr<Hueco>> huecos;

    // Potenciadores
    vector<unique_ptr<Potenciador>> potenciadores;

    //estado colision con obstaculos
    vector<bool> dentroZonasLodosas;
    vector<bool> dentroHuecos;

    Dificultad dificultad;
    float tiempoRestante;

public:
    NivelConduccion();
    ~NivelConduccion() override;

    void actualizar(float dt) override;
    void generarObstaculos();
    void generarPotenciadores();
    bool comprobarVictoria();
    void finalizar() override;

    // Getters
    Rigby* getRigby() const;
    Pelota* getPelota() const;
    RivalPerseguidor* getRivalPerseguidor() const;

    const vector<unique_ptr<RivalLanzador>>& getRivalesLanzadores() const;
    const vector<unique_ptr<Proyectil>>& getProyectiles() const;
    const vector<unique_ptr<ZonaLodosa>>& getZonasLodosas() const;
    const vector<unique_ptr<Hueco>>& getHuecos() const;
    const vector<unique_ptr<Potenciador>>& getPotenciadores() const;

    Dificultad getDificultad() const;
    float getTiempoRestante() const;

    // Setters
    void setDificultad(Dificultad dificultad);
    void setTiempoRestante(float tiempoRestante);
};

#endif // NIVELCONDUCCION_H
