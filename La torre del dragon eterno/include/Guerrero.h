#pragma once
#include "Heroe.h"

class Guerrero : public Heroe{
    public:
        Guerrero(std::string nom, int hp, int atk, int def, int eMax);

        void ejecutarGolpeFeroz(Personaje &objetivo);
        void mostrarEstadisticas() override;
        void curarse() override;
        void ataqueEspecial(Enemigo* objetivo) override;

};


