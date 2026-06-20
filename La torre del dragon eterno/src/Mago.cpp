#include "Mago.h"
#include "Enemigo.h"
#include "Heroe.h"
#include <iostream>


Mago::Mago(std::string nom, int hp, int atk, int def, int energiaMax) : Heroe(nom, hp, atk, def, energiaMax) {

}

void Mago::ataqueEspecial(Enemigo* objetivo){
    // Bola de fuego ignorando un poco la defensa (o daño directo mágico)
    objetivo->recibirDanio(ataque + 20);
    std::cout << nombre << " lanzo una Bola de Fuego!" << std::endl;
}

void Mago::mostrarEstadisticas() {
    std::cout << "--- MAGO ---" << std::endl;
    std::cout << "Nombre: " << nombre << " | Vida: " << vidaActual << std::endl;

}

void Mago::curarse() {
    vidaActual += 40;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
}

void Mago::subirNivel() {
    nivel++;
    ataque += 4;      // Menor incremento de ataque[cite: 2]
    defensa += 4;     // Incremento de defensa bajo[cite: 2]
    vidaMaxima += 25; // Vida baja[cite: 2]
    energiaMax += 15; // Más mana para compensar su debilidad física
    restaurarTodo();  // Aplica los nuevos máximos
}
