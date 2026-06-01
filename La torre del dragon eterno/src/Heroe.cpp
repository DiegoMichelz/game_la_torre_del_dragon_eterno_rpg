#include "Heroe.h"

Heroe::Heroe(std::string nom, int hp, int atk, int def): Personaje (nom, hp, atk, def) {
    experiencia = 0;
    nivel = 1;
}

Heroe::~Heroe(){

}

void Heroe::ganarExperiencia(int cant){
    experiencia += cant; //subir nivel
}
