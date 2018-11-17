#include "snake.h"
#include <time.h>
#include <iostream>

const int spriteSize = 16;
static sf::Texture t;

Snake::Snake(unsigned int N, unsigned int M, GameState &s) : length(4), dir(Dir::Down), N(N), M(M), state(s)
{
    t.loadFromFile("/home/luis/lfn-games/images/red.png");
    sprite.setTexture(t);
    foodSprite.setTexture(t);
    body[0].x = 0;
    body[1].x = 0;
    body[2].x = 0;
    body[3].x = 0;
    body[0].y = 0;
    body[1].y = 0;
    body[2].y = 0;
    body[3].y = 0;

    food.x = food.y = 10;
}

void Snake::update(){
    //  Move snake body
    for (int i=length;i>0;--i){
        body[i].x=body[i-1].x;
        body[i].y=body[i-1].y;
    }

    // Move the snake's head in the direction of the pressed key
    if (dir==Dir::Down) body[0].y+=1;
    if (dir==Dir::Left) body[0].x-=1;
    if (dir==Dir::Right) body[0].x+=1;
    if (dir==Dir::Up) body[0].y-=1;

    // Check if the snake ate the food
    if ((body[0].x==food.x) && (body[0].y==food.y)){
        length++;
        food.x=rand() % (N);
        food.y=rand() % (M);
    }
    // Wrap around screen
    if (body[0].x > int(N)){;
        body[0].x = 0;
    }
    if (body[0].x < 0){
        body[0].x = N;
    }
    if (body[0].y > int(M)){
        body[0].y = 0;
    }
    if (body[0].y < 0){
        body[0].y = M;
    }

    // Check for game over
    for (int i=1;i<length;i++){
        if (body[0].x==body[i].x && body[0].y==body[i].y){
            state = GameState::gameOver;
            reset();
        }
    }
}

void Snake::draw(sf::RenderWindow &window){
    for (int i = 0; i < length; i++){
        sprite.setPosition(body[i].x*spriteSize, body[i].y*spriteSize);
        window.draw(sprite);
    }
    foodSprite.setPosition(food.x*spriteSize, food.y*spriteSize);
    window.draw(foodSprite);
}

void Snake::setDir(Dir newDir){
    dir = newDir;
}

void Snake::reset(){
    length = 4;
    body[0].x = 0;
    body[1].x = 0;
    body[2].x = 0;
    body[3].x = 0;
    body[0].y = 0;
    body[1].y = 0;
    body[2].y = 0;
    body[3].y = 0;

    dir = Dir::Down;
    food.x = food.y = 10;
}

