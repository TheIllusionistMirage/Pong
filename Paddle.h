/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/*************
*  Paddle.h  *
*************/

#include <SFML/Graphics.hpp>

#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
    private:
        sf::RectangleShape paddleObject;        // stores the paddle as a sf::RectanlgeShape instance

    public:

        // parameterized ctor to initialize as per user's input
        Paddle(int WIDTH, int HEIGHT, sf::Color COLOR);

        // reset paddle position
        void Init(sf::Vector2f POSITION);

        // set paddle position
        void setPosition(sf::Vector2f POSITION);

        // get paddle's rects as a sf::FloatRect
        sf::FloatRect getRect();

        // move the paddle up
        void moveUp(float dt);

        // move the paddle down
        void moveDown(float dt);

        // detect collision
        bool isColliding(sf::RectangleShape RECTANGLE);

        // get paddle's current position
        sf::Vector2f getPaddlePosition();

        // get paddle size
        sf::Vector2f getPaddleSize();

        // update paddle object
        void update(sf::RenderWindow &WINDOW);

        // dctor
        ~Paddle();
};

#endif // PADDLE_H
