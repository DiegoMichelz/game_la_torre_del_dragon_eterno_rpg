#pragma once
#include "Enemigo.h"


class Golem : public Enemigo{
    public:
        Golem(std::string nom, int hp, int atk, int def, int exp);
        virtual ~Golem();
};


