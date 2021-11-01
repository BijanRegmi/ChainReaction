#pragma once

#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "tile.hpp"

class grid{
private:
    std::vector< std::vector<tile> > m_grid;
    
    sf::RenderWindow* target;
    
    const uint32_t colors[7] = {0xffffffff, 0xff0000ff, 0x00ff00ff, 0x0000ffff, 0xffff00ff, 0x00ffffff, 0xff00ffff};
    const int size_x, size_y, length;
    
    void draw_grid();
    void fill(tile& t, int p);
    void explosion(int x, int y);
public:
    grid(int size_x, int size_y, int length, sf::RenderWindow* target);
    bool click(int pos_x, int pos_y, int player, bool force = 0);
    void printgrid();
    bool checkplayer(int player);
    void render(bool c=true);
    void handleinput(sf::Event& event);
};

