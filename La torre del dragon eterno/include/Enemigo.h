#pragma once
#include "Personaje.h"

class Enemigo : public Personaje{
    protected:        int expOtorgada;

    public:
        Enemigo(std::string nom, int hp, int atk, int def, int exp);
        virtual ~Enemigo();

        int getexpOtorgada();
        int getAtaque();
        void mostrarEstadisticas() override;
};
