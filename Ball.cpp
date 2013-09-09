/*************
*  Ball.cpp  *
*************/

#include "Ball.h"

sf::Vector2<float> BallSpeed(0.3, 0.3);     // speed of the ball

Ball::Ball()
{
    //ctor
}

Ball::Ball(float RADIUS, sf::Color COLOR, const char *BUFFER_NAME)
{
    ballObject.setRadius(RADIUS);
    ballObject.setFillColor(COLOR);

    paddleHit.loadFromFile(BUFFER_NAME);
    soundPaddleHit.setBuffer(paddleHit);
}

void Ball::Init(sf::Vector2f POSITION)
{
    ballObject.setPosition(POSITION);
    currentSpeed = BallSpeed;
}

void Ball::deflectX()
{
    currentSpeed.x = -currentSpeed.x;
}

void Ball::deflectY()
{
    currentSpeed.y = -currentSpeed.y;
}

void Ball::accelerate(Paddle PLAYER)
{
    currentSpeed.y = (ballObject.getGlobalBounds().top
                        + ballObject.getGlobalBounds().height / 2
                            - PLAYER.getRect().top
                                - PLAYER.getRect().height / 2) / 100;
}

void Ball::stopMoving()
{
    currentSpeed = sf::Vector2<float>(0.0f, 0.0f);
}
void Ball::resetSpeed()
{
    currentSpeed = BallSpeed;
}

void Ball::playHitSound()
{
    soundPaddleHit.play();
}

bool Ball::isColliding(sf::RectangleShape RECTANGLE)
{
    if(ballObject.getGlobalBounds().intersects(RECTANGLE.getGlobalBounds()))
        return true;
    return false;
}

bool Ball::isColliding(sf::FloatRect RECT)
{
    if(ballObject.getGlobalBounds().intersects(RECT))
        return true;
    return false;
}

sf::Vector2f Ball::getBallPosition()
{
    return ballObject.getPosition();
}

float Ball::getBallRadius()
{
    return ballObject.getRadius();
}

void Ball::move()
{
    ballObject.move(currentSpeed.x, currentSpeed.y);
}

void Ball::update(sf::RenderWindow &WINDOW)
{
    WINDOW.draw(ballObject);
}

Ball::~Ball()
{
    //dtor
}
