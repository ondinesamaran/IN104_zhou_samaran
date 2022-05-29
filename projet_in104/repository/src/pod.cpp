#include<cmath>
#include "pod.h"
#include "game.h"
#include "checkpoint.h"
#include <SFML/System/Vector2.hpp>

Decision::Decision(sf::Vector2f target, float power) : target_(target), power_(power)
{
    
};

Pod::Pod(sf::Vector2f pos, float angle, sf::Vector2f vel) : pos_(pos), vel_(vel), angle_(angle)
{

};
int initialisation = 1;
int vitesse = 50;
Decision Pod::getDecision(GameInfos gameInfos ) const 
{

    int IA ;
    int manuelflèche ;
    int manueltouche ; 

    if(mode==0){
        IA = 0;
        manuelflèche = 0;
        manueltouche = 0;
    }
    else if(mode==1){
        IA = 1;
        manuelflèche = 0;
        manueltouche = 0;
    }
    else if (mode==2){
        IA = 0;
        manuelflèche = 1;
        manueltouche = 0;
    }
    else {
        IA = 0;
        manuelflèche = 0;
        manueltouche = 1;
    }

    int droite = 0;
    int gauche = 0;
    int haut = 0;
    int bas = 0;

    int d = 0;
    int q = 0;
    int z = 0;
    int s = 0;
    
    //mnuelfleche
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                droite = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                gauche = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                haut = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                bas = 1;
            }


    //manueltouche
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                d = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                q = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            {
                z = 1;
            }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                s = 1;
            }
    

    sf::Vector2f position ;      
    if (manuelflèche == 1)
   {
        if(initialisation==1)
        {
        position = gameInfos.cpPositions[0];
        if(nextCP_!=0){initialisation=0;}
        return Decision(position,10);
        }
        position.x=pos_.x;
        position.y=pos_.y;
        
        // si on appuie sur une touche pour déplacer on met à jour
        if(droite==1||gauche==1||haut==1||bas==1){
        position.x = pos_.x +10*(droite-gauche);
        position.y = pos_.y +10*(bas-haut);
        vitesse = 100;
        }
        // si on n'appuie pas on décélère progressivement 
        else {
        position.x=pos_.x;
        position.y=pos_.y;
        vitesse = vitesse-10;
        }
        return Decision(position,vitesse);
   }

   if (manueltouche == 1)
   {
        if(initialisation==1)
        {
        position = gameInfos.cpPositions[0];
        if(nextCP_!=0){initialisation=0;}
        return Decision(position,10);
        }
        position.x=pos_.x;
        position.y=pos_.y;
        
        if(d==1||q==1||z==1||s==1){
        position.x = pos_.x +10*(d-q);
        position.y = pos_.y +10*(s-z);
        vitesse = 100;
        }
        else {
        position.x=pos_.x;
        position.y=pos_.y;
        vitesse = vitesse-10;
        }
        return Decision(position,vitesse);

   }

   if (IA == 1)
    {
    position = gameInfos.cpPositions[nextCP_];
    return Decision(position,100);
    }
    

    
};