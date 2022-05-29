#ifndef INC_ORIGINE_H
#define INC_ORIGINE_H

#include <SFML/Graphics.hpp>

/*void setorigintocenter(sf::Sprite &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2.,rect.height/2.);
}
*/

template<class T>
void setorigintocenter(T &object)
{
    auto rect = object.getGlobalBounds();
    object.setOrigin(rect.width/2.,rect.height/2.);
}

#endif
