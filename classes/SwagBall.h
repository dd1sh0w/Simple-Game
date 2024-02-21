#ifndef GRAVITATION_SWAGBALL_H
#define GRAVITATION_SWAGBALL_H

#include <SFML/Graphics.hpp>

enum SwagBallTypes {DEFAULT = 0, DAMAGING, HEALING, DEAD, NROFTYPES};

class SwagBall {
private:
    sf::CircleShape shape;

    int type;

    void initShape(sf::RenderWindow& window);
public:
    //Constructor & destructor
    SwagBall(sf::RenderWindow& window, int type);
    virtual ~SwagBall();

    //Accessors
    const sf::CircleShape getShape() const;
    const int& getType() const;

    //Functions

    void update();
    void render(sf::RenderTarget& target);
};


#endif //GRAVITATION_SWAGBALL_H
