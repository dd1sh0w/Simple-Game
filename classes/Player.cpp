#include "Player.h"


//Constructor & destructor
//**************************************************************
Player::Player(float x, float y) {
    this->shape.setPosition(x,y);

    this->initVariables();
    this->initShapes();
}

Player::~Player() {

}

//**************************************************************
//Init functions
//**************************************************************

void Player::initVariables() {
    this->movementSpeed = 5.f;
    this->hpMax = 10;
    this->hp = this->hpMax;
}

void Player::initShapes() {
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setSize(sf::Vector2f(50.f, 50.f));
}
//**************************************************************
//Functions
//**************************************************************

void Player::takeDamage(const int damage) {

    if (this->hp > 0)
        this->hp -= damage;

    if (this->hp < 0)
        this->hp = 0;
}

void Player::gainHealth(const int health) {

    if (this->hp < this->hpMax)
        this->hp += health;
    if(this->hp > this->hpMax)
        this->hp = this->hpMax;
}

void Player::update(sf::RenderTarget* target) {

    this->updateInput();

    //Window bounds collision
    this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget *target) {
    target->draw(this->shape);
}

void Player::updateInput() {

    //Keyboard input
    //Left
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->shape.move(sf::Vector2f(-this->movementSpeed, 0));
    }
    //Right
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->shape.move(sf::Vector2f(this->movementSpeed, 0));
    }
    //Up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->shape.move(sf::Vector2f(0, -this->movementSpeed));
    }
    //Down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->shape.move(sf::Vector2f(0, this->movementSpeed));
    }

}

void Player::updateWindowBoundsCollision(sf::RenderTarget *target) {

    sf::FloatRect playerBounds = this->shape.getGlobalBounds();
    //Left
    if (playerBounds.left <= 0.f)
        this->shape.setPosition(0.f, playerBounds.top);
    playerBounds = this->shape.getGlobalBounds();
    //Right
    if (playerBounds.left + playerBounds.width >= target->getSize().x)
        this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
    playerBounds = this->shape.getGlobalBounds();
    //Top
    if (playerBounds.top <= 0.f)
        this->shape.setPosition(playerBounds.left,0.f);
    playerBounds = this->shape.getGlobalBounds();
    //Bottom
    if (playerBounds.top + playerBounds.height >= target->getSize().y)
        this->shape.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}

//**************************************************************
//Accessors
//**************************************************************

const sf::RectangleShape Player::getShape() const {
    return this->shape;
}

const int &Player::getHp() const {
    return this->hp;
}

const int &Player::getHpMax() const {
    return this->hpMax;
}

//**************************************************************
