/************
*  Mouse.h  *
************/

#ifndef MOUSE_H
#define MOUSE_H

#include <SFML/Graphics.hpp>

class Mouse
{
    private:
        sf::Texture MouseTexture;       // stores the mouse texture
        sf::Sprite MouseSprite;         // stores the mouse sprite

    public:

        // parameterized ctor to initialze as per as user's input
        Mouse(const char *FILE_NAME, float SOURCE_X, float SOURCE_Y,
              float WIDTH, float HEIGHT);

        // detect mouse button press
        bool isButtonPressed();

        // display mouse pointer
        void displayMouse(sf::RenderWindow &WINDOW);

        // dctor
        ~Mouse();
};

#endif // MOUSE_H
