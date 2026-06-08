#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <iostream>
#include "Personaje.h"
#include "Enemigo.h"
#include "Guerrero.h"
#include "Heroe.h"
#include "Mago.h"
#include "Esqueleto.h"
#include "EsqueletoMjr.h"
#include "Golem.h"

// Definición de estados del juego
enum EstadoJuego {
    MENU_PRINCIPAL,
    SELECCION_PERSONAJE,
    COMBATE_NIVEL_1,
    VICTORIA_PISO,
    GAME_OVER
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "La Torre del Dragon Eterno");
    window.setFramerateLimit(60);

    EstadoJuego estadoActual = MENU_PRINCIPAL;
    Heroe* heroe = nullptr;
    Enemigo* enemigoActual = nullptr;

    bool seleccion; // 0 para Guerrero, 1 para Mago
    int seleccionEnem = 0;
    int cambioDePostura;
    bool turnoJugador = true;
    bool esperandoContraataque = false;
    sf::Clock clock;

    sf::SoundBuffer bufferMusicIntro;
    bufferMusicIntro.loadFromFile("MusicaIntro.wav");
    sf::Sound soundMusicIntro;
    soundMusicIntro.setBuffer(bufferMusicIntro);

    soundMusicIntro.setVolume(7.0f);


    // --- CARGA DE TEXTURAS ---
    sf::Texture texFondoMenu, textFondoSeleccionP, texFondo, texMago, texGuerre, texEsque1eto1, texEsqueleto2, texGolem, texGuerreCurar, texGuerreAtaqueBasico, texGuerreAtaqueFeroz, texMagoAtaqueBasico, texMagoAtaqueFuego,texMagoCuracion;
    sf::Sprite fondoMenu, FondoSeleccionP, fondolv1, Magobase, Guerrerobase, Esqueleto1_base, Esqueleto2_base, Golem_base, guerreroCurar, GuerreroAtaqueBasico,GuerreAtaqueFeroz, MagoAtaqueBasico,MagoAtaqueFuego,MagoCuracion  ;


    texFondoMenu.loadFromFile("FondoMenu.png");
    fondoMenu.setTexture(texFondoMenu);

    textFondoSeleccionP.loadFromFile("SeleccionDePersonaje.png");
    FondoSeleccionP.setTexture(textFondoSeleccionP);

    texFondo.loadFromFile("fondo_nivel1.png");
    fondolv1.setTexture(texFondo);
///============SPRITE DEL MAGO==================
    texMago.loadFromFile("mago_sprite.png");
    Magobase.setTexture(texMago);
    Magobase.setPosition(65.f, 85.f);

    texMagoAtaqueBasico.loadFromFile("MagoAtaqueBasico.png");
    MagoAtaqueBasico.setTexture(texMagoAtaqueBasico);
    MagoAtaqueBasico.setPosition(65.f, 85.f);

    texMagoAtaqueFuego.loadFromFile("MagoAtaqueFuego.png");
    MagoAtaqueFuego.setTexture(texMagoAtaqueFuego);
    MagoAtaqueFuego.setPosition(65.f, 85.f);

    texMagoCuracion.loadFromFile("MagoCuracion.png");
    MagoCuracion.setTexture(texMagoCuracion);
    MagoCuracion.setPosition(65.f, 85.f);
///============SPRITE DE GUERRERO==================
    texGuerre.loadFromFile("Guerrerobase.png");
    Guerrerobase.setTexture(texGuerre);
    Guerrerobase.setPosition(55.f, 85.f);

    texGuerreCurar.loadFromFile("Guerrerocuracion.png");
    guerreroCurar.setTexture(texGuerreCurar);
    guerreroCurar.setPosition(55.f, 85.f);

    texGuerreAtaqueBasico.loadFromFile("GuerreroAtaqueBasico.png");
    GuerreroAtaqueBasico.setTexture(texGuerreAtaqueBasico);
    GuerreroAtaqueBasico.setPosition(55.f, 85.f);

    texGuerreAtaqueFeroz.loadFromFile("GuerreAtaqueFeroz.png");
    GuerreAtaqueFeroz.setTexture(texGuerreAtaqueFeroz);
    GuerreAtaqueFeroz.setPosition(55.f, 85.f);





    texEsque1eto1.loadFromFile("esqueleto1_sprite.png");
    Esqueleto1_base.setTexture(texEsque1eto1);
    Esqueleto1_base.setPosition(550.f, 95.f);

    texEsqueleto2.loadFromFile("esqueletomejoradobase_sprite.png");
    Esqueleto2_base.setTexture(texEsqueleto2);
    Esqueleto2_base.setPosition(450.f, 65.f);

    texGolem.loadFromFile("golemdepiedrabase_sprite.png");
    Golem_base.setTexture(texGolem);
    Golem_base.setPosition(410.f, 65.f);

    // --- CARGA DE FUENTES Y TEXTOS ---
    sf::Font fuente;
    fuente.loadFromFile("arial.ttf");

    sf::Text txtTitulo("LA TORRE DEL DRAGON ETERNO", fuente, 35);
    txtTitulo.setPosition(150, 100);
    txtTitulo.setFillColor(sf::Color::Yellow);

    sf::Text txtInfoCombate("", fuente, 20);
    txtInfoCombate.setPosition(50, 50);

    sf::Text txtControles("Presione [A] para Atacar, [B] Especial, [C] Curar", fuente, 18);
    txtControles.setPosition(50, 550);
    txtControles.setFillColor(sf::Color::Green);

    sf::Text txtVida, txtVidaEn, txtVic;
    txtVida.setFont(fuente); txtVida.setCharacterSize(20);
    txtVida.setFillColor(sf::Color::Yellow);
    txtVida.setPosition(30.f, 10.f);
    txtVidaEn.setFont(fuente);
    txtVidaEn.setCharacterSize(20);
    txtVidaEn.setFillColor(sf::Color::Yellow);
    txtVidaEn.setPosition(600.f, 10.f);

    sf::Text txtEnergia;
    txtEnergia.setFont(fuente);
    txtEnergia.setCharacterSize(18);
    txtEnergia.setFillColor(sf::Color::Cyan); // Azul para Mana, o Verde para Estamina
    txtEnergia.setPosition(30.f, 35.f);

    sf::Text txtCuraciones;
    txtCuraciones.setFont(fuente);
    txtCuraciones.setCharacterSize(18);
    txtCuraciones.setFillColor(sf::Color::White);
    txtCuraciones.setPosition(30.f, 60.f);

    txtVic.setFont(fuente);
    txtVic.setCharacterSize(30);
    txtVic.setFillColor(sf::Color::Green);
    txtVic.setPosition(150, 250);
    txtVic.setString("¡VICTORIA! Nivel 1 Superado.\nPresione ENTER para continuar.");

     soundMusicIntro.play();
    // GAME LOOP
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (estadoActual) {
                    case MENU_PRINCIPAL:


                        if (event.key.code == sf::Keyboard::Num1) estadoActual = SELECCION_PERSONAJE;
                        if (event.key.code == sf::Keyboard::Escape) window.close();
                        break;

                    case SELECCION_PERSONAJE:
                            soundMusicIntro.stop();
                            if (event.key.code == sf::Keyboard::G) {
                            heroe = new Guerrero("Guerrero", 150, 25, 10, 100);
                            seleccion = 0; estadoActual = COMBATE_NIVEL_1;
                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 100, 15, 5, 50);
                            seleccionEnem = 1;
                        } else if (event.key.code == sf::Keyboard::M) {
                            heroe = new Mago("Mago", 120, 18, 5, 120);
                            seleccion = 1; estadoActual = COMBATE_NIVEL_1;
                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 135, 15, 5, 50);
                            seleccionEnem = 1;
                        }
                        break;

                    case COMBATE_NIVEL_1:

                        if (heroe && enemigoActual && turnoJugador) {

                            bool accionRealizada = false;
                            cambioDePostura = 0;
                            if (event.key.code == sf::Keyboard::A){
                                    enemigoActual->recibirDanio(heroe->getAtaque());
                                    // Ataque básico recupera un poco de energía
                                    heroe->recuperarEnergia(10);
                                    txtInfoCombate.setString("Atacaste al enemigo.");
                                    accionRealizada = true;
                                    cambioDePostura = 1;

                            }else if (event.key.code == sf::Keyboard::B){
                                // Validamos si tiene suficiente energía (ejemplo: requiere 30)
                                if (heroe->getEnergia() >= 30) {
                                    heroe->ataqueEspecial(enemigoActual);
                                    heroe->gastarEnergia(30);
                                    txtInfoCombate.setString("Ataque Especial!");
                                    accionRealizada = true;
                                    cambioDePostura = 2;
                                }else{
                                    txtInfoCombate.setString("¡Energia insuficiente!");
                                    accionRealizada = false; // No consumimos turno si no puede atacar
                                }
                            }else if (event.key.code == sf::Keyboard::C){
                                    if(heroe->getCuracionesRestantes() > 0){
                                        heroe->curarse();
                                        heroe->usarCuracion();//restamos curaciones
                                        // Curarse también recupera energía
                                        heroe->recuperarEnergia(15);
                                        txtInfoCombate.setString("Te curaste!");
                                        accionRealizada = true;
                                        cambioDePostura = 3;
                                    }else {
                                        txtInfoCombate.setString("¡No quedan curaciones");
                                        accionRealizada=false;
                                    }
                                }
                            if (accionRealizada){
                                turnoJugador = false;
                                if (!enemigoActual->estaVivo())  {
                                    delete enemigoActual;
                                    if (seleccionEnem == 1) {
                                            enemigoActual = new EsqueletoMjr("Esqueleto Mejorado", 145, 20, 5, 50);
                                    seleccionEnem = 2;
                                    txtInfoCombate.setString("¡Aparece un enemigo mas fuerte!");
                                    turnoJugador = true; }
                                    else if (seleccionEnem == 2) {
                                            enemigoActual = new Golem("Golem de Piedra", 200, 15, 12, 50);
                                    seleccionEnem = 3;
                                    txtInfoCombate.setString("¡Un Golem bloquea el paso!");
                                    turnoJugador = true; }
                                    else { estadoActual = VICTORIA_PISO; turnoJugador = true; }
                                } else {
                                    esperandoContraataque = true;
                                    clock.restart();
                                    txtInfoCombate.setString("Espero el contraataque...");
                                }
                            }
                        }
                        break;
                    case VICTORIA_PISO:
                        if (event.key.code == sf::Keyboard::Enter) estadoActual = MENU_PRINCIPAL;
                        break;
                    case GAME_OVER:
                        if (event.key.code == sf::Keyboard::Enter) estadoActual = MENU_PRINCIPAL;
                        break;
                }
            }
        }


        if (esperandoContraataque && clock.getElapsedTime().asSeconds() >= 2.0f) {
            if (enemigoActual) {
                heroe->recibirDanio(enemigoActual->getAtaque());
                // El simple hecho de sobrevivir al turno recupera un poco de energia
                //heroe->recuperarEnergia(5);
                txtInfoCombate.setString("El enemigo te ataca!");
            }
            esperandoContraataque = false;
            turnoJugador = true;
        }

        if (heroe && !heroe->estaVivo()) estadoActual = GAME_OVER;

        // RENDERIZADO
        window.clear(sf::Color::Black);
        switch (estadoActual) {
            case MENU_PRINCIPAL: window.draw(fondoMenu);


                break;
            case SELECCION_PERSONAJE:
                 window.draw(FondoSeleccionP);

                break;
            case COMBATE_NIVEL_1:
                window.draw(fondolv1);
                if (seleccion == 1) {
                     if(cambioDePostura == 0){
                        window.draw(Magobase);
                   }
                    else if(cambioDePostura == 1){
                        window.draw(MagoAtaqueBasico);
                    }else if (cambioDePostura == 2){
                        window.draw(MagoAtaqueFuego);
                    }else if(cambioDePostura == 3){
                        window.draw(MagoCuracion);
                    }
                } else {
                   if(cambioDePostura == 0){
                        window.draw(Guerrerobase);
                   }
                    else if(cambioDePostura == 1){
                        window.draw(GuerreroAtaqueBasico);
                    }else if (cambioDePostura == 2){
                        window.draw(GuerreAtaqueFeroz);
                    }else if(cambioDePostura == 3){
                        window.draw(guerreroCurar);
                    }
                }


                if (heroe) {
                    std::string nombreEnergia;

                    // Si seleccion es 1 (Mago), el nombre es "Mana", si no, es "Estamina"
                    if (seleccion == 1) {
                        nombreEnergia = "Mana: ";
                    } else {
                        nombreEnergia = "Estamina: ";
                    }

                    txtEnergia.setString(nombreEnergia + std::to_string(heroe->getEnergia()));
                    window.draw(txtEnergia);
                    txtCuraciones.setString("Curaciones: " + std::to_string(heroe->getCuracionesRestantes()) + "/5");
                    window.draw(txtCuraciones);
                }

                if (seleccionEnem == 1) window.draw(Esqueleto1_base);
                else if (seleccionEnem == 2) window.draw(Esqueleto2_base);
                else window.draw(Golem_base);
                window.draw(txtInfoCombate);
                window.draw(txtControles);
                if (heroe) { txtVida.setString("HP Heroe: " + std::to_string(heroe->getVidaActual()));
                    window.draw(txtVida);
                }
                if (enemigoActual) {
                    txtVidaEn.setString("HP Enemigo: " + std::to_string(enemigoActual->getVidaActual()));
                    window.draw(txtVidaEn);
                }




                break;
            case VICTORIA_PISO: window.draw(txtVic); break;
            case GAME_OVER:
                sf::Text txtGov("GAME OVER.\nPresione ENTER para reintentar.", fuente, 30);
                txtGov.setPosition(150, 250); txtGov.setFillColor(sf::Color::Red);
                window.draw(txtGov); break;
        }
        window.display();
    }
    if (heroe) delete heroe;
    return 0;
}
