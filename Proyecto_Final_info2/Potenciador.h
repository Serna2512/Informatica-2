#ifndef POTENCIADOR_H
#define POTENCIADOR_H

class Rigby;

class Potenciador
{
private:
    float x;
    float y;
    float ancho;
    float alto;

    float factorAumento;
    float duracion;

    bool activo;

public:
    Potenciador(float x, float y, float ancho, float alto,
                float factorAumento, float duracion);

    bool recoger(Rigby* jugador);

    float getX() const;
    float getY() const;
    float getAncho() const;
    float getAlto() const;

    float getFactorAumento() const;
    float getDuracion() const;

    bool estaActivo() const;

    void desactivar();
};

#endif // POTENCIADOR_H