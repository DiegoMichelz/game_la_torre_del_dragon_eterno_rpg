#include "Guerrero.h"
#include <iostream>

Guerrero::Guerrero(std::string nom, int hp, int atk, int def) : Heroe (nom, hp, atk, def){

}

void Guerrero::ejecutarGolpeFeroz (Personaje &objetivo){
    //hace doble de danño
    int danioExtra = ataque * 2;
    objetivo.recibirDanio(danioExtra);
    std::cout << nombre << " uso Golpe Feroz!" << std::endl;
}

void Guerrero::mostrarEstadisticas() {
    std::cout << "--- GUERRERO ---" << std::endl;
    std::cout << "Nombre: " << nombre << " | Vida: " << vidaActual << std::endl;
}
