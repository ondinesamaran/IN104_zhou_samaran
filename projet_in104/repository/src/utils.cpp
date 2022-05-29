#include "utils.h"
#include <cmath>
#include <cstdlib>
#include <stdlib.h>


void setOriginToCenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void setOriginToCenter(sf::Shape &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2., rect.height/2.);
}

void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::max(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y)
{
    double scalingFactor = std::min(size_x/sp.getTextureRect().width, size_y/sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void scaleByRadius(sf::Sprite &sp, int radius)
{
    double scalingFactor = 2*radius/std::sqrt(sp.getTextureRect().width*sp.getTextureRect().width + sp.getTextureRect().height*sp.getTextureRect().height);
    sp.scale(scalingFactor, scalingFactor);
}

void setTextCenterPosition(sf::Text &txt, sf::Vector2f center)
{
    sf::Vector2f offset;
    offset.x = txt.getPosition().x - txt.getGlobalBounds().left - txt.getGlobalBounds().width/2.;
    offset.y = txt.getPosition().y - txt.getGlobalBounds().top - txt.getGlobalBounds().height/2.;

    txt.setPosition(center + offset);
}

float norme(sf::Vector2f U, sf::Vector2f V)
{
    return std::sqrt(pow(U.x-V.x,2)+pow(U.y-V.y,2));
}

std::vector<sf::Vector2f> cp_aleatoire(int n)
    {
        std::vector<sf::Vector2f> Coord_CP;
        long int nbCP;
    
        nbCP = random()%n + 4; // il y a un nombre de checkpoints choisi aléatoirement entre 4 et 4+n-1
        
    Coord_CP.reserve(nbCP+1);

    Coord_CP.emplace_back(sf::Vector2f(700,700)); // on ajoute le point de départ et d'arrivée
    
    for (int i=1; i<nbCP+1; ++i)
    {
        //srand(7);
        long int x;
        long int y;
        
        x = rand()%14801 + 1000; // x dans [1000,15800]
        y = rand()%7501 + 900; // y dans [900, 8400]
        
    
        //on ajoute les coordonnees du CP
        Coord_CP.emplace_back(sf::Vector2f(x,y));
    }
    return Coord_CP;

    }

void setTextCenterPosition(sf::Text &Sprite, float x, float y){
    sf::FloatRect textRect = Sprite.getLocalBounds();
    Sprite.setOrigin(textRect.left + textRect.width/2.0f,
    textRect.top  + textRect.height/2.0f);
    Sprite.setPosition(x,y);
}

