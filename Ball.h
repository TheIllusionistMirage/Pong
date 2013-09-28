/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/***********
*  Ball.h  *
***********/

#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Paddle.h"

// declaration of class Ball
class Ball
{
    private:
        sf::CircleShape ballObject;         // object of class CircleShape which acts as a ball
        sf::Vector2<float> currentSpeed;    // stores the cureent speed of the ball
        sf::SoundBuffer paddleHit;          // stores audio file for paddle hit sound
        sf::Sound soundPaddleHit;           // stores sound for paddle hit

    public:

        // default ctor
        Ball();

        // paramerterized ctor to initialize sccording to the user input
        Ball(float RADIUS, sf::Color COLOR, const char *BUFFER_NAME);

        // reset position of ball
        void Init(sf::Vector2f POSITION);

        // reverse the speed of ball along X-direction
        void deflectX();

        // reverse the speed of ball along Y-direction
        void deflectY();

        // play collision sound
        void playHitSound();

        // move the ball
        void move();

        // accelerate the ball according to the collision with player
        void accelerate(Paddle PLAYER);

        // stop moving the ball
        void stopMoving();

        // reset the speed of ball
        void resetSpeed(int sign);

        // detect collision
        bool isColliding(sf::RectangleShape RECTANGLE);
        bool isColliding(sf::FloatRect RECT);

        // get ball position
        sf::Vector2f getBallPosition();

        // get ball radius
        float getBallRadius();

        // update the ball object
        void update(sf::RenderWindow &WINDOW);

        // dctor
        ~Ball();
};

#endif // BALL_H
