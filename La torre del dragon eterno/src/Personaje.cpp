#include "Personaje.h"

Personaje::Personaje(std::string nom, int hp, int atk, int def){
    nombre = nom;
    vidaMaxima = hp;
    vidaActual = hp;
    ataque = atk;
    defensa = def;

}

Personaje::~Personaje(){

}
 //recibir daño
void Personaje::recibirDanio(int cantidad){
    int danioFinal = cantidad -  defensa;
    if (danioFinal < 1){
        danioFinal = 1; //al menos le saca 1 de vida siempre
    }

    vidaActual -= danioFinal;
    if (vidaActual < 0){
        vidaActual = 0; //evita que la vida quede en numeros negativos
    }
}
 //pregunta si aun vive y devuelve verdadero si le queda vida
bool Personaje::estaVivo(){
    return vidaActual > 0;
 }

 int Personaje::getAtaque() {
    return ataque;
}
 //para mostrarlo en pantalla
std::string Personaje::getNombre(){ return nombre; }
int Personaje::getVidaActual() { return vidaActual; }
int Personaje::getVidaMaxima() { return vidaMaxima; }
