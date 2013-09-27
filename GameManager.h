/***********************
*  GameStateManager.h  *
***********************/

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"

class GameManager
{
    private:
        State currentState, previousState;  // stores the current and previous state of the game
        sf::Texture backTexture;            // stores the background image texture
        sf::Texture menuTexture;            // stores the menu texture
        sf::Texture quitMsgTexture;         // stores the quit message texture
        sf::Texture winMsgTexture;          // stores the win message texture

        sf::Sprite backSprite;              // stores the background sprite
        sf::Sprite menuSprite;              // stores the  menu sprite
        sf::Sprite quitMsgSprite;           // stores the quit message sprite

        Button playButton;                  // the play button
        Button aboutButton;                 // the about button
        Button quitButton;                  // the quit button

        // play menu
        sf::Sprite playMenu;
        Button playVsComputerButton;        // play vs computer button
        Button playVsHumanButton;           // play vs human button

        // select difficulty
        sf::Sprite difficulty;
        Button difficultyEasy;              // difficulty easy button
        Button difficultyIntermediate;      // difficulty medium button
        Button difficultyHard;              // difficulty hard button

        Button backButton;                  // back button

    public:

        // default ctor
        GameManager();

        // parameterized ctor to initialize as per user's input
        GameManager(const char *BACK_TEX, const char *MENU_TEX,
                const char *QUIT_MSG_TEX, const char *MSG_TEX,
                const char *WIN_MSG_TEX);

        // show the main menu
        void ShowMainMenu(sf::RenderWindow &GAME_WINDOW);

        // show the play menu
        void ShowPlayMenu(sf::RenderWindow &GAME_WINDOW);

        // show the play vs computer menu
        void ShowPlayVsComputerMenu(sf::RenderWindow &GAME_WINDOW);

        // show the play vs human menu
        void ShowPlayVsHumanControls(sf::RenderWindow &GAME_WINDOW);

        // show the game info
        void showAbout(sf::RenderWindow &GAME_WINDOW);

        // show quit messageS
        void ShowQuitMessage(sf::RenderWindow &GAME_WINDOW);

        // get the current game state
        State getGameState();

        // set the current game state
        void setGameState(State GAME_STATE);

        // show the win messages
        void playerOneWinVsComp(sf::RenderWindow &GAME_WINDOW);
        void playerOneWinVsHuman(sf::RenderWindow &GAME_WINDOW);
        void compWin(sf::RenderWindow &GAME_WINDOW);
        void playerTwoWin(sf::RenderWindow &GAME_WINDOW);

        // dctor
        ~GameManager();
};

#endif // GAMEMANAGER_H
