#pragma once

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "tile.hpp"

class grid: public Scene{
public:
    grid(GameDataRef data, int size_x, int size_y, int players);
    
    void Init();

    void HandleInput();
    void Update();
    void Draw();
private:
    GameDataRef _data;

    std::vector< std::vector<tile> > m_grid;
    sf::Sprite _background;
    
    const int size_x, size_y;
    float len_x, len_y;
    const int player_count;

    int curr_player = 1;

    bool beginCheck = false, isRunning = true;
    std::map<int, bool> playerlist;
    
    void draw_grid();
    void fill(tile& t, int p);
    void explosion(int x, int y);

    bool click(int pos_x, int pos_y, int player, bool force = 0);
    int CheckGameOver();
    
};

