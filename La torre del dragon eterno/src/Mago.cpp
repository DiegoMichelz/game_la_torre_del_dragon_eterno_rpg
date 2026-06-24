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
    if(nivel==1){
        vidaActual += 38;
    }else if (nivel==2){
        vidaActual += 40;
    }else if (nivel==3) vidaActual+=44;
    if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
}

void Mago::subirNivel() {
    nivel++;
    if(nivel==2){
            ataque += 4;
            defensa += 4;
            vidaMaxima += 25;
            energiaMax += 15;
            restaurarTodo();
    }else if (nivel ==3){
            ataque +=6;
            defensa += 4;
            vidaMaxima += 35;
            energiaMax += 25;
            restaurarTodo();
    }

}
