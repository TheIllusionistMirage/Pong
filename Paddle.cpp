/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/***************
*  Paddle.cpp  *
***************/

#include "Paddle.h"

const int PaddleSpeed = 450.0f;

Paddle::Paddle(int WIDTH, int HEIGHT, sf::Color COLOR)
{
    paddleObject.setSize(sf::Vector2f(WIDTH, HEIGHT));
    paddleObject.setFillColor(COLOR);
}

void Paddle::Init(sf::Vector2f POSITION)
{
    paddleObject.setPosition(POSITION);
}

void Paddle::setPosition(sf::Vector2f POSITION)
{
    paddleObject.setPosition(POSITION);
}

sf::FloatRect Paddle::getRect()
{
    return paddleObject.getGlobalBounds();
}

void Paddle::moveUp(float dt)
{
    paddleObject.move(0, -PaddleSpeed * dt);
}

void Paddle::moveDown(float dt)
{
    paddleObject.move(sf::Vector2f(0, PaddleSpeed * dt));
}

bool Paddle::isColliding(sf::RectangleShape RECTANGLE)
{
    if(paddleObject.getGlobalBounds().intersects(RECTANGLE.getGlobalBounds()))
        return true;
    return false;
}
sf::Vector2f Paddle::getPaddlePosition()
{
    return paddleObject.getPosition();
}

sf::Vector2f Paddle::getPaddleSize()
{
    return paddleObject.getSize();
}

void Paddle::update(sf::RenderWindow &WINDOW)
{
    WINDOW.draw(paddleObject);
}

Paddle::~Paddle()
{

}
