#include "Heroe.h"
#include "Personaje.h"

Heroe::Heroe(std::string nom, int hp, int atk, int def, int energiaMax): Personaje (nom, hp, atk, def), energia(energiaMax), energiaMax(energiaMax) {
    experiencia = 0;
    nivel = 1;
    curacionesRestantes = 5;
}

Heroe::~Heroe(){

}

void Heroe::ganarExperiencia(int cant){
    experiencia += cant; //subir nivel
}

void Heroe::usarCuracion() {
    if (curacionesRestantes > 0) {
        curacionesRestantes--;
    }
}

void Heroe::restaurarTodo() {
    vidaActual = vidaMaxima;      // Restaurar HP[cite: 3, 5]
    energia = energiaMax;         // Restaurar Energía[cite: 3, 9]
    curacionesRestantes = 5;      // Restaurar curaciones[cite: 3]
}

void Heroe::subirNivel() {
    nivel++;
    ataque += 5;   // Incremento de ataque
    defensa += 2;  // Incremento de defensa
    vidaMaxima += 20; // Incremento de vida máxima
    restaurarTodo(); // Al subir de nivel, también se restaura
}
