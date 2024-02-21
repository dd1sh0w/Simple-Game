#ifndef GRAVITATION_PLAYER_H
#define GRAVITATION_PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape shape;

    int hp;
    int hpMax;
    float movementSpeed;

    //Init functions
    void initVariables();
    void initShapes();
public:
    //Constructor & destructor
    Player(float x = 0.f, float y = 0.f);
    virtual ~Player();

    //Accessors
    const sf::RectangleShape getShape() const;
    const int& getHp() const;
    const int& getHpMax() const;

    //Functions

    void takeDamage(const int damage);
    void gainHealth(const int health);

    void updateInput();
    void updateWindowBoundsCollision(sf::RenderTarget* target);
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};


#endif //GRAVITATION_PLAYER_H
