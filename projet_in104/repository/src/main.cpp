#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdio>
#include <iostream>
#include <cmath>
#include "game.h"
#include "utils.h"
#include <vector>
#include <string>
#include <SFML/Audio.hpp>
#include "pod.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 32;

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!", sf::Style::Default, settings);
    window.setView(sf::View(sf::Rect(0.f,0.f,16000.f,9000.f)));

    //frame per second
    float fps = 60;
    //temps minimal entre deux frame
    sf::Time refreshTime = sf::microseconds(1e6/fps);
    
    sf::Clock clock;
    //horloge depuis le début du jeu
    sf::Clock globalClock;
    //horloge réinitialisée Ã  chaque frame
    sf::Clock refreshClock;

    sf::Text time_txt; 
    time_txt.setCharacterSize(50);
    time_txt.setFillColor(sf::Color::Blue);

    //temps de la physique du jeu
    sf::Time physicsTime = sf::Time::Zero;

    //Vous pouvez aussi initialiser myGame avec une liste de checkpoints prédéfinie
    //On génère aléatoirement les checkpoints
    std::vector<sf::Vector2f> cp = cp_aleatoire(4);
    Game myGame(cp);

    //banane placée en (5000,5000)
    // on pourrait mettre un nombre aléatoire de banane sur des positions aléatoires
    sf::Texture texture_banane;
    texture_banane.loadFromFile("../repository/Images/banane.png");
    sf::Sprite banane;
    banane.setTexture(texture_banane);
    scaleByRadius(banane, 500);
    setOriginToCenter(banane);
    banane.setPosition({5000,5000});

    int j1;
    int j2;
    

    int gameMode = 0;
    
    // la musique ne fonctonne pas
    /*sf::Music music;
    if (!music.openFromFile("../repository/Images/musique.ogg"))
    {
        std::cerr << "Error while loading background music file" << std::endl;
        return -1;
    }
    music.setVolume(50);*/

    while (window.isOpen())
    { 
        sf::Event event;
        if (gameMode == 0)//on est dans le menu
        {
            while(gameMode==0)
            {

                sf::Texture fondTexture;
                fondTexture.loadFromFile("../repository/Images/menu.jpg");  
                sf::Sprite fondSprite;
                fondSprite.setTexture(fondTexture);
                auto rec = fondSprite.getGlobalBounds();
                fondSprite.scale(sf::Vector2f(16000/rec.width, 9000/rec.height));
               

                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                        gameMode=1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
                    {
                        window.close();
                        gameMode=1;
                    }


                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A ))
                    {
                        // 1 joueur en manuel
                        j1 = 0;
                        j2 = 2;
                        gameMode = 1; // on peut jouer
                     }
                       
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B ))
                    {
                        // 1 joueur en manuel et 1 IA
                        j1 = 2;
                        j2 = 3;
                        gameMode = 1;
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::C ))
                    {
                        // 2 joueurs en manuel
                        j1 = 1;
                        j2 = 2;
                        gameMode = 1;
                    }
       
                        
                } 
                window.clear();
                window.draw(fondSprite);
                window.display();
                //music.play();
            }

            myGame.addPod(j1,j2);
        }  
        //music.stop();

        

        if (gameMode == 1)// on est dans le jeu
        {
            while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
                    {
                        window.close();
                    }
                }
            
            float chrono;
            
            
            sf::Text text1;
            sf::Font font;
            if(!font.loadFromFile("/home/ensta/projet_in104/repository/Fredoka-Bold.ttf")){
                printf("error");
            }
            text1.setFont(font);
            text1.setCharacterSize(500);
            text1.setFillColor(sf::Color(255,255,255,200));
            text1.setOutlineThickness(10);
            setTextCenterPosition(text1, 12000, 700);


            //si on a dépassé le refreshTime depuis la dernière frame
            if (refreshClock.getElapsedTime() >= refreshTime)
            {
                //réinitialise l'horloge qui mesure le temps entre les frames
                refreshClock.restart();

                //récupère le temps écoulé depuis le début du jeu
                sf::Time frameTime = globalClock.getElapsedTime();
                //si on a dépassé le temps de la physique
                if (frameTime > physicsTime)
                {
                    //met Ã  jour les sprite au temps de la physique
                    myGame.updateGraphics(physicsTime);
                    //fait avancer la physique d'un pas de temps
                    myGame.updatePhysics();
                    physicsTime += PHYSICS_TIME_STEP;

                    //reprend le temps écoulé depuis le début pour rester précis
                    frameTime = globalClock.getElapsedTime();
                }

                // on recupère le chrono et on le converti en string pour l'afficher
                chrono = frameTime.asSeconds();
                sf::String chronotxt = std::to_string(chrono);
                text1.setString("temps : " + chronotxt);
               

                //met Ã  jour les sprites au temps actuel
                myGame.updateGraphics(frameTime);
                window.clear();
                window.draw(myGame);
                window.draw(banane);
                window.draw(text1);
                window.display();
            }
        }
        
    }

    return 0;
}