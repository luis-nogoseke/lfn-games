#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

enum class GameState { start, run, gameOver};

class Entity{
public:
    virtual ~Entity() {}

   virtual void update() = 0;

   virtual void draw(sf::RenderWindow &window) = 0;
};

#endif // ENTITY_H
