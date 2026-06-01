#include "Enemigo.h"
#include <iostream>

Enemigo::Enemigo(std::string nom, int hp, int atk, int def, int exp) : Personaje (nom, hp, atk, def){
        int expOtorgada = exp;
}

Enemigo::~Enemigo(){

}

int Enemigo::getexpOtorgada(){
     return expOtorgada;
}
int Enemigo::getAtaque() {
    return ataque;
}

void Enemigo::mostrarEstadisticas() {
    std::cout << "Enemigo: " << nombre << " | Vida: " << vidaActual << std::endl;
}
