/***************
*  Button.cpp  *
***************/

#include "Button.h"

Button::Button()
{
    //ctor
}

void Button::setParams(const char *BUTTON_TEX, float BUTTON_SOURCE_X, float BUTTON_SOURCE_Y,
               float BUTTON_WIDTH, float BUTTON_HEIGHT, const char *SOUND_FILE,
               float MOUSE_OVER_SOURCE_X, float MOUSE_OVER_SOURCE_Y,
               float MOUSE_OVER_WIDTH, float MOUSE_OVER_HEIGHT)
{
    buttonTexture.loadFromFile(BUTTON_TEX);
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setTextureRect(sf::IntRect(BUTTON_SOURCE_X, BUTTON_SOURCE_Y,
               BUTTON_WIDTH, BUTTON_HEIGHT));
    buttonRect.left = BUTTON_SOURCE_X;
    buttonRect.top = BUTTON_SOURCE_Y;
    buttonRect.width = BUTTON_WIDTH;
    buttonRect.height = BUTTON_HEIGHT;
    mouseOver.left = MOUSE_OVER_SOURCE_X;
    mouseOver.top = MOUSE_OVER_SOURCE_Y;
    mouseOver.width = MOUSE_OVER_WIDTH;
    mouseOver.height = MOUSE_OVER_HEIGHT;

    ButtonSoundBuffer.loadFromFile(SOUND_FILE);
    ButtonPressSound.setBuffer(ButtonSoundBuffer);
}

bool Button::isMouseOver(sf::RenderWindow &win)
{
    if(sf::Mouse::getPosition(win).x >=  buttonSprite.getPosition().x &&
         sf::Mouse::getPosition(win).x <=  buttonSprite.getPosition().x + buttonSprite.getGlobalBounds().width &&
           sf::Mouse::getPosition(win).y >=  buttonSprite.getPosition().y &&
             sf::Mouse::getPosition(win).y <=  buttonSprite.getPosition().y + buttonSprite.getGlobalBounds().height)
        return true;
    else
    {
        buttonSprite.setTextureRect(buttonRect);
        return false;
    }
}

void Button::setPosition(float BUTTON_POS_X, float BUTTON_POS_Y)
{
    buttonSprite.setPosition(sf::Vector2f(BUTTON_POS_X, BUTTON_POS_Y));
}

void Button::highlighted()
{
    buttonSprite.setTextureRect(mouseOver);
}

bool Button::mouseClicked()
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return true;
    return false;
}

void Button::playClickSound()
{
    ButtonPressSound.play();
}

void Button::update(sf::RenderWindow &WINDOW)
{
    WINDOW.draw(buttonSprite);
}

Button::~Button()
{
    //dtor
}
