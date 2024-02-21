#include "Game.h"


//Constructors & destructors
Game::Game() {

    this->initVariables();
    this->initWindow();
    this->initFont();
    this->initText();
}

Game::~Game() {
    delete this->window;
}

void Game::initWindow() {
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables() {
    this->endGame = false;
    this->spawnTimerMax = 10.f;
    this->spawnTimer = 0.f;
    this-> swagBallsMax = 10;
    this->points = 0;
}

//Accessors

//Modifiers

//Functions

const bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event)){
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::update() {

    this->pollEvents();

    if(!this->endGame) {
        this->updatePlayer();
        this->spawnSwagBall();
        this->updateGui();
        this->updateCollision();
    }
}

void Game::render() {
    this->window->clear();

    //Render bodies
    for (auto i : this->swagBalls) {
        i.render(*this->window);
    }
    this->player.render(this->window);

    //Render gui
    this-> guiRender(this->window);

    //Render end game text
    if (this->endGame) {
        this->window->draw(this->endGameText);
    }

    //Display
    this->window->display();
}

void Game::spawnSwagBall() {
    //Timer
    if(this->spawnTimer < this->spawnTimerMax) {
        this->spawnTimer += 1.f;
    } else {
        this->spawnTimer = 0.f;
        if (this->swagBalls.size() < this->swagBallsMax) {
            this->swagBalls.push_back(SwagBall(*this->window, this->randomizeType()));
        }
    }

}

void Game::updateCollision() {

    for (size_t i = 0; i < this-> swagBalls.size(); ++i) {
        if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())) {
            switch (this->swagBalls[i].getType()) {
                case SwagBallTypes::DEFAULT:
                    //Add points
                    this->points++;
                    break;
                case SwagBallTypes::DAMAGING:
                    //Take damage
                    this->player.takeDamage(1);
                    break;
                case SwagBallTypes::HEALING:
                    //Add health & point
                    this->points++;
                    this->player.gainHealth(1);
                    break;
                case SwagBallTypes::DEAD:
                    this->player.takeDamage(10);
                    break;
            }
            
            this->swagBalls.erase(this->swagBalls.begin() + i);

        }
    }
}

void Game::initFont() {
    if (!this->font.loadFromFile("../fonts/Ticketing.ttf")){
        std::cerr << "ERROR::GAME.CPP::INITFONT: Could not load a font!" << '\n';
    }
}

void Game::initText() {
    //GUI text
    this->guiText.setFont(this->font);
    this->guiText.setCharacterSize(24);

    //End game text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(68);
    this->endGameText.setPosition(sf::Vector2f(250, 250));
    this->endGameText.setString("GAME OVER!");
}

void Game::guiRender(sf::RenderTarget* target) {
    target->draw(this->guiText);
}

void Game::updateGui() {

    std::stringstream ss;
    ss << " Points: " << this->points << '\n';
    ss << " Health: " << this->player.getHp() << " / " << this->player.getHpMax();
    this->guiText.setString(ss.str());
}

const int Game::randomizeType() {
    int type = SwagBallTypes::DEFAULT;
    int randomValue = rand()% 100 + 1;

    if(randomValue > 0 && randomValue <= 33) {
        type = SwagBallTypes::DAMAGING;
    } else {
        if (randomValue > 33 && randomValue <= 43) {
            type = SwagBallTypes::HEALING;
        } else {
            if (randomValue == 44) {
                type = SwagBallTypes::DEAD;
            }
        }
    }

    return type;
}

const bool &Game::getEndGame() const {
    return this->endGame;
}

void Game::updatePlayer() {
    this->player.update(this->window);

    if (this->player.getHp() <= 0)
        this->endGame = true;
}
