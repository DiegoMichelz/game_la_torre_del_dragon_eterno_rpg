#include "Heroe.h"
#include "Personaje.h"

Heroe::Heroe(std::string nom, int hp, int atk, int def, int energiaMax): Personaje (nom, hp, atk, def), energia(energiaMax), energiaMax(energiaMax) {
    experiencia = 0;
    nivel = 1;
}

Heroe::~Heroe(){

}

void Heroe::ganarExperiencia(int cant){
    experiencia += cant; //subir nivel
}
