/*************************
*  GameStateManager.cpp  *
*************************/

#include "GameManager.h"

GameManager::GameManager()
{
    //ctor
}

GameManager::GameManager(const char *BACK_TEX, const char *MENU_TEX, const char *QUIT_MSG_TEX, const char *MSG_TEX,
                    const char *WIN_MSG_TEX)
{
    backTexture.loadFromFile(BACK_TEX);
    backSprite.setTexture(backTexture);
    backSprite.setPosition(sf::Vector2f(45, 20));

    menuTexture.loadFromFile(MENU_TEX);
    menuSprite.setTexture(menuTexture);
    menuSprite.setTextureRect(sf::IntRect(0, 20, 245, 45));
    menuSprite.setPosition(sf::Vector2f(265, 250));

    quitMsgTexture.loadFromFile(QUIT_MSG_TEX);
    quitMsgSprite.setTexture(quitMsgTexture);
    quitMsgSprite.setTextureRect(sf::IntRect(0, 0, 525, 188));
    quitMsgSprite.setPosition(sf::Vector2f(135, 180));

    currentState = ShowingMainMenu;

    playButton.setParams("Images/menuTexture.png", 0, 64, 110, 43, "Audio/MouseHit.wav", 110, 64, 156, 43);
    playButton.setPosition(330, 330);
    aboutButton.setParams("Images/menuTexture.png", 4, 110, 128, 42, "Audio/MouseHit.wav", 134, 110, 180, 42);
    aboutButton.setPosition(330, 400);
    quitButton.setParams("Images/menuTexture.png", 0, 155, 103, 45, "Audio/MouseHit.wav", 107, 155, 150, 45);
    quitButton.setPosition(330, 470);

    playMenu.setTexture(menuTexture);
    playMenu.setTextureRect(sf::IntRect(596, 202, 242, 44));
    playMenu.setPosition(sf::Vector2f(265, 250));
    playVsComputerButton.setParams("Images/menuTexture.png", 0, 248, 401, 45, "Audio/MouseHit.wav", 410, 248, 446, 45);
    playVsComputerButton.setPosition(200, 370);
    playVsHumanButton.setParams("Images/menuTexture.png", 0, 298, 328, 47, "Audio/MouseHit.wav", 349, 298, 375, 47);
    playVsHumanButton.setPosition(220, 420);

    difficulty.setTexture(menuTexture);
    difficulty.setTextureRect(sf::IntRect(0, 347, 370, 45));
    difficulty.setPosition(sf::Vector2f(250, 250));
    difficultyEasy.setParams("Images/menuTexture.png", 0, 397, 110, 43, "Audio/MouseHit.wav", 127, 398, 157, 45);
    difficultyEasy.setPosition(300, 330);
    difficultyIntermediate.setParams("Images/menuTexture.png", 0, 444, 270, 45, "Audio/MouseHit.wav", 295, 443, 319, 47);
    difficultyIntermediate.setPosition(300, 420);
    difficultyHard.setParams("Images/menuTexture.png", 0, 494, 105, 45, "Audio/MouseHit.wav", 127, 493, 153, 45);
    difficultyHard.setPosition(300, 510);

    backButton.setParams("Images/menuTexture.png", 357, 27, 119, 45, "Audio/MouseHit.wav", 487, 27, 168, 45);
    backButton.setPosition(500, 550);

    winMsgTexture.loadFromFile("Images/winMessage.png");
}

void GameManager::ShowMainMenu(sf::RenderWindow &GAME_WINDOW)
{
    previousState = currentState;

    if(playButton.isMouseOver(GAME_WINDOW))
    {
        playButton.highlighted();
        if(playButton.mouseClicked())
        {
            playButton.playClickSound();
            previousState = currentState;
            currentState = ShowingPlayMenu;
        }
    }
    playButton.update(GAME_WINDOW);

    if(aboutButton.isMouseOver(GAME_WINDOW))
    {
        aboutButton.highlighted();
        if(aboutButton.mouseClicked())
        {
            aboutButton.playClickSound();
            previousState = currentState;
            currentState = ShowingAbout;
        }
    }

    aboutButton.update(GAME_WINDOW);

    if(quitButton.isMouseOver(GAME_WINDOW))
    {
        quitButton.highlighted();
        if(quitButton.mouseClicked())
        {
            previousState = currentState;
            currentState = Quitting;
        }
    }
    quitButton.update(GAME_WINDOW);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    GAME_WINDOW.draw(backSprite);
    GAME_WINDOW.draw(menuSprite);
}

void GameManager::ShowPlayMenu(sf::RenderWindow &GAME_WINDOW)
{
    if(playVsComputerButton.isMouseOver(GAME_WINDOW))
    {
        playVsComputerButton.highlighted();
        if(playVsComputerButton.mouseClicked())
        {
            playVsComputerButton.playClickSound();
            previousState = currentState;
            currentState = ShowingPlayVsComputerMenu;
        }
    }
    playVsComputerButton.update(GAME_WINDOW);

    if(playVsHumanButton.isMouseOver(GAME_WINDOW))
    {
        playVsHumanButton.highlighted();
        if(playVsHumanButton.mouseClicked())
        {
            playVsHumanButton.playClickSound();
            previousState = currentState;
            currentState = ShowingPlayVsHumanControls;
        }
    }
    playVsHumanButton.update(GAME_WINDOW);

    if(backButton.isMouseOver(GAME_WINDOW))
    {
        backButton.highlighted();
        if(backButton.mouseClicked())
        {
            backButton.playClickSound();
            currentState = ShowingMainMenu;
        }
    }
    backButton.update(GAME_WINDOW);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }


    GAME_WINDOW.draw(backSprite);
    GAME_WINDOW.draw(playMenu);
}

void GameManager::ShowPlayVsComputerMenu(sf::RenderWindow &GAME_WINDOW)
{
    sf::Texture msgTexture;
    msgTexture.loadFromFile("Images/message.png");

    sf::Sprite msgSprite;
    msgSprite.setTexture(msgTexture);
    msgSprite.setTextureRect(sf::IntRect(0, 0, 0, 0));

    if(difficultyEasy.isMouseOver(GAME_WINDOW))
    {
        difficultyEasy.highlighted();
        msgSprite.setTextureRect(sf::IntRect(0, 0, 230, 54));
        msgSprite.setPosition(sf::Vector2f(10, 540));
        msgSprite.setScale(sf::Vector2f(0.6, 0.6));
        GAME_WINDOW.draw(msgSprite);
        if(difficultyEasy.mouseClicked())
        {
            difficultyEasy.playClickSound();
            previousState = currentState;
            currentState = PlayingVsComputerEasy;
        }
    }
    difficultyEasy.update(GAME_WINDOW);

    if(difficultyIntermediate.isMouseOver(GAME_WINDOW))
    {
        difficultyIntermediate.highlighted();
        msgSprite.setTextureRect(sf::IntRect(0, 54, 494, 38));
        msgSprite.setPosition(sf::Vector2f(10, 550));
        msgSprite.setScale(sf::Vector2f(0.6, 0.6));
        GAME_WINDOW.draw(msgSprite);
        if(difficultyIntermediate.mouseClicked())
        {
            difficultyIntermediate.playClickSound();
            previousState = currentState;
            currentState = PlayingVsComputerIntermediate;
        }
    }
    difficultyIntermediate.update(GAME_WINDOW);

    if(difficultyHard.isMouseOver(GAME_WINDOW))
    {
        difficultyHard.highlighted();
        msgSprite.setTextureRect(sf::IntRect(0, 94, 600, 47));
        msgSprite.setPosition(sf::Vector2f(10, 550));
        msgSprite.setScale(sf::Vector2f(0.6, 0.6));
        GAME_WINDOW.draw(msgSprite);
        if(difficultyHard.mouseClicked())
        {
            difficultyHard.playClickSound();
            previousState = currentState;
            currentState = PlayingVsComputerHard;
        }
    }
    difficultyHard.update(GAME_WINDOW);

    if(backButton.isMouseOver(GAME_WINDOW))
    {
        backButton.highlighted();
        if(backButton.mouseClicked())
        {
            backButton.playClickSound();
            currentState = ShowingPlayMenu;
        }
    }
    backButton.update(GAME_WINDOW);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    GAME_WINDOW.draw(backSprite);
    GAME_WINDOW.draw(difficulty);
}

void GameManager::ShowPlayVsHumanControls(sf::RenderWindow &GAME_WINDOW)
{
    GAME_WINDOW.clear(sf::Color::White);

    sf::Texture controls;
    controls.loadFromFile("Images/humanControls.png");

    sf::Sprite humanControls;
    humanControls.setTexture(controls);
    humanControls.setPosition(sf::Vector2f(170, 200));

    sf::RectangleShape borderRect(sf::Vector2f(740, 540));
    borderRect.setFillColor(sf::Color::Black);
    borderRect.setPosition(sf::Vector2f(30, 30));

    sf::Font textFont;
    textFont.loadFromFile("Fonts/BankGothic.ttf");

    sf::Text title("PLAYER CONTROLS", textFont, 30);
    title.setColor(sf::Color(44, 127, 255));
    title.setPosition(sf::Vector2f(245, 30));

    sf::Text player1_controls("PLAYER - 1", textFont, 25);
    player1_controls.setColor(sf::Color::Yellow);
    player1_controls.setPosition(sf::Vector2f(200, 150));

    sf::Text player2_controls("PLAYER - 2", textFont, 25);
    player2_controls.setColor(sf::Color::Yellow);
    player2_controls.setPosition(sf::Vector2f(450, 150));

    sf::Text continueText("Press ENTER key to continue...", textFont, 30);
    continueText.setColor(sf::Color::Red);
    continueText.setPosition(sf::Vector2f(150, 500));

    GAME_WINDOW.draw(borderRect);
    GAME_WINDOW.draw(title);
    GAME_WINDOW.draw(humanControls);
    GAME_WINDOW.draw(player1_controls);
    GAME_WINDOW.draw(player2_controls);
    GAME_WINDOW.draw(continueText);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        currentState = Quitting;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        currentState = PlayingVsHuman;
    }
}

void GameManager::showAbout(sf::RenderWindow &GAME_WINDOW)
{
    sf::Font textFont;
    textFont.loadFromFile("Fonts/arial.ttf");

    sf::Font nameFont;
    nameFont.loadFromFile("Fonts/eldiablo.ttf");

    sf::Text myCredits("Made by : ", textFont, 20);
    myCredits.setColor(sf::Color::White);
    myCredits.setPosition(sf::Vector2f(350, 30));

    sf::Text name("Kou$htav Chakrabarty", textFont, 35);
    name.setColor(sf::Color::White);
    name.setPosition(sf::Vector2f(240, 100));

    sf::Text myName("The illusionist mirage", nameFont, 35);
    myName.setColor(sf::Color::Red);
    myName.setPosition(sf::Vector2f(310, 150));

    sf::Text credits1("This game is a remake of the original Pong created by Allan Alcorn. I didn't create it\nnor do I claim so.", textFont, 20);
    credits1.setColor(sf::Color::White);
    credits1.setPosition(sf::Vector2f(30, 250));

    sf::Text credits2("THANKS TO : ", textFont, 20);
    credits2.setColor(sf::Color::White);
    credits2.setPosition(sf::Vector2f(330, 320));

    sf::Texture SFML_Logo;
    SFML_Logo.loadFromFile("Images/sfmlLogo.png");

    sf::Texture codeBlocksLogo;
    codeBlocksLogo.loadFromFile("Images/codeBlocksLogo.png");

    sf::Sprite SFML_Sprite;
    SFML_Sprite.setTexture(SFML_Logo);
    SFML_Sprite.setScale(sf::Vector2f(0.8, 0.8));
    SFML_Sprite.setPosition(sf::Vector2f(40, 370));

    sf::Sprite codeBlocks_Sprite;
    codeBlocks_Sprite.setTexture((codeBlocksLogo));
    codeBlocks_Sprite.setScale(sf::Vector2f(0.8, 0.8));
    codeBlocks_Sprite.setPosition(sf::Vector2f(460, 360));

    if(backButton.isMouseOver(GAME_WINDOW))
    {
        backButton.highlighted();
        if(backButton.mouseClicked())
        {
            backButton.playClickSound();
            currentState = previousState;
        }
    }
    backButton.update(GAME_WINDOW);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    GAME_WINDOW.draw(myCredits);
    GAME_WINDOW.draw(name);
    GAME_WINDOW.draw(myName);
    GAME_WINDOW.draw(credits1);
    GAME_WINDOW.draw(credits2);
    GAME_WINDOW.draw(SFML_Sprite);
    GAME_WINDOW.draw(codeBlocks_Sprite);
}

void GameManager::ShowQuitMessage(sf::RenderWindow &GAME_WINDOW)
{
    sf::Vector2i MousePosition = sf::Mouse::getPosition(GAME_WINDOW);

    if(MousePosition.x > 261 && MousePosition.x < 375 && MousePosition.y > 303 && MousePosition.y < 343)
    {
        quitMsgSprite.setTextureRect(sf::IntRect(0, 191, 525, 187));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            GAME_WINDOW.close();
        }
    }

    else if(MousePosition.x > 406 && MousePosition.x < 520 && MousePosition.y > 303 && MousePosition.y < 338)
    {
        quitMsgSprite.setTextureRect(sf::IntRect(0, 383, 525, 187));

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            currentState = previousState;
        }
    }
    else
        quitMsgSprite.setTextureRect(sf::IntRect(0, 0, 525, 188));

    GAME_WINDOW.draw(quitMsgSprite);
}

State GameManager::getGameState()
{
    return currentState;
}

void GameManager::setGameState(State GAME_STATE)
{
    currentState = GAME_STATE;
}

void GameManager::playerOneWinVsComp(sf::RenderWindow &GAME_WINDOW)
{
    sf::Sprite pOneWonVsComp;
    pOneWonVsComp.setTexture(winMsgTexture);
    pOneWonVsComp.setTextureRect(sf::IntRect(0, 0, 625, 90));
    pOneWonVsComp.setPosition(sf::Vector2f(100, 100));

    sf::Sprite returnMsg;
    returnMsg.setTexture(winMsgTexture);
    returnMsg.setTextureRect(sf::IntRect(0, 309, 540, 39));
    returnMsg.setPosition(sf::Vector2f(100, 200));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        previousState = currentState;
        currentState = ShowingMainMenu;
    }

    GAME_WINDOW.draw(pOneWonVsComp);
    GAME_WINDOW.draw(returnMsg);
}

void GameManager::playerOneWinVsHuman(sf::RenderWindow &GAME_WINDOW)
{
    sf::Sprite pOneWonVsHuman;
    pOneWonVsHuman.setTexture(winMsgTexture);
    pOneWonVsHuman.setTextureRect(sf::IntRect(0, 160, 625, 72));
    pOneWonVsHuman.setPosition(sf::Vector2f(100, 100));

    sf::Sprite returnMsg;
    returnMsg.setTexture(winMsgTexture);
    returnMsg.setTextureRect(sf::IntRect(0, 309, 540, 39));
    returnMsg.setPosition(sf::Vector2f(100, 200));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        previousState = currentState;
        currentState = ShowingMainMenu;
    }

    GAME_WINDOW.draw(pOneWonVsHuman);
    GAME_WINDOW.draw(returnMsg);
}

void GameManager::compWin(sf::RenderWindow &GAME_WINDOW)
{
    sf::Sprite compWonVsHuman;
    compWonVsHuman.setTexture(winMsgTexture);
    compWonVsHuman.setTextureRect(sf::IntRect(0, 87, 625, 75));
    compWonVsHuman.setPosition(sf::Vector2f(100, 100));

    sf::Sprite returnMsg;
    returnMsg.setTexture(winMsgTexture);
    returnMsg.setTextureRect(sf::IntRect(0, 309, 540, 39));
    returnMsg.setPosition(sf::Vector2f(100, 200));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        previousState = currentState;
        currentState = ShowingMainMenu;
    }

    GAME_WINDOW.draw(compWonVsHuman);
    GAME_WINDOW.draw(returnMsg);
}

void GameManager::playerTwoWin(sf::RenderWindow &GAME_WINDOW)
{
    sf::Sprite pTwoWonVsHuman;
    pTwoWonVsHuman.setTexture(winMsgTexture);
    pTwoWonVsHuman.setTextureRect(sf::IntRect(0, 232, 625, 70));
    pTwoWonVsHuman.setPosition(sf::Vector2f(100, 100));

    sf::Sprite returnMsg;
    returnMsg.setTexture(winMsgTexture);
    returnMsg.setTextureRect(sf::IntRect(0, 309, 540, 39));
    returnMsg.setPosition(sf::Vector2f(100, 200));

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        previousState = currentState;
        currentState = Quitting;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        previousState = currentState;
        currentState = ShowingMainMenu;
    }

    GAME_WINDOW.draw(pTwoWonVsHuman);
    GAME_WINDOW.draw(returnMsg);
}

GameManager::~GameManager()
{
    //dtor
}
