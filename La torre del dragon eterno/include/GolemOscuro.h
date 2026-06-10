#pragma once
#include "Enemigo.h"


class GolemOscuro: public Enemigo
{
    public:
        GolemOscuro(std::string nom, int hp, int atk, int def, int exp);
        virtual ~GolemOscuro();
};


