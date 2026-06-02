#pragma once
#include "Enemigo.h"

class Esqueleto : public Enemigo {
    public:
        Esqueleto(std::string nom, int hp, int atk, int def, int exp);
        virtual ~Esqueleto();

};


