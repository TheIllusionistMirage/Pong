/****************
*  Constants.h  *
****************/

//#pragma once
#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED


/** Window related constants **/
const int WINDOW_WIDTH = 800;           // specify window width
const int WINDOW_HEIGHT = 600;          // specify window height
const int WINDOW_BPP = 32;              // specify window bits per pixel
const char *WINDOW_CAPTION = "Pong";    // specify window caption

/** Paddle related constants **/
//const int PaddleSpeed = 450.0f;

/** Ball related constants **/
//const int BallSpeed = 0.4;
sf::Vector2<float> BallSpeed(0.4, 0.4);


#endif // CONSTANTS_H_INCLUDED
