#pragma once
#include "Enemigo.h"


class MagoDragon: public Enemigo
{
    public:
        MagoDragon(std::string nom, int hp, int atk, int def, int exp);
        virtual ~MagoDragon();

    protected:

    private:
};
