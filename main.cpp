/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/*************
*  main.cpp  *
*************/

#include <SFML/Audio.hpp>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"
#include "Mouse.h"
#include "GameManager.h"
#include <string>
#include <sstream>

/** Window related constants **/
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int WINDOW_BPP = 32;
const char *WINDOW_CAPTION = "Pong";

/** Obstacle related constants **/
const int TOP_RECT_WIDTH = 800;
const int TOP_RECT_HEIGHT = 30;
sf::Color TOP_RECT_COLOR = sf::Color::Green;

const int BOTTOM_RECT_WIDTH = 800;
const int BOTTOM_RECT_HEIGHT = 30;
sf::Color BOTTOM_RECT_COLOR = sf::Color::Green;

const int LEFT_RECT_WIDTH = 30;
const int LEFT_RECT_HEIGHT = 600;
sf::Color LEFT_RECT_COLOR = sf::Color::Green;

const int RIGHT_RECT_WIDTH = 30;
const int RIGHT_RECT_HEIGHT = 600;
sf::Color RIGHT_RECT_COLOR = sf::Color::Green;

const int PARTITION_WIDTH = 5;
const int PARTITION_HEIGHT = 540;
sf::Color PARTITION_COLOR = sf::Color::Green;

/** Paddle related constants **/
const int PADDLE_WIDTH = 10;
const int PADDLE_HEIGHT = 60;

sf::Color PLAYER_1_COLOR = sf::Color::Red;
sf::Color PLAYER_2_COLOR = sf::Color::Blue;

/** Ball related constants **/
const float BALL_RADIUS = 5.0f;
sf::Color BALL_COLOR = sf::Color::White;
const char *BUFFER_NAME = "Audio/paddleHit.wav";
sf::Vector2f DEFAULT_POSITION = sf::Vector2f(WINDOW_WIDTH / 2 - 7.5, WINDOW_HEIGHT / 2 - 5);


/** Game manager class related constants **/
const char *backGround = "Images/Back.png";
const char *menu = "Images/menuTexture.png";
const char *msg = "Images/message.png";
const char *quitMsg = "Images/quitmessage.png";
const char *winMsg = "Images/winMessage.png";

int main()
{
    sf::RenderWindow GameWindow;
    GameWindow.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP),
                      WINDOW_CAPTION, sf::Style::Close);

    GameManager G_Manager(backGround, menu, quitMsg, msg, winMsg);

    sf::Clock Clock;
    float currentTime = 0.0f;
    float previousTime = 0.0f;
    float deltaTime = 0.0f;

    GameWindow.setMouseCursorVisible(false);

    Mouse MousePointer("Images/mousePointer.png", 9, 4, 26, 37);

    /** Obstacles **/
    sf::RectangleShape topRect;
    sf::RectangleShape bottomRect;
    sf::RectangleShape leftRect;
    sf::RectangleShape rightRect;
    sf::RectangleShape separationLine;

    topRect.setSize(sf::Vector2f(TOP_RECT_WIDTH, TOP_RECT_HEIGHT));
    bottomRect.setSize(sf::Vector2f(BOTTOM_RECT_WIDTH, BOTTOM_RECT_HEIGHT));
    leftRect.setSize(sf::Vector2f(LEFT_RECT_WIDTH, LEFT_RECT_HEIGHT));
    rightRect.setSize(sf::Vector2f(RIGHT_RECT_WIDTH, RIGHT_RECT_HEIGHT));
    separationLine.setSize(sf::Vector2f(PARTITION_WIDTH, PARTITION_HEIGHT));

    topRect.setFillColor(TOP_RECT_COLOR);
    bottomRect.setFillColor(BOTTOM_RECT_COLOR);
    leftRect.setFillColor(LEFT_RECT_COLOR);
    rightRect.setFillColor(RIGHT_RECT_COLOR);
    separationLine.setFillColor(PARTITION_COLOR);

    topRect.setPosition(sf::Vector2f(0, 0));
    bottomRect.setPosition(sf::Vector2f(0, 570));
    leftRect.setPosition(sf::Vector2f(0, 0));
    rightRect.setPosition(sf::Vector2f(770, 0));
    separationLine.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - separationLine.getSize().x, 30));

    Paddle player1(PADDLE_WIDTH, PADDLE_HEIGHT, PLAYER_1_COLOR);
    Paddle player2(PADDLE_WIDTH, PADDLE_HEIGHT, PLAYER_2_COLOR);

    player1.Init(sf::Vector2f(40, 260));
    player2.Init(sf::Vector2f(750, 260));

    Ball ball(BALL_RADIUS, BALL_COLOR, BUFFER_NAME);

    ball.Init(DEFAULT_POSITION);

    bool ballMoving = false;
    bool ballStopped = true;

    int ballRandomDirection = 1;

    sf::Font textFont;
    textFont.loadFromFile("Fonts/BankGothic.ttf");

    sf::Text Score("0   0", textFont, 50);
    Score.setColor(sf::Color(44, 127, 255));
    Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 68, 20)) ;

    int player1Score = 0, player2Score = 0;

    const char *SCORE_UPDATE_BUFFER = "Audio/scoreUpdate.wav";
    sf::SoundBuffer UPDATE_BUFFER;
    UPDATE_BUFFER.loadFromFile(SCORE_UPDATE_BUFFER);
    sf::Sound UPDATE_SOUND;
    UPDATE_SOUND.setBuffer(UPDATE_BUFFER);

    while(GameWindow.isOpen())
    {
        currentTime = Clock.getElapsedTime().asSeconds();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        sf::Event Event;
        while(GameWindow.pollEvent(Event))
        {
            switch(Event.type)
            {
                case sf::Event::Closed:
                    GameWindow.close();
                    break;
            }
        }

        GameWindow.clear();

        switch(G_Manager.getGameState())
        {
            case ShowingMainMenu:
                G_Manager.ShowMainMenu(GameWindow);
                break;

            case Quitting:
                {
                    G_Manager.ShowQuitMessage(GameWindow);
                    player1.Init(sf::Vector2f(40, 260));
                    player2.Init(sf::Vector2f(750, 260));
                    ball.Init(DEFAULT_POSITION);
                    player1Score = 0;
                    player2Score = 0;
                    Score.setString("0   0");
                    ballMoving = false;
                    ballStopped = true;
                }
                break;

            case ShowingPlayMenu:
                G_Manager.ShowPlayMenu(GameWindow);
                break;

            case ShowingPlayVsComputerMenu:
                G_Manager.ShowPlayVsComputerMenu(GameWindow);
                break;

            case ShowingPlayVsHumanControls:
                G_Manager.ShowPlayVsHumanControls(GameWindow);
                break;

            case PlayingVsComputerEasy:
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        player1.moveUp(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        player1.moveDown(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        if(!ballMoving && ballStopped)
                        {
                            ballMoving = true;
                            ballStopped = false;
                        }

                    if (ball.getBallPosition().y < player2.getPaddlePosition().y)
                        player2.moveUp(deltaTime / 2);

                    if(ball.getBallPosition().y +  2 * ball.getBallRadius() > player2.getPaddlePosition().y + player2.getPaddleSize().y)
                        player2.moveDown(deltaTime / 2);

                    if(player1.isColliding(topRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player1.isColliding(bottomRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(player2.isColliding(topRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player2.isColliding(bottomRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(ball.isColliding(player1.getRect()))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player1);
                    }

                    if(ball.isColliding((player2.getRect())))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player2);
                    }

                    if(ball.isColliding(bottomRect))
                        ball.deflectY();

                    if(ball.isColliding(topRect))
                        ball.deflectY();

                    if(ball.isColliding(leftRect))
                    {
                        UPDATE_SOUND.play();
                        player2Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(ball.isColliding(rightRect))
                    {
                        UPDATE_SOUND.play();
                        player1Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(player1Score >= 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 20));
                    else if(player2Score < 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 68, 20));

                    if(player1Score > 10 && (player1Score - player2Score >= 2))
                    {
                        G_Manager.setGameState(PlayerOneWonVsComp);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }
                    else if(player2Score > 10 && ((player2Score - player1Score) >= 2))
                    {
                        G_Manager.setGameState(CompWonVsHuman);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        G_Manager.setGameState(Quitting);

                    GameWindow.draw(topRect);
                    GameWindow.draw(bottomRect);
                    GameWindow.draw(leftRect);
                    GameWindow.draw(rightRect);
                    GameWindow.draw(separationLine);
                    GameWindow.draw(Score);

                    if(ballMoving && !ballStopped)
                        ball.move();

                    player1.update(GameWindow);
                    player2.update(GameWindow);
                    ball.update(GameWindow);
                } break;

            case PlayingVsComputerIntermediate:
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        player1.moveUp(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        player1.moveDown(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        if(!ballMoving && ballStopped)
                        {
                            ballMoving = true;
                            ballStopped = false;
                        }

                    if (ball.getBallPosition().y < player2.getPaddlePosition().y)
                        player2.moveUp(deltaTime / 1.5);

                    if(ball.getBallPosition().y +  2 * ball.getBallRadius() >
                       player2.getPaddlePosition().y + player2.getPaddleSize().y)
                        player2.moveDown(deltaTime / 1.5);

                    if(player1.isColliding(topRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player1.isColliding(bottomRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(player2.isColliding(topRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player2.isColliding(bottomRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(ball.isColliding(player1.getRect()))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player1);
                    }

                    if(ball.isColliding((player2.getRect())))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player2);
                    }

                    if(ball.isColliding(bottomRect))
                        ball.deflectY();

                    if(ball.isColliding(topRect))
                        ball.deflectY();

                    if(ball.isColliding(leftRect))
                    {
                        UPDATE_SOUND.play();
                        player2Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(ball.isColliding(rightRect))
                    {
                        UPDATE_SOUND.play();
                        player1Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(player1Score >= 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 20));
                    else if(player2Score < 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 68, 20));

                    if(player1Score > 10 && (player1Score - player2Score >= 2))
                    {
                        G_Manager.setGameState(PlayerOneWonVsComp);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }
                    else if(player2Score > 10 && ((player2Score - player1Score) >= 2))
                    {
                        G_Manager.setGameState(CompWonVsHuman);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        G_Manager.setGameState(Quitting);

                    GameWindow.draw(topRect);
                    GameWindow.draw(bottomRect);
                    GameWindow.draw(leftRect);
                    GameWindow.draw(rightRect);
                    GameWindow.draw(separationLine);
                    GameWindow.draw(Score);

                    if(ballMoving && !ballStopped)
                        ball.move();

                    player1.update(GameWindow);
                    player2.update(GameWindow);
                    ball.update(GameWindow);
                } break;

            case PlayingVsComputerHard:
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        player1.moveUp(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        player1.moveDown(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        if(!ballMoving && ballStopped)
                        {
                            ballMoving = true;
                            ballStopped = false;
                        }

                    if (ball.getBallPosition().y < player2.getPaddlePosition().y)
                        player2.moveUp(deltaTime);

                    if(ball.getBallPosition().y +  2 * ball.getBallRadius() >
                       player2.getPaddlePosition().y + player2.getPaddleSize().y)
                        player2.moveDown(deltaTime);

                    if(player1.isColliding(topRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player1.isColliding(bottomRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(player2.isColliding(topRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player2.isColliding(bottomRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(ball.isColliding(player1.getRect()))
                    {

                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player1);
                    }

                    if(ball.isColliding((player2.getRect())))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player2);
                    }

                    if(ball.isColliding(bottomRect))
                        ball.deflectY();

                    if(ball.isColliding(topRect))
                        ball.deflectY();

                    if(ball.isColliding(leftRect))
                    {
                        UPDATE_SOUND.play();
                        player2Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(ball.isColliding(rightRect))
                    {
                        UPDATE_SOUND.play();
                        player1Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(player1Score >= 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 20));
                    else if(player2Score < 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 68, 20));

                    if(player1Score > 10 && (player1Score - player2Score >= 2))
                    {
                        G_Manager.setGameState(PlayerOneWonVsComp);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }
                    else if(player2Score > 10 && ((player2Score - player1Score) >= 2))
                    {
                        G_Manager.setGameState(CompWonVsHuman);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        G_Manager.setGameState(Quitting);

                    GameWindow.draw(topRect);
                    GameWindow.draw(bottomRect);
                    GameWindow.draw(leftRect);
                    GameWindow.draw(rightRect);
                    GameWindow.draw(separationLine);
                    GameWindow.draw(Score);

                    if(ballMoving && !ballStopped)
                        ball.move();

                    player1.update(GameWindow);
                    player2.update(GameWindow);
                    ball.update(GameWindow);
                } break;

            case PlayingVsHuman:
                {
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                        player1.moveUp(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        player1.moveDown(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                        player2.moveUp(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                        player2.moveDown(deltaTime);

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        if(!ballMoving && ballStopped)
                        {
                            ballMoving = true;
                            ballStopped = false;
                        }



                    if(player1.isColliding(topRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player1.isColliding(bottomRect))
                        player1.setPosition(sf::Vector2f(player1.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(player2.isColliding(topRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, topRect.getPosition().y + 30));

                    if(player2.isColliding(bottomRect))
                        player2.setPosition(sf::Vector2f(player2.getPaddlePosition().x, bottomRect.getPosition().y - 60));

                    if(ball.isColliding(player1.getRect()))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player1);
                    }

                    if(ball.isColliding((player2.getRect())))
                    {
                        ball.playHitSound();
                        ball.deflectX();
                        ball.accelerate(player2);
                    }

                    if(ball.isColliding(bottomRect))
                        ball.deflectY();

                    if(ball.isColliding(topRect))
                        ball.deflectY();

                    if(ball.isColliding(leftRect))
                    {
                        UPDATE_SOUND.play();
                        player2Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(ball.isColliding(rightRect))
                    {
                        UPDATE_SOUND.play();
                        player1Score++;
                        std::stringstream Player_score;
                        Player_score << player1Score << "   " << player2Score;
                        Score.setString(Player_score.str());
                        ball.Init(sf::Vector2f(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2 - 5));
                        player1.Init(sf::Vector2f(player1.getPaddlePosition().x, WINDOW_HEIGHT / 2 - 5));
                        ballMoving = false;
                        ballStopped = true;
                        ball.resetSpeed(ballRandomDirection * (-1));
                    }

                    if(player1Score >= 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 20));
                    else if(player2Score < 10)
                        Score.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 68, 20));

                    if(player1Score > 10 && (player1Score - player2Score >= 2))
                    {
                        G_Manager.setGameState(PlayerOneWonVsHuman);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }
                    else if(player2Score > 10 && ((player2Score - player1Score) >= 2))
                    {
                        G_Manager.setGameState(PlayerTwoWonVsHuman);
                        G_Manager.ShowQuitMessage(GameWindow);
                        player1.Init(sf::Vector2f(40, 260));
                        player2.Init(sf::Vector2f(750, 260));
                        ball.Init(DEFAULT_POSITION);
                        player1Score = 0;
                        player2Score = 0;
                        Score.setString("0   0");
                        ballMoving = false;
                        ballStopped = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        G_Manager.setGameState(Quitting);

                    GameWindow.draw(topRect);
                    GameWindow.draw(bottomRect);
                    GameWindow.draw(leftRect);
                    GameWindow.draw(rightRect);
                    GameWindow.draw(separationLine);
                    GameWindow.draw(Score);

                    if(ballMoving && !ballStopped)
                        ball.move();

                    player1.update(GameWindow);
                    player2.update(GameWindow);
                    ball.update(GameWindow);
                } break;

            case ShowingAbout:
                G_Manager.showAbout(GameWindow);
                break;

            case PlayerOneWonVsComp:
                G_Manager.playerOneWinVsComp(GameWindow);
                break;

            case PlayerOneWonVsHuman:
                G_Manager.playerOneWinVsHuman(GameWindow);
                break;

            case PlayerTwoWonVsHuman:
                G_Manager.playerTwoWin(GameWindow);
                break;

            case CompWonVsHuman:
                G_Manager.compWin(GameWindow);
                break;
        }

        MousePointer.displayMouse(GameWindow);

        GameWindow.display();

    }

    return EXIT_SUCCESS;
}
