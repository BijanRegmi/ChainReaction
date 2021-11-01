#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics/CircleShape.hpp"

class tile{
private:
    int size = 0;
    const int pos_x;
    const int pos_y;
    const int max_size;
    const float len_x, len_y;

    void realign();
public:
    int player = 0;
    bool occupied = false;
    std::vector<sf::CircleShape*> circles;

    tile(int pos_x, int pos_y, int max_size, int len_x, int len_y);
    void fill(int p, uint32_t c);
    void remove();
    void clear();
    bool overflow();
    void print_details();
    int getsize(){return size;}
};
