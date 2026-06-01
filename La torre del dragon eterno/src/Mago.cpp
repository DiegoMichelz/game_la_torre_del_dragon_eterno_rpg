#include "Mago.h"
#include <iostream>

Mago::Mago(std::string nom, int hp, int atk, int def) : Heroe(nom, hp, atk, def) {

}

void Mago::lanzarBolaDeFuego(Personaje &objetivo) {
    // Bola de fuego ignorando un poco la defensa (o daño directo mágico)
    objetivo.recibirDanio(ataque + 10);
    std::cout << nombre << " lanzo una Bola de Fuego!" << std::endl;
}

void Mago::mostrarEstadisticas() {
    std::cout << "--- MAGO ---" << std::endl;
    std::cout << "Nombre: " << nombre << " | Vida: " << vidaActual << std::endl;
}
