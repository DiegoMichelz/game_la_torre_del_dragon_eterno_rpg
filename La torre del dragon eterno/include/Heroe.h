#pragma once
#include "Personaje.h"

class Enemigo; //declaracion anticipada

class Heroe : public Personaje {
    protected:
        int experiencia;
        int nivel;

    public:
        Heroe(std::string nom, int hp, int atk, int def);
        virtual ~Heroe();

        void ganarExperiencia(int cant);
        virtual void curarse() = 0;
        virtual void ataqueEspecial(Enemigo* objetivo) = 0;
};
