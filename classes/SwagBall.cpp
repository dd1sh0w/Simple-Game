#include "SwagBall.h"

SwagBall::SwagBall(sf::RenderWindow& window, int type) : type(type) {
    this->initShape(window);
}

SwagBall::~SwagBall() {

}

void SwagBall::initShape(sf::RenderWindow& window) {
    this->shape.setRadius(static_cast<float>(rand()%10 + 10));
    sf::Color color;

    switch (type) {
        case DEFAULT:
            color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255);
            break;
        case DAMAGING:
            color = sf::Color::Red;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2);
            break;
        case HEALING:
            color = sf::Color::Green;
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2);
            break;
        case SwagBallTypes::DEAD:
            color = sf::Color::White;
            break;
    }

    this->shape.setFillColor(color);
    this->shape.setPosition(sf::Vector2f(
            static_cast<float>(rand() % window.getSize().x - this->shape.getGlobalBounds().width),
            static_cast<float>(rand() % window.getSize().y - this->shape.getGlobalBounds().height)));
}

void SwagBall::update() {

}

void SwagBall::render(sf::RenderTarget& target) {
    target.draw(this->shape);
}

const sf::CircleShape SwagBall::getShape() const {
    return this->shape;
}

const int& SwagBall::getType() const {
    return this->type;
}
