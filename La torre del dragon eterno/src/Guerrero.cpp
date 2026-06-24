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
    if(nivel==1){
        vidaActual += 10;
    }else if (nivel==2){
        vidaActual += 12;
    }else if (nivel==3) vidaActual+=18;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
}

void Guerrero::subirNivel() {
    nivel++;
    if(nivel==2){

        ataque += 5;
        defensa += 3;
        vidaMaxima += 15;
        energiaMax += 8;
        restaurarTodo();
    }else if (nivel==3){
        ataque += 7;
        defensa += 3;
        vidaMaxima += 25;
        energiaMax += 12;
        restaurarTodo();
    }
}
