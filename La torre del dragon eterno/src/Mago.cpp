#include "Mago.h"
#include "Enemigo.h"
#include <iostream>


Mago::Mago(std::string nom, int hp, int atk, int def) : Heroe(nom, hp, atk, def) {

}

void Mago::ataqueEspecial(Enemigo* objetivo){
    // Bola de fuego ignorando un poco la defensa (o daño directo mágico)
    objetivo->recibirDanio(ataque + 10);
    std::cout << nombre << " lanzo una Bola de Fuego!" << std::endl;
}

void Mago::mostrarEstadisticas() {
    std::cout << "--- MAGO ---" << std::endl;
    std::cout << "Nombre: " << nombre << " | Vida: " << vidaActual << std::endl;

}

void Mago::curarse() {
    vidaActual += 30;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
}
