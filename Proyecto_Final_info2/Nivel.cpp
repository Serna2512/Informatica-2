#include "Nivel.h"

Nivel::Nivel()
{
    activo = false;
}

Nivel::~Nivel()
{
}

void Nivel::iniciar()
{
    activo = true;
}

void Nivel::finalizar(){
    activo = false;
}

bool Nivel::getActivo() const
{
    return activo;
}