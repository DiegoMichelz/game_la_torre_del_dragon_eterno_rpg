#include <SFML/Graphics.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemigo.h"
#include "Guerrero.h"
#include "Mago.h"
#include "Esqueleto.h"
#include "EsqueletoMjr.h"
#include "Golem.h"
// 1. Definimos los estados posibles del juego (0 a 4)
enum EstadoJuego {
    MENU_PRINCIPAL,
    SELECCION_PERSONAJE,
    COMBATE_NIVEL_1,
    VICTORIA_PISO,
    GAME_OVER
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "La Torre del Dragon Eterno");
    window.setFramerateLimit(60); // definimos que corra a 60 fps

    // Variables de estado y puntero polimórfico para el héroe
    EstadoJuego estadoActual = MENU_PRINCIPAL;


    Heroe* heroe = nullptr; // Puntero de la clase base
    Enemigo* enemigoActual = nullptr;

    bool seleccion;

    int seleccionEnem=0;

   // --- CARGA DE TEXTURAS (Fuera del bucle while) ---
    sf:: Sprite fondoMenu;
    sf::Texture texFondoMenu;
    texFondoMenu.loadFromFile("FondoMenu.png");
    fondoMenu.setTexture(texFondoMenu);

    sf:: Sprite FondoSeleccionP;
    sf::Texture textFondoSeleccionP;
    textFondoSeleccionP.loadFromFile("SeleccionDePersonaje.png");
    FondoSeleccionP.setTexture(textFondoSeleccionP);

    sf:: Sprite fondolv1;
    sf::Texture texFondo;
    texFondo.loadFromFile("fondo_nivel1.png");
    fondolv1.setTexture(texFondo);

    sf::Sprite Magobase;
    sf::Texture texMago;
    texMago.loadFromFile("mago_sprite.png");
    Magobase.setTexture(texMago);
    Magobase.setPosition(65.f, 85.f);

    sf::Sprite Guerrerobase;
    sf::Texture texGuerre;
    texGuerre.loadFromFile("Guerrero_sprite.png");
    Guerrerobase.setTexture(texGuerre);
    Guerrerobase.setPosition(55.f, 85.f);


    sf::Sprite Esqueleto1_base;
    sf::Texture texEsque1eto1;
    texEsque1eto1.loadFromFile("esqueleto1_sprite.png");
    Esqueleto1_base.setTexture(texEsque1eto1);
    Esqueleto1_base.setPosition(550.f, 95.f);

    sf::Sprite Esqueleto2_base;
    sf::Texture texEsqueleto2;
    texEsqueleto2.loadFromFile("esqueletomejoradobase_sprite.png");
    Esqueleto2_base.setTexture(texEsqueleto2);
    Esqueleto2_base.setPosition(450.f, 65.f);

    sf::Sprite Golem_base;
    sf::Texture texGolem;
    texGolem.loadFromFile("golemdepiedrabase_sprite.png");
    Golem_base.setTexture(texGolem);
    Golem_base.setPosition(410.f, 65.f);

    // --- CARGA DE FUENTES Y TEXTOS (Para el menú rápido) ---
    sf::Font fuente;
    if (!fuente.loadFromFile("arial.ttf")) {
        // Manejar error si no encuentra la fuente
    }

    sf::Text txtSeleccion("Seleccione Clase:\n[G] Guerrero\n[M] Mago", fuente, 24);
    txtSeleccion.setPosition(250, 250);

    // Textos dinámicos para el combate
    sf::Text txtInfoCombate("", fuente, 20);
    txtInfoCombate.setPosition(50, 50);

    sf::Text txtControles("Presione [A] para Atacar, [B] Especial, [C] Curar", fuente, 18);
    txtControles.setPosition(50, 550);
    txtControles.setFillColor(sf::Color::Green);

   // --- DEFINICIÓN DE TEXTO DE VIDA ---
    sf::Text txtVida;
    txtVida.setFont(fuente);
    txtVida.setCharacterSize(20);
    txtVida.setFillColor(sf::Color::Yellow);
    txtVida.setPosition(30.f, 10.f);

    sf::Text txtVidaEn;
    txtVidaEn.setFont(fuente);
    txtVidaEn.setCharacterSize(20);
    txtVidaEn.setFillColor(sf::Color::Yellow);
    txtVidaEn.setPosition(600.f, 10.f);

    sf::Text txtVic("¡VICTORIA! Nivel 1 Superado.\nPresione ENTER para continuar.", fuente, 30);
    txtVic.setPosition(150, 250);
    txtVic.setFillColor(sf::Color::Green);

    sf::Clock clock;
    bool esperandoContraataque = false;

    // GAME LOOP
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            // --- PROCESAR ENTRADAS DE TECLADO SEGÚN EL ESTADO ---
            if (event.type == sf::Event::KeyPressed) {

                switch (estadoActual) {
                    case MENU_PRINCIPAL:
                        if (event.key.code == sf::Keyboard::Num1) {
                            estadoActual = SELECCION_PERSONAJE;
                        }
                        if (event.key.code == sf::Keyboard::Escape) {
                            window.close();
                        }
                        break;

                    case SELECCION_PERSONAJE:
                        if (event.key.code == sf::Keyboard::G) {
                            heroe = new Guerrero("Guerrero", 150, 20, 10); // Instancia dinámica de Guerrero
                            estadoActual = COMBATE_NIVEL_1;
                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 100, 15, 5, 50);
                            seleccion=0;
                            seleccionEnem = 1;
                        }
                        if (event.key.code == sf::Keyboard::M) {
                            heroe = new Mago("Mago", 120, 30, 5); // Instancia dinámica de Mago
                            estadoActual = COMBATE_NIVEL_1;
                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 135, 15, 5, 50);
                            seleccion=1;
                            seleccionEnem = 1;
                        }

                        break;

                    case COMBATE_NIVEL_1:
                        if (heroe != nullptr && enemigoActual != nullptr){

                            // 1. Manejo de acciones (A, B, C)
                            if (event.type == sf::Event::KeyPressed) {

                                if (event.key.code == sf::Keyboard::A) {
                                    // ATAQUE NORMAL
                                    enemigoActual->recibirDanio(heroe->getAtaque());
                                    if(enemigoActual->estaVivo()) {
                                    esperandoContraataque = true;
                                    clock.restart(); // Iniciamos la cuenta desde cero
                                    txtInfoCombate.setString("Espero el contraataque...");
                                    }else if(enemigoActual->estaVivo()){
                                        heroe->recibirDanio(enemigoActual->getAtaque());
                                        txtInfoCombate.setString("El enemigo te ataco!");
                                    }
                                    else{txtInfoCombate.setString("¡Enemigo derrotado!");
                                        // delay o esperar que el usuario presione una tecla
                                        //estadoActual = VICTORIA_PISO;
                                        //delete enemigoActual;
                                        //enemigoActual = nullptr;
                                    }

                                }
                                else if (event.key.code == sf::Keyboard::B) {
                                    // ATAQUE ESPECIAL (Polimorfismo)
                                heroe->ataqueEspecial(enemigoActual);
                                if(enemigoActual->estaVivo()) {
                                    esperandoContraataque = true;
                                    clock.restart(); // Iniciamos la cuenta desde cero
                                    txtInfoCombate.setString("Espero el contraataque...");
                                }else if(enemigoActual->estaVivo()){
                                    heroe->recibirDanio(enemigoActual->getAtaque());
                                    txtInfoCombate.setString("El enemigo te ataco!");
                                }else{
                                    txtInfoCombate.setString("¡Enemigo derrotado!");
                                }
                                }
                                else if (event.key.code == sf::Keyboard::C) {
                                    // CURACIÓN (Polimorfismo)
                                heroe->curarse();
                                esperandoContraataque = true;
                                clock.restart(); // Iniciamos la cuenta desde cero
                                txtInfoCombate.setString("Espero el contraataque...");
                                heroe->recibirDanio(enemigoActual->getAtaque());
                                }

                                // 3. Verificar condiciones de fin de combate
                                if (!enemigoActual->estaVivo()) {
                                    delete enemigoActual;
                                    enemigoActual = nullptr;

                                    if(seleccionEnem==1){
                                        enemigoActual = new EsqueletoMjr("Esqueleto Mejorado", 145, 20, 5, 50);
                                        seleccionEnem = 2;
                                        txtInfoCombate.setString("¡Aparece un enemigo mas fuerte!");
                                    }
                                    else if (seleccionEnem==2){
                                        enemigoActual = new Golem("Golem de Piedra", 200, 15, 12, 50);
                                        seleccionEnem = 3;
                                    }
                                    else estadoActual = VICTORIA_PISO;
                                }

                                else if (!heroe->estaVivo()) {
                                    estadoActual = GAME_OVER;
                                }
                            }
                        }
                        break;

                    case VICTORIA_PISO:
                        if (event.key.code == sf::Keyboard::Enter) {
                            estadoActual=MENU_PRINCIPAL;
                        }
                        break;
                    case GAME_OVER:
                        if (event.key.code == sf::Keyboard::Enter) {
                            // Reiniciar juego al menú
                            estadoActual = MENU_PRINCIPAL;
//                            if (heroe != nullptr) {
 //                               delete heroe;
 //                               heroe = nullptr;
                        }
                            // Resetear enemigo también acá...

                        break;
                }
            }
        }
        if (esperandoContraataque) {
            if (clock.getElapsedTime().asSeconds() >= 2.0f) {
            // Ya pasaron 2 segundos, el enemigo ataca ahora
            //verifico si no murio
            if(enemigoActual != nullptr){
            heroe->recibirDanio(enemigoActual->getAtaque());
            txtInfoCombate.setString("El enemigo te ataca!");
            }
            esperandoContraataque = false; // Terminó la espera
            }
        }

        // --- ACTUALIZAR LÓGICA DE TEXTOS EN COMBATE ---
 //       if (estadoActual == COMBATE_NIVEL_1 && heroe != nullptr) {
 //           std::string info = "HEROE: Vida " + std::to_string(heroe->getVida()) + "\n\n" +
  //                             "ENEMIGO: " + esqueleto.getNombre() + " | Vida " + std::to_string(esqueleto.getVida());
  //          txtInfoCombate.setString(info);


        // --- RENDERIZADO (DIBUJAR) SEGÚN EL ESTADO ---
        window.clear(sf::Color::Blue); // Fondo gris oscuro

        switch (estadoActual) {
            case MENU_PRINCIPAL:
                window.draw(fondoMenu);
                break;

            case SELECCION_PERSONAJE:
                window.draw(FondoSeleccionP);
                break;

            case COMBATE_NIVEL_1:
                window.draw(fondolv1);

                if(seleccion==1){
                    window.draw(Magobase);
                }else{ window.draw(Guerrerobase);
                }

                if(seleccionEnem ==1){
                window.draw(Esqueleto1_base);
                }
                else if (seleccionEnem == 2) {
                    window.draw(Esqueleto2_base);
                }
                else window.draw(Golem_base);


                window.draw(txtInfoCombate);
                window.draw(txtControles);
                if (heroe != nullptr){
                txtVida.setString("HP Heroe: " + std::to_string(heroe->getVidaActual()));
                window.draw(txtVida);
                }
                if (enemigoActual != nullptr){
                txtVidaEn.setString("HP Enemigo: " + std::to_string(enemigoActual->getVidaActual()));
                window.draw(txtVidaEn);
                }

                break;

            case VICTORIA_PISO:

                window.draw(txtVic);

                break;

            case GAME_OVER:

                sf::Text txtGov("GAME OVER.\nPresione ENTER para reintentar.", fuente, 30);
                txtGov.setPosition(150, 250);
                txtGov.setFillColor(sf::Color::Red);
                window.draw(txtGov);

                break;
        }
        window.display();

    }
    // Limpieza de memoria al cerrar
    if (heroe != nullptr){
        delete heroe;
    }
    return 0;
}


