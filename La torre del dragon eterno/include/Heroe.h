#pragma once
#include "Personaje.h"

class Enemigo; //declaracion anticipada

class Heroe : public Personaje {
    protected:
        int experiencia;
        int nivel;
        int energia;        // Variable compartida
        int energiaMax;     // Para saber cuál es el tope
        int curacionesRestantes;
    public:
        Heroe(std::string nom, int hp, int atk, int def, int energiaMax);
        int getCuracionesRestantes() { return curacionesRestantes; }
        void usarCuracion(); // Método para restar
        void ganarExperiencia(int cant);
        virtual void curarse() = 0;
        virtual void ataqueEspecial(Enemigo* objetivo) = 0;

        //logica restauracion y subida de nivel
        void restaurarTodo();
        virtual void subirNivel()=0;

        // Métodos para manejar la energía
        int getEnergia() { return energia; }
        void gastarEnergia(int cantidad) {
            energia -= cantidad;
            if (energia < 0) energia = 0;
        }

        void recuperarEnergia(int cantidad) {
            energia += cantidad;
            if (energia > energiaMax) energia = energiaMax;
        }

        void recargarCuraciones() { curacionesRestantes = 5; }

        virtual ~Heroe();
    };
