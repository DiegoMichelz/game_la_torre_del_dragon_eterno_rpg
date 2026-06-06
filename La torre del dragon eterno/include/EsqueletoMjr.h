#pragma once
#include "Enemigo.h"

class EsqueletoMjr : public Enemigo{
     public:
        EsqueletoMjr(std::string nom, int hp, int atk, int def, int exp);
        virtual ~EsqueletoMjr();
};
