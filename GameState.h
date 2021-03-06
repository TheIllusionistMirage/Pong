/**********************************************************************
*  Copyright (c) 2013, Koushtav Chakrabarty(The Illusionist Mirage)   *
*  License: zlib/libpng License                                       *
*  zlib/libpng License web page: http://opensource.org/licenses/Zlib  *
**********************************************************************/

/****************
*  GameState.h  *
****************/

#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

// various states of the game
enum State{
    ShowingMainMenu = 1,
    ShowingPlayMenu,
    ShowingPlayVsComputerMenu,
    ShowingPlayVsHumanControls,
    ShowingAbout,
    PlayingVsComputerEasy,
    PlayingVsComputerIntermediate,
    PlayingVsComputerHard,
    PlayingVsHuman,
    PlayerOneWonVsComp,
    PlayerOneWonVsHuman,
    PlayerTwoWonVsHuman,
    CompWonVsHuman,
    Quitting
};

#endif // GAMESTATE_H_INCLUDED
