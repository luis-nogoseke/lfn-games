#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "snake.h"

static unsigned int spriteSize = 16, N = 30, M = 20;

static GameState state = GameState::start;

const float S_PER_UPDATE = 0.1f;

void processInput(sf::RenderWindow &window, Snake &s){
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Window closed
        if (event.type == sf::Event::Closed)
            window.close();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        s.setDir(Dir::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        s.setDir(Dir::Right);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        s.setDir(Dir::Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        s.setDir(Dir::Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (state != GameState::run )){
        state = GameState::run;
        s.reset();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
    }
}

void update(std::vector<Entity *> &ent){
    for (auto &e : ent){
        e->update();
    }
}

void render(sf::RenderWindow &window, std::vector<Entity *> &ent){
    window.clear();

    if(state == GameState::start){
        sf::Text message;
        sf::Font font;
        font.loadFromFile("test.ttf");
        message.setFont(font);
        message.setString("PRESS SPACE TO START");
        message.setCharacterSize(40);
        message.setColor(sf::Color::White);
        window.draw(message);
    } else if(state == GameState::run){
        // Draw our game scene here
        for (auto &e : ent){
            e->draw(window);
        }
    } else {
        sf::Text message;
        sf::Font font;
        font.loadFromFile("test.ttf");
        message.setFont(font);
        message.setString("GAME OVER");
        message.setCharacterSize(40);
        message.setColor(sf::Color::White);
        window.draw(message);
    }

    window.display();
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    std::vector<Entity *> entities;
    Snake s{N, M, state};
    entities.push_back(&s);

    sf::RenderWindow window(sf::VideoMode(spriteSize*N, spriteSize*M), "Snake");

    sf::Clock clock;
    float elapsed = 0, lag = 0;

    // The game loop
    while (window.isOpen())
    {
        elapsed = clock.getElapsedTime().asSeconds();
        clock.restart();
        lag += elapsed;

        // Process events
        processInput(window, s);

        while (lag >= S_PER_UPDATE)
        {
          // update game/entities states
          update(entities);
          lag -= S_PER_UPDATE;
        }
        // render game to the screen
        render(window, entities);
    }
    return 0;
}

// TODO:
// add music
// add score
