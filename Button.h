/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/*************
*  Button.h  *
*************/

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Button
{
    private:
        sf::Texture buttonTexture;          // stores the button texture
        sf::Sprite buttonSprite;            // stores the button sprite
        sf::IntRect buttonRect;             // stores texture rect for button's sprite
        sf::SoundBuffer ButtonSoundBuffer;  // stores the audio file for button press
        sf::Sound ButtonPressSound;         // stores the sound for button press
        sf::IntRect mouseOver;              // stores texture rect when mouse is over button

    public:

        // default ctor
        Button();

        // initialize sccording to the user input
        void setParams(const char *BUTTON_TEX, float BUTTON_SOURCE_X, float BUTTON_SOURCE_Y,
               float BUTTON_WIDTH, float BUTTON_HEIGHT, const char *SOUND_FILE,
               float MOUSE_OVER_SOURCE_X, float MOUSE_OVER_SOURCE_Y,
               float MOUSE_OVER_WIDTH, float MOUSE_OVER_HEIGHT);

        // detect if mouse is over button
        bool isMouseOver(sf::RenderWindow &win);

        // set button position
        void setPosition(float BUTTON_POS_X, float BUTTON_POS_Y);

        // change button's texture rect if mouse is over button
        void highlighted();

        // detect mouse click
        bool mouseClicked();

        // play button play sound
        void playClickSound();

        // update button object
        void update(sf::RenderWindow &WINDOW);

        // dctor
        ~Button();
};

#endif // BUTTON_H
