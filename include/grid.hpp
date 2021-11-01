#pragma once

#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "tile.hpp"

class grid: public sf::Sprite
{
private:
    std::vector< std::vector<tile> > m_grid;
    
    sf::RenderTexture _texture;
    
    const uint32_t colors[7] = {0xffffffff, 0xff0000ff, 0x00ff00ff, 0x0000ffff, 0xffff00ff, 0x00ffffff, 0xff00ffff};
    const int size_x, size_y, length;
    bool animating = false;
public:
    grid(int size_x, int size_y, int length);
    bool click(int pos_x, int pos_y, int player, bool force=0);
    void printgrid();
    bool checkplayer(int player);
    void draw_grid();
    void render();
    void fill(int x, int y, int p);
    void animate_move(bool x, bool y, int dir, sf::CircleShape* c);
    void explosion(int x, int y);
};

