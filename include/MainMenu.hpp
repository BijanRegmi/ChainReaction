#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Button.hpp"

class MainMenu:public Scene{
public:
    MainMenu(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();
private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Text _title;
    sf::Sprite _PlayerCount;
    sf::Sound _menuSound;

    Button _button;

    struct Particles{
        sf::Sprite sprite;
        int vx = 0;
        int vy = 0;
    }particles[MENU_PARTICLE_COUNT];

    void updateParticles();

    sf::Text playerCount;
    sf::Text tile_size;
    void OnScroll(sf::Event& e);
};