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
#include "MagoOscuro.h"
#include "GolemOscuro.h"
#include "SeguidordelVillano.h"

// Definición de estados del juego
enum EstadoJuego {
    MENU_PRINCIPAL,
    HISTORIA_1, // Imagen 1
    HISTORIA_2, // Imagen 2
    HISTORIA_3, // Imagen 3
    SELECCION_PERSONAJE,
    HISTORIA_GUERRERO, // Pantalla tras elegir Guerrero
    HISTORIA_MAGO,     // Pantalla tras elegir Mago
    COMBATE_NIVEL_1,
    COMBATE_NIVEL_2,
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

    /*sf::SoundBuffer bufferMusicIntro;
    bufferMusicIntro.loadFromFile("MusicaIntro.wav");
    sf::Music soundMusicIntro;
    soundMusicIntro.setBuffer(bufferMusicIntro);

    soundMusicIntro.setVolume(20.0f);*/
    sf::Music musicaFondo; // Cambiamos Sound por Music
    if (!musicaFondo.openFromFile("MusicaIntro.wav")) {
        std::cout << "Error: No se pudo cargar la música" << std::endl;
    }
    musicaFondo.setLoop(true); // Para que la intro se repita
    musicaFondo.setVolume(80.0f);


    /// ------------------ DECLARACION DE TEXTURAS Y SPRITES ------------------

    /// ----- DECLARACION DE TEXTURAS FONDOS -----

    sf::Texture texFondoMenu;
    sf::Texture textFondoSeleccionP;
    sf::Texture texFondo, texFondo2;
    sf::Texture texFondoVicPiso;
    sf::Texture texHist1, texHist2, texHist3, texHistGuerrero, texHistMago;

    /// ----- DECLARACION DE SPRITES FONDOS -----

    sf::Sprite fondoMenu;
    sf::Sprite FondoSeleccionP;
    sf::Sprite fondolv1, fondolvl2;
    sf::Sprite fondoVicPiso;
    sf::Sprite sprHist1, sprHist2, sprHist3, sprHistGuerrero, sprHistMago;

    /// ----- DECLARACION DE TEXTURAS HEROES -----

    sf::Texture texMago, texMagoAtaqueBasico, texMagoAtaqueFuego, texMagoCuracion;
    sf::Texture texGuerre, texGuerreCurar, texGuerreAtaqueBasico, texGuerreAtaqueFeroz;

    /// ----- DECLARACION DE SPRITES HEROES -----

    sf::Sprite Magobase, MagoAtaqueBasico, MagoAtaqueFuego, MagoCuracion;
    sf::Sprite Guerrerobase, guerreroCurar, GuerreroAtaqueBasico,GuerreAtaqueFeroz;

    /// ----- DECLARACION DE TEXTURAS ENEMIGOS -----

    sf::Texture texGolem2,texSeguidorDelvillano, texEsque1eto1, texEsqueleto2, texGolem, texMagoOscuro;

    /// ----- DECLARACION DE SPRITES ENEMIGOS -----

    sf::Sprite seguidorDelVillano, Golem_base2, Esqueleto1_base, Esqueleto2_base, Golem_base, Mago_Oscuro;

    /// ----- DECLARACION DE TEXTURAS HUD -----

    sf::Texture tex5posiones, tex4posiones, tex3posiones, tex2posiones, tex1posiones, tex0posiones;

    /// ----- DECLARACION DE SPRITES HUD -----

    sf::Sprite posiones5, posiones4, posiones3, posiones2, posiones1, posiones0;



    texFondoMenu.loadFromFile("FondoMenu.png");
    fondoMenu.setTexture(texFondoMenu);

    textFondoSeleccionP.loadFromFile("SeleccionDePersonaje.png");
    FondoSeleccionP.setTexture(textFondoSeleccionP);

    texFondo.loadFromFile("fondo_nivel1.png");
    fondolv1.setTexture(texFondo);

    texFondo2.loadFromFile("fondo_nivel2.png");
    fondolvl2.setTexture(texFondo2);

    texFondoVicPiso.loadFromFile ("Victoriadepiso.png");
    fondoVicPiso.setTexture(texFondoVicPiso);

    texHist1.loadFromFile("historia1.png");
    sprHist1.setTexture(texHist1);
    texHist2.loadFromFile("historia2.png");
    sprHist2.setTexture(texHist2);
    texHist3.loadFromFile("historia3.png");
    sprHist3.setTexture(texHist3);
    texHistGuerrero.loadFromFile("historiadelguerrero.png");
    sprHistGuerrero.setTexture(texHistGuerrero);
    texHistMago.loadFromFile("historiadelmago.png");
    sprHistMago.setTexture(texHistMago);


///================SPRITE DEL MAGO===================
    texMago.loadFromFile("mago_sprite.png");
    Magobase.setTexture(texMago);
    Magobase.setPosition(65.f, 85.f);

    texMagoAtaqueBasico.loadFromFile("MagoAtaqueBasico.png");
    MagoAtaqueBasico.setTexture(texMagoAtaqueBasico);
    MagoAtaqueBasico.setPosition(65.f, 105.f);

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
    GuerreroAtaqueBasico.setPosition(55.f, 55.f);

    texGuerreAtaqueFeroz.loadFromFile("GuerreroAtaqueFeroz.png");
    GuerreAtaqueFeroz.setTexture(texGuerreAtaqueFeroz);
    GuerreAtaqueFeroz.setPosition(65.f, 10.f);


///============SPRITE DE ENEMIGOS==================

    texEsque1eto1.loadFromFile("esqueleto1_sprite.png");
    Esqueleto1_base.setTexture(texEsque1eto1);
    Esqueleto1_base.setPosition(550.f, 95.f);

    texEsqueleto2.loadFromFile("esqueletomejoradobase_sprite.png");
    Esqueleto2_base.setTexture(texEsqueleto2);
    Esqueleto2_base.setPosition(450.f, 65.f);

    texGolem.loadFromFile("golemdepiedrabase_sprite.png");
    Golem_base.setTexture(texGolem);
    Golem_base.setPosition(410.f, 65.f);

    texSeguidorDelvillano.loadFromFile("SeguidorDelVillano.png");
    seguidorDelVillano.setTexture(texSeguidorDelvillano);
    seguidorDelVillano.setPosition(450.f, 65.f);

    texGolem2.loadFromFile("golemDePIedralvl2.png");
    Golem_base2.setTexture(texGolem2);
    Golem_base2.setPosition(410.f, 65.f);

    texMagoOscuro.loadFromFile("MagoOscuro.png");
    Mago_Oscuro.setTexture(texMagoOscuro);
    Mago_Oscuro.setPosition(450.f,65.f);

///============SPRITE DEL HUD==================

    tex5posiones.loadFromFile("5posiones.png");
    posiones5.setTexture(tex5posiones);
    posiones5.setPosition(230.f,-10.f);

    tex4posiones.loadFromFile("4posiones.png");
    posiones4.setTexture(tex4posiones);
    posiones4.setPosition(230.f,-10.f);

    tex3posiones.loadFromFile("3posiones.png");
    posiones3.setTexture(tex3posiones);
    posiones3.setPosition(230.f,-10.f);

    tex2posiones.loadFromFile("2posiones.png");
    posiones2.setTexture(tex2posiones);
    posiones2.setPosition(230.f,-10.f);

    tex1posiones.loadFromFile("1posion.png");
    posiones1.setTexture(tex1posiones);
    posiones1.setPosition(230.f,-10.f);

    tex0posiones.loadFromFile("0posiones.png");
    posiones0.setTexture(tex0posiones);
    posiones0.setPosition(230.f,-10.f);





    // --- CARGA DE FUENTES Y TEXTOS ---
    sf::Font fuente;
    fuente.loadFromFile("arial.ttf");

    sf::Text txtTitulo("LA TORRE DEL DRAGON ETERNO", fuente, 35);
    txtTitulo.setPosition(150, 100);
    txtTitulo.setFillColor(sf::Color::Yellow);

    sf::Text txtInfoCombate("", fuente, 20);
    txtInfoCombate.setPosition(80, 60);

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
    txtEnergia.setCharacterSize(20);
    txtEnergia.setFillColor(sf::Color::Cyan); // Azul para Mana, o Verde para Estamina
    txtEnergia.setPosition(30.f, 35.f);

    sf::Text txtCuraciones;
    txtCuraciones.setFont(fuente);
    txtCuraciones.setCharacterSize(20);
    txtCuraciones.setFillColor(sf::Color::White);
    txtCuraciones.setPosition(200.f, 12.f);

    txtVic.setFont(fuente);
    txtVic.setCharacterSize(30);
    txtVic.setFillColor(sf::Color::Green);
    txtVic.setPosition(150, 250);
    txtVic.setString("¡VICTORIA! Nivel 1 Superado.\nPresione ENTER para continuar.");

     musicaFondo.play();
    // GAME LOOP
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (estadoActual) {
                    case MENU_PRINCIPAL:


                        if (event.key.code == sf::Keyboard::Num1) estadoActual = HISTORIA_1;
                        if (event.key.code == sf::Keyboard::Escape) window.close();
                        break;
                    case HISTORIA_1:
                        if (event.key.code == sf::Keyboard::Enter) estadoActual = HISTORIA_2;
                        break;
                    case HISTORIA_2:
                        if (event.key.code == sf::Keyboard::Enter) estadoActual = HISTORIA_3;
                        break;
                    case HISTORIA_3:
                        if (event.key.code == sf::Keyboard::Enter) estadoActual = SELECCION_PERSONAJE;
                        break;
                    case SELECCION_PERSONAJE:
                            if (event.key.code == sf::Keyboard::G) {
                            heroe = new Guerrero("Guerrero", 170, 20, 8, 100);
                            seleccion = 0;
                            estadoActual = HISTORIA_GUERRERO;

                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 100, 15, 5, 50);
                            seleccionEnem = 1;
                        } else if (event.key.code == sf::Keyboard::M) {
                            heroe = new Mago("Mago", 150, 15, 5, 140);
                            seleccion = 1;
                            estadoActual = HISTORIA_MAGO;
                            enemigoActual = new Esqueleto("Esqueleto Nivel 1", 100, 15, 5, 50);
                            seleccionEnem = 1;
                        }
                        break;
                    case HISTORIA_GUERRERO:
                            if (event.key.code == sf::Keyboard::Enter) estadoActual = COMBATE_NIVEL_1;
                            musicaFondo.stop();
                        break;

                    case HISTORIA_MAGO:
                            if (event.key.code == sf::Keyboard::Enter) estadoActual = COMBATE_NIVEL_1;
                            musicaFondo.stop();
                        break;

                    case COMBATE_NIVEL_1:

                        if (heroe && enemigoActual && turnoJugador) {

                            bool accionRealizada = false;
                            cambioDePostura = 0;
                            if (event.key.code == sf::Keyboard::A){
                                    enemigoActual->recibirDanio(heroe->getAtaque());
                                // Asignación de energía por ataque básico
                                    int ganancia = 10;//si es guerrero
                                    if (seleccion == 1) { // Si es mago
                                        ganancia = 20;
                                    }
                                    heroe->recuperarEnergia(ganancia);
                                    txtInfoCombate.setString("Atacaste! (Energia +" + std::to_string(ganancia) + ")");
                                    accionRealizada = true;
                                    cambioDePostura = 1;
                                    clock.restart();

                            }else if (event.key.code == sf::Keyboard::B){
                                // Definimos el costo según el tipo de personaje
                                int costo = 30; // Costo por defecto (Mago)
                                if (seleccion == 0) { // Si es Guerrero
                                    costo = 40;
                                }

                                // Validamos si tiene suficiente energía
                                if (heroe->getEnergia() >= costo) {
                                    heroe->ataqueEspecial(enemigoActual);
                                    heroe->gastarEnergia(costo);
                                    txtInfoCombate.setString("¡Ataque Especial!");
                                    accionRealizada = true;
                                    cambioDePostura = 2;
                                    clock.restart();
                                }else{
                                    txtInfoCombate.setString("¡Energia insuficiente!");
                                    accionRealizada = false; // No consumimos turno si no puede atacar
                                }
                            }else if (event.key.code == sf::Keyboard::C){
                                    if(heroe->getCuracionesRestantes() > 0){
                                        heroe->curarse();
                                        heroe->usarCuracion();//restamos curaciones
                                        // Curarse también recupera energía
                                        //heroe->recuperarEnergia(15);
                                        txtInfoCombate.setString("Te curaste!");
                                        //accionRealizada = true;
                                        //turnoJugador = true;
                                        cambioDePostura = 3;
                                        clock.restart();
                                    }else {
                                        txtInfoCombate.setString("¡No quedan curaciones");
                                        accionRealizada=false;
                                    }
                                }
                            if (accionRealizada){
                                turnoJugador = false;
                                if (!enemigoActual->estaVivo())  {
                                    delete enemigoActual;
                                    enemigoActual = nullptr;
                                    esperandoContraataque = false;
                                    if (seleccionEnem == 1) {
                                            enemigoActual = new EsqueletoMjr("Esqueleto Mejorado", 145, 20, 5, 50);
                                    seleccionEnem = 2;
                                    txtInfoCombate.setString("¡Aparece un enemigo mas fuerte!");
                                    turnoJugador = true; }
                                    else if (seleccionEnem == 2) {
                                            enemigoActual = new Golem("Golem de Piedra", 200, 15, 8, 50);
                                    seleccionEnem = 3;
                                    txtInfoCombate.setString("¡Un Golem bloquea el paso!");
                                    turnoJugador = true; }
                                    else { estadoActual = VICTORIA_PISO; turnoJugador = true;}
                                } else {
                                    esperandoContraataque = true;
                                    clock.restart();
                                    txtInfoCombate.setString("Espero el contraataque...");
                                }


                            }
                        }
                        break;

                    case VICTORIA_PISO:
                        if (event.key.code == sf::Keyboard::Enter)
                        {
                                         // Borramos el enemigo anterior si quedó alguno
                            if (enemigoActual != nullptr) {
                                delete enemigoActual;
                                enemigoActual = nullptr;
                            }
                            //transicion a nivel 2
                            heroe->subirNivel(); //restauramos todo e incremento stats
                            turnoJugador = true; // El jugador siempre empieza
                            esperandoContraataque = false;// Limpiamos estados viejos
                            cambioDePostura = 0;
                            clock.restart();
                            // Creamos el primer enemigo del Nivel 2
                            enemigoActual = new SeguidordelVillano("Seguidor del Villano", 140, 18, 7, 50);
                            seleccionEnem = 1; // Reseteamos al índice del primer enemigo del Nivel 2
                            estadoActual = COMBATE_NIVEL_2;

                        }
                        break;



///=================================================================================================================
                    case COMBATE_NIVEL_2:

                        if (heroe && enemigoActual && turnoJugador) {

                            bool accionRealizada = false;
                            cambioDePostura = 0;
                            if (event.key.code == sf::Keyboard::A){
                                    enemigoActual->recibirDanio(heroe->getAtaque());
                                   // Asignación de energía por ataque básico
                                    int ganancia = 12;//si es guerrero
                                    if (seleccion == 1) { // Si es mago
                                        ganancia = 22;
                                    }
                                    heroe->recuperarEnergia(ganancia);
                                    txtInfoCombate.setString("Atacaste! (Energia +" + std::to_string(ganancia) + ")");
                                    accionRealizada = true;
                                    cambioDePostura = 1;
                                    clock.restart();
                            }else if (event.key.code == sf::Keyboard::B){
                                // Definimos el costo según el tipo de personaje
                                int costo = 30; // Costo por defecto (Mago)
                                if (seleccion == 0) { // Si es Guerrero
                                    costo = 40;
                                }

                                // Validamos si tiene suficiente energía
                                if (heroe->getEnergia() >= costo) {
                                    heroe->ataqueEspecial(enemigoActual);
                                    heroe->gastarEnergia(costo);
                                    txtInfoCombate.setString("¡Ataque Especial!");
                                    accionRealizada = true;
                                    cambioDePostura = 2;
                                    clock.restart();
                                }else{
                                    txtInfoCombate.setString("¡Energia insuficiente!");
                                    accionRealizada = false; // No consumimos turno si no puede atacar
                                }
                            }else if (event.key.code == sf::Keyboard::C){
                                    if(heroe->getCuracionesRestantes() > 0){
                                        heroe->curarse();
                                        heroe->usarCuracion();//restamos curaciones
                                        // Curarse también recupera energía
                                        //heroe->recuperarEnergia(15);
                                        txtInfoCombate.setString("Te curaste!");
                                        //accionRealizada = true;
                                        //turnoJugador = true;
                                        cambioDePostura = 3;
                                        clock.restart();
                                    }else {
                                        txtInfoCombate.setString("¡No quedan curaciones");
                                        accionRealizada=false;
                                    }
                                }
                            if (accionRealizada){
                                turnoJugador = false;

                                if (!enemigoActual->estaVivo())  {
                                    delete enemigoActual;
                                    enemigoActual = nullptr;
                                    esperandoContraataque = false;
                                    if (seleccionEnem == 1) {
                                            enemigoActual = new GolemOscuro("Golem Oscuro", 240, 18, 14, 50);
                                    seleccionEnem = 2;
                                    txtInfoCombate.setString("¡Aparece un enemigo mas fuerte!");
                                    turnoJugador = true; }
                                    else if (seleccionEnem == 2) {
                                            enemigoActual = new MagoOscuro("Mago Oscuro", 172, 22, 12, 50);
                                    seleccionEnem = 3;
                                    txtInfoCombate.setString("¡Aparece un Mago Oscuro!");
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

                    case GAME_OVER:
                        if (event.key.code == sf::Keyboard::Enter) {

                            if (heroe != nullptr) {
                                delete heroe;
                                heroe = nullptr;
                            }

                            if (enemigoActual != nullptr) {
                                delete enemigoActual;
                                enemigoActual = nullptr;
                            }

                            turnoJugador = true;
                            esperandoContraataque = false;

                            estadoActual = MENU_PRINCIPAL;
                        }
                        break;
                }
            }
        }
        if (esperandoContraataque && clock.getElapsedTime().asSeconds() >= 2.0f) {
            if (enemigoActual!=nullptr) {
                heroe->recibirDanio(enemigoActual->getAtaque());
                // El simple hecho de sobrevivir al turno recupera un poco de energia
                //heroe->recuperarEnergia(5);
                txtInfoCombate.setString("El enemigo te ataca!");
                esperandoContraataque = false;
                turnoJugador = true;
            }else {esperandoContraataque = false;}

        }

        // Si cambioDePostura es distinto de 0 (está atacando o curando)
        // y pasó medio segundo, lo devolvemos a la pose base (0)
        if (cambioDePostura != 0 && clock.getElapsedTime().asSeconds() >= 1.0f) {
            cambioDePostura = 0;
        }


        if (heroe && !heroe->estaVivo()) estadoActual = GAME_OVER;

        // RENDERIZADO
        window.clear(sf::Color::Black);
        switch (estadoActual) {
            case MENU_PRINCIPAL: window.draw(fondoMenu);

                break;
            case HISTORIA_1: window.draw(sprHist1);
                break;
            case HISTORIA_2: window.draw(sprHist2);
                break;
            case HISTORIA_3: window.draw(sprHist3);
                break;
            case SELECCION_PERSONAJE:
                 window.draw(FondoSeleccionP);

                break;
            case HISTORIA_GUERRERO: window.draw(sprHistGuerrero);
                break;
            case HISTORIA_MAGO: window.draw(sprHistMago);
                break;
///======================================================
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

                    if (heroe->getCuracionesRestantes() == 5)
                    {
                    window.draw(posiones5);
                    }
                        else if (heroe->getCuracionesRestantes() == 4)
                        {
                            window.draw(posiones4);

                            }else if (heroe->getCuracionesRestantes() == 3)
                            {
                                window.draw(posiones3);

                                }else if (heroe->getCuracionesRestantes() == 2)
                                {
                                    window.draw(posiones2);

                                    }else if (heroe->getCuracionesRestantes() == 1)
                                    {
                                        window.draw(posiones1);

                                        }else if (heroe->getCuracionesRestantes() == 0)
                                        {
                                            window.draw(posiones0);

                                            }
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
///======================================================
            case COMBATE_NIVEL_2:
                window.draw(fondolvl2);
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

                    /*void dibujarPociones(sf::RenderWindow& window, int cantidad, sf::Sprite sprites[]) {
                        if(cantidad >= 0 && cantidad <= 5) {
                            window.draw(sprites[cantidad]);
                        }
                    }*/
                    if (heroe->getCuracionesRestantes() == 5)
                    {
                    window.draw(posiones5);
                    }
                        else if (heroe->getCuracionesRestantes() == 4)
                        {
                            window.draw(posiones4);

                            }else if (heroe->getCuracionesRestantes() == 3)
                            {
                                window.draw(posiones3);

                                }else if (heroe->getCuracionesRestantes() == 2)
                                {
                                    window.draw(posiones2);

                                    }else if (heroe->getCuracionesRestantes() == 1)
                                    {
                                        window.draw(posiones1);

                                        }else if (heroe->getCuracionesRestantes() == 0)
                                        {
                                            window.draw(posiones0);

                                            }
                }

                if (seleccionEnem == 1){ window.draw(seguidorDelVillano);
                }else if (seleccionEnem == 2){ window.draw(Golem_base2);
                } else window.draw(Mago_Oscuro);
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
            case VICTORIA_PISO: window.draw(fondoVicPiso);
                break;
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
