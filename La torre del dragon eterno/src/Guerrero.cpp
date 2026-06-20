#include "Guerrero.h"
#include "Enemigo.h"
#include "Heroe.h"
#include <iostream>

Guerrero::Guerrero(std::string nom, int hp, int atk, int def, int energiaMax) : Heroe (nom, hp, atk, def, energiaMax){
}

void Guerrero::ataqueEspecial(Enemigo* objetivo){
    //hace doble de danño
    int danioExtra = ataque * 2;
    objetivo->recibirDanio(danioExtra);
    std::cout << nombre << " uso Golpe Feroz!" << std::endl;
}

void Guerrero::mostrarEstadisticas() {
    std::cout << "--- GUERRERO ---" << std::endl;
    std::cout << "Nombre: " << nombre << " | Vida: " << vidaActual << std::endl;
}

void Guerrero::curarse() {
    vidaActual += 15;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
}

void Guerrero::subirNivel() {
    nivel++;
    ataque += 5;      // Fuerte incremento de ataque[cite: 4]
    defensa += 3;     // ¡Más defensa para el guerrero![cite: 4]
    vidaMaxima += 15; // Mucha más vida[cite: 4]
    energiaMax += 8;  // Incremento moderado de estamina[cite: 4, 6]
    restaurarTodo();  // Aplica los nuevos máximos[cite: 1]
}
