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
