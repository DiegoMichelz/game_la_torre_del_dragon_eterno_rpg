#pragma once
#include "Enemigo.h"

class SeguidordelVillano: public Enemigo
{
    public:
        SeguidordelVillano(std::string nom, int hp, int atk, int def, int exp);
        virtual ~SeguidordelVillano();

    protected:

    private:
};
