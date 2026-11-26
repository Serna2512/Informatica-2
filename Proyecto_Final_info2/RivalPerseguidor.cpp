#include "Rivalperseguidor.h"
#include "Rigby.h"
#include "Jugador.h"
#include "Proyectil.h"
#include <cmath>
#include <QRectF>
#include <QDebug>

RivalPerseguidor::RivalPerseguidor(float x, float y, float velocidad, unsigned short int danio, Rigby* objetivo)
    : Rival(x, y, velocidad, danio),
    objetivo(objetivo),
    distanciaAnterior(0.0),
    cantidadColisiones(0),
    intentosEsquivar(0)
{
}

RivalPerseguidor::~RivalPerseguidor()
{
}

float RivalPerseguidor::percibir()
{
    if (objetivo == nullptr)
        return -1.0;

    // Centro de Rigby (59 x 29)
    float centroRigbyX = objetivo->getX() + 29.5;
    float centroRigbyY = objetivo->getY() + 14.5;

    // Centro del rival (35 x 35)
    float centroRivalX = getX() + 17.5;
    float centroRivalY = getY() + 17.5;

    float dx = centroRigbyX - centroRivalX;
    float dy = centroRigbyY - centroRivalY;

    return sqrt(dx * dx + dy * dy); //retorna distancia entre sus centros
}

bool RivalPerseguidor::razonar(float distanciaActual)
{
    if (distanciaActual < 0.0)
        return false;

    return false; // Por ahora, siempre perseguir
}

void RivalPerseguidor::aprender(float distanciaActual)
{
    if (distanciaActual < 0.0)
        return;

    distanciaAnterior = distanciaActual; //conserva la distancia obtenida antes del movimiento
}

void RivalPerseguidor::actuar(bool bloquear, float dt, float distancia)
{
    //if (bloquear)
        //bloquearCamino(dt, distancia);
    //else
        perseguir(dt, distancia);
}

void RivalPerseguidor::perseguir(float dt, float distancia)
{
    if (objetivo == nullptr || dt <= 0.0 || distancia <= 0.01)
        return;

    // Rectángulo de Rigby
    QRectF rectRigby(
        objetivo->getX(),
        objetivo->getY(),
        59,
        29
        );

    // Rectángulo del rival
    QRectF rectRival(
        getX(),
        getY(),
        35,
        35
        );

    // Si ya están tocándose, no avanzar más
    if (rectRival.intersects(rectRigby))
        return;

    float centroRigbyX = objetivo->getX() + 29.5;
    float centroRigbyY = objetivo->getY() + 14.5;

    float centroRivalX = getX() + 17.5;
    float centroRivalY = getY() + 17.5;

    float dx = centroRigbyX - centroRivalX;
    float dy = centroRigbyY - centroRivalY;

    float desplazamiento = getVelocidad() * dt;

    // Mover hacia Rigby
    setX(getX() + (dx / distancia) * desplazamiento);
    setY(getY() + (dy / distancia) * desplazamiento);
}


void RivalPerseguidor::bloquearCamino(float dt, float distancia)
{
    if (objetivo == nullptr || dt <= 0.0 || distancia <= 0.01){
        return;}

    // Calculamos un punto lateral respecto a Rigby
    const float distanciaLateral = 30.0;

    float dx = objetivo->getX() - getX();
    float dy = objetivo->getY() - getY();

    float puntoX = objetivo->getX() - (dy / distancia) * distanciaLateral; //desplazamiento laterales en los ejes respectivos
    float puntoY = objetivo->getY() + (dx / distancia) * distanciaLateral;

    //Calculamos el desplazamiento hacia ese punto
    float dxPunto = puntoX - getX();
    float dyPunto = puntoY - getY();

    float distanciaPunto = sqrt(dxPunto * dxPunto + dyPunto * dyPunto);

    if (distanciaPunto <= 0.01){
        return;}

    float desplazamiento = getVelocidad() * dt;

    if (desplazamiento >= distanciaPunto)
    {
        setX(puntoX);
        setY(puntoY);
    }
    else
    {
        setX(getX() + (dxPunto / distanciaPunto) * desplazamiento);
        setY(getY() + (dyPunto / distanciaPunto) * desplazamiento);
    }
}


unique_ptr<Proyectil> RivalPerseguidor::atacar(Jugador* jugador)
{
    if (jugador == nullptr){
        return nullptr;}

    jugador->recibirDanio(getDanio());

    cantidadColisiones++;
    return nullptr; //devolvemos nullptr ya que este rival no crea proyectiles, ataca por contacto
}

void RivalPerseguidor::actualizar(float dt)
{
    if (dt <= 0.0 || objetivo == nullptr)
        return;

    // Actualizar el tiempo entre ataques
    tiempoUltimoAtaque += dt;

    float distanciaActual = percibir();

    if (distanciaActual < 0.0)
        return;

    // Perseguir a Rigby
    perseguir(dt, distanciaActual);

    // 2. Evitar que el rival salga de la cancha
    if (getX() < 0.0)
        setX(0.0);

    if (getX() > 750.0)
        setX(750.0);

    if (getY() < 29.0)
        setY(29.0);

    if (getY() > 507.0)
        setY(507.0);

    // Comprobar contacto
    QRectF rectRigby(
        objetivo->getX(),
        objetivo->getY(),
        59,
        29
        );

    QRectF rectRival(
        getX(),
        getY(),
        35,
        35
        );

    //qDebug() << "Rectangulo Rigby:" << rectRigby;
    //qDebug() << "Rectangulo Rival:" << rectRival;
    //qDebug() << "¿Intersectan?:" << rectRival.intersects(rectRigby);

    if (rectRival.intersects(rectRigby)) {

        if (tiempoUltimoAtaque >= tiempoEntreAtaques) {

            atacar(objetivo);

            //qDebug() << "¡RIGBY RECIBIO DANIO!";
            //qDebug() << "Vida restante:" << objetivo->getVida();

            tiempoUltimoAtaque = 0.0;
        }
    }

    aprender(percibir());
}