#include "NivelConduccion.h"
#include <QDebug>

#include "Rigby.h"
#include "Pelota.h"
#include "RivalPerseguidor.h"
#include "RivalLanzador.h"
#include "Proyectil.h"
#include "ZonaLodosa.h"
#include "Hueco.h"
#include "Potenciador.h"
#include <random>
#include <array>

NivelConduccion::NivelConduccion()
    : dificultad(Dificultad::FACIL),
    tiempoRestante(0.0)
{
    // Crear a Rigby
    rigby = unique_ptr<Rigby>(
        new Rigby(100, 300, 100, 120)
        );

    // Crear la pelota y asignarla inicialmente a Rigby
    pelota = unique_ptr<Pelota>(
        new Pelota(0, 0, 8)
        );

    pelota->transportarPor(rigby.get());

    // Crear el rival perseguidor
    rivalPerseguidor = unique_ptr<RivalPerseguidor>(
        new RivalPerseguidor(
            rigby->getX() + 250,
            rigby->getY(),
            65,
            5,
            rigby.get()
            )
        );

    // Crear los rivales lanzadores
    rivalesLanzadores.push_back(
        unique_ptr<RivalLanzador>(
            new RivalLanzador(342, 20, 0.0, 10, 2.0, 180.0)
            )
        );

    rivalesLanzadores.push_back(
        unique_ptr<RivalLanzador>(
            new RivalLanzador(342, 480, 0.0, 10, 2.0, 180.0)
            )
        );

    // Generar obstáculos y potenciadores
    generarObstaculos();
    generarPotenciadores();
}



NivelConduccion::~NivelConduccion()
{
}


void NivelConduccion::actualizar(float dt)
{
    // Implementaremos aquí la actualización del nivel
}

void NivelConduccion::finalizar()
{
    Nivel::finalizar();
}


//crear objetos lógicos

void NivelConduccion::generarObstaculos()
{
    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> posicionX(200, 560);
    uniform_int_distribution<int> posicionY(60, 440);

    // Estructura auxiliar para representar rectángulos
    struct Rectangulo {
        float x;
        float y;
        float ancho;
        float alto;
    };

    // Espacio reservado alrededor de Rigby
    Rectangulo rectRigby = {
        rigby->getX() - 100,
        rigby->getY() - 100,
        59 + 200,
        29 + 200
    };

    // Zona que deben evitar los obstáculos
    Rectangulo zonaArco = {620, 0, 180, 600};

    // Posiciones que ya están ocupadas
    vector<Rectangulo> posicionesOcupadas;

    // Comprobar si dos rectángulos se intersectan
    auto seIntersectan = [](const Rectangulo& a, const Rectangulo& b)
    {
        return a.x < b.x + b.ancho &&
               a.x + a.ancho > b.x &&
               a.y < b.y + b.alto &&
               a.y + a.alto > b.y;
    };

    // Comprobar si una posición es válida
    auto posicionValida = [&](const Rectangulo& candidato)
    {
        if (seIntersectan(candidato, rectRigby))
            return false;

        if (seIntersectan(candidato, zonaArco))
            return false;

        for (const Rectangulo& ocupada : posicionesOcupadas) {
            if (seIntersectan(candidato, ocupada))
                return false;
        }

        return true;
    };

    // Generar 4 zonas lodosas
    for (int i = 0; i < 4; i++) {

        bool generado = false;

        for (int intento = 0; intento < 500 && !generado; intento++) {

            float x = posicionX(generador);
            float y = posicionY(generador);

            Rectangulo rectangulo = {x, y, 100, 70};

            // Margen para evitar que queden demasiado cerca
            Rectangulo areaSeparacion = {
                x - 12,
                y - 12,
                100 + 24,
                70 + 24
            };

            if (!posicionValida(areaSeparacion))
                continue;

            zonasLodosas.push_back(
                unique_ptr<ZonaLodosa>(
                    new ZonaLodosa(x, y, 100, 70, 0.5)
                    )
                );

            posicionesOcupadas.push_back(areaSeparacion);

            generado = true;
        }

        if (!generado)
            qWarning() << "No se pudo generar una zona lodosa.";
    }

    // Generar 4 huecos
    for (int i = 0; i < 4; i++) {

        bool generado = false;

        for (int intento = 0; intento < 500 && !generado; intento++) {

            float x = posicionX(generador);
            float y = posicionY(generador);

            Rectangulo areaSeparacion = {
                x - 12,
                y - 12,
                65 + 24,
                50 + 24
            };

            if (!posicionValida(areaSeparacion))
                continue;

            huecos.push_back(
                unique_ptr<Hueco>(
                    new Hueco(x, y, 65, 50, 15)
                    )
                );

            posicionesOcupadas.push_back(areaSeparacion);

            generado = true;
        }

        if (!generado)
            qWarning() << "No se pudo generar un hueco.";
    }

    // Inicializar los estados de colisión
    dentroZonasLodosas.resize(zonasLodosas.size(), false);
    dentroHuecos.resize(huecos.size(), false);
}


//crear objetos potenciadores lógicos

void NivelConduccion::generarPotenciadores()
{
    // Evitar generar otro si ya existe uno activo
    if (!potenciadores.empty())
        return;

    random_device rd;
    mt19937 generador(rd());

    uniform_int_distribution<int> posicionX(200, 560);
    uniform_int_distribution<int> posicionY(40, 540);

    float x;
    float y;

    bool posicionValida = false;
    int intentos = 0;

    while (!posicionValida && intentos < 500) {

        x = posicionX(generador);
        y = posicionY(generador);

        posicionValida = true;

        // Evitar que aparezca encima de Rigby
        if (x < rigby->getX() + 59 &&
            x + 32 > rigby->getX() &&
            y < rigby->getY() + 29 &&
            y + 32 > rigby->getY()) {

            posicionValida = false;
        }

        // Evitar que aparezca encima de los huecos
        for (size_t i = 0; i < huecos.size(); i++) {

            if (x < huecos[i]->getX() + huecos[i]->getAncho() &&
                x + 32 > huecos[i]->getX() &&
                y < huecos[i]->getY() + huecos[i]->getAlto() &&
                y + 32 > huecos[i]->getY()) {

                posicionValida = false;
            }
        }

        intentos++;
    }

    if (!posicionValida)
        return;

    // Crear el potenciador lógico
    potenciadores.push_back(
        unique_ptr<Potenciador>(
            new Potenciador(x, y, 32, 32, 1.5, 5.0)
            )
        );
}
