#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "Scene.hpp"
#include "Game.hpp"

class SplashScene:public Scene{
public:
    SplashScene(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();
private:
    GameDataRef _data;
    sf::Text splash_string;
    float _opacity=0;
    sf::Sound _introSound;
};