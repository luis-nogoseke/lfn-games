#ifndef SNAKE_H
#define SNAKE_H

#include "entity.h"

enum class  Dir {Left, Right, Up, Down};

class Snake : public Entity
{
public:
    Snake(unsigned int N, unsigned int M, GameState &s);

    void update() override;

    void draw(sf::RenderWindow &window) override;

    void setDir(Dir newDir);

    void reset();


private:
    sf::Sprite sprite, foodSprite;
    int length;
    struct position {int x,y;};
    position body[100];
    position food;
    unsigned int N, M;
    Dir dir;
    GameState &state;
};

#endif // SNAKE_H
