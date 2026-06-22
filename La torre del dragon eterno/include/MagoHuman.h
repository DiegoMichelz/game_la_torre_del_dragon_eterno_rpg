#pragma once
#include "Enemigo.h"


class MagoHuman: public Enemigo
{
    public:
        MagoHuman(std::string nom, int hp, int atk, int def, int exp);
        virtual ~MagoHuman();

    protected:

    private:
};

