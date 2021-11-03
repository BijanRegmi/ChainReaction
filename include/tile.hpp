#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Game.hpp"

class tile{
private:
    int size = 0;
    const int pos_x, pos_y, max_size;
    const float len_x, len_y;

    GameDataRef _data;

public:
    int player = 0;
    bool occupied = false;

    std::vector<sf::CircleShape> circles;

    tile(int pos_x, int pos_y, int max_size, int len_x, int len_y, GameDataRef data);
    
    void fill(int p);

    void Update();
    void Draw();

    void remove();
    void makeVaccant();
    bool overflow();
    int getsize(){return size;}


    sf::Texture texture;
};
