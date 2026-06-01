#pragma once
#include "Heroe.h"

class Guerrero : public Heroe{
    public:
        Guerrero(std::string nom, int hp, int atk, int def);

        void ejecutarGolpeFeroz(Personaje &objetivo);
        void mostrarEstadisticas() override;

};


