#ifndef INC_UTILS_H
#define INC_UTILS_H

#include <SFML/Graphics.hpp>

// l'origine est par defaut en haut à gauche pas tres pratique
void setOriginToCenter(sf::Sprite &object);     
void setOriginToCenter(sf::Shape &object);

// mettre à la bonne taille en fonction du sprite
void scaleToMinSize(sf::Sprite &sp, double size_x, double size_y);
void scaleToMaxSize(sf::Sprite &sp, double size_x, double size_y);
void scaleByRadius(sf::Sprite &sp, int radius);

// centrer le texte
void setTextCenterPosition(sf::Text &txt, sf::Vector2f center);
void setTextCenterPosition(sf::Text &Sprite, float x, float y);

// calcul de la norme entre deux vecteurs
float norme(sf::Vector2f U, sf::Vector2f C);

// fourni une lise de vecteur aléatoire pour les checkpoints
std::vector<sf::Vector2f> cp_aleatoire(int n);

#endif