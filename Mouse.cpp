/**************
*  Mouse.cpp  *
**************/

#include "Mouse.h"

Mouse::Mouse(const char *FILE_NAME, float SOURCE_X, float SOURCE_Y,
              float WIDTH, float HEIGHT)
{
    MouseTexture.loadFromFile(FILE_NAME);
    MouseSprite.setTexture(MouseTexture);
    MouseSprite.setTextureRect(sf::IntRect(SOURCE_X, SOURCE_Y, WIDTH, HEIGHT));
}

bool Mouse::isButtonPressed()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    return false;
}

void Mouse::displayMouse(sf::RenderWindow &WINDOW)
{
    MouseSprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(WINDOW)));
    WINDOW.draw(MouseSprite);
}

Mouse::~Mouse()
{
    //dtor
}
