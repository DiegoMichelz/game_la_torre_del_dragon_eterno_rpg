#pragma once
#include "Heroe.h"

class Mago : public Heroe {
    public:
        Mago(std::string nom, int hp, int atk, int def);

        // Método especial del Mago
        void lanzarBolaDeFuego(Personaje &objetivo);
        void mostrarEstadisticas() override;
};
