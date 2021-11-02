#pragma once

#include <memory>
#include <string>

#include "SceneHandler.hpp"
#include "ResourceManager.hpp"
#include "InputManager.hpp"

#include <SFML/Graphics.hpp>

struct GameData{
    SceneHandler handler;
    ResourceManager res;
    InputManager inp;
    sf::RenderWindow window;
    sf::Event event;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game{
public:
    Game(int width, int height, std::string title);
private:
    GameDataRef _data = std::make_shared<GameData>();
    
    void Run();
};
