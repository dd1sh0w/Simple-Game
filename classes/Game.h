#ifndef GRAVITATION_GAME_H
#define GRAVITATION_GAME_H

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"

// A main class of game!
//There is all updates, renders and logic will be
class Game {
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;
    bool endGame;

    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    Player player;
    int points;
    std::vector<SwagBall> swagBalls;

    int swagBallsMax;
    float spawnTimer;
    float spawnTimerMax;

    const int randomizeType();
    void initVariables();
    void initWindow();
    void initFont();
    void initText();

public:
    //Constructors & Destructors
    Game();
    ~Game();

    //Modifiers

    //Accessors
    const bool running() const;
    const bool& getEndGame() const;

    //Functions

    void updatePlayer();
    void updateCollision();
    void spawnSwagBall();
    void pollEvents();
    void updateGui();
    void update();


    void guiRender(sf::RenderTarget* target);
    void render();

};


#endif //GRAVITATION_GAME_H
