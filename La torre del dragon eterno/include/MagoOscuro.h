#pragma once
#include "Enemigo.h"

class MagoOscuro: public Enemigo
{
    public:
        MagoOscuro (std::string nom, int hp, int atk, int def, int exp);
        virtual ~MagoOscuro();

};


