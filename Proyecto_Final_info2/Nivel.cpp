#include "nivel.h"

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

bool Nivel::getActivo() const
{
    return activo;
}