#pragma once
#include "Enemigo.h"


class GuerreroZombie: public Enemigo
{
    public:
        GuerreroZombie(std::string nom, int hp, int atk, int def, int exp);
        virtual ~GuerreroZombie();

    protected:

    private:
};


