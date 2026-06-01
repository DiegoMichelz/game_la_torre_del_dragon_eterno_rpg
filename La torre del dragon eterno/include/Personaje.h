#pragma once
#include <string>

class Personaje
{
    protected:
        std::string nombre;
        int vidaActual;
        int vidaMaxima;
        int ataque;
        int defensa;

    public:
        Personaje(std::string nom, int hp, int atk, int def);
        virtual ~Personaje() ;

        void recibirDanio(int cantidad);
        bool estaVivo();

        virtual void mostrarEstadisticas() = 0;
        std::string getNombre();
        int getVidaActual();
        int getVidaMaxima();
        int getAtaque();
};
