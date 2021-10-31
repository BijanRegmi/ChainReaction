#include "tile.hpp"

tile::tile(int x, int y, int m){
    pos_x = x;
    pos_y = y;
    max_size = m;
}

bool tile::fill(int p){
    if (!occupied){
        std::cout << "Player " << p << " placed on (" << pos_x << ", " << pos_y << ")" << std::endl;
        player = p;
        occupied = true;
        size++;
        return true;
    }
    std::cout << "Oh no that place is already occupied" << std::endl;
    return false;
}

void tile::capture(int p){
    player = p;
    size++;
    std::cout << "Player " << p << " captured (" << pos_x << ", " << pos_y << ")" << std::endl;
}

void tile::add(){
    size++;
    std::cout << "Player " << player << " increased in (" << pos_x << ", " << pos_y << ")" << std::endl;
}

bool tile::checkoverflow(){
    return (size>=max_size);
}

void tile::clear(){
    occupied = false;
    player = -1;
    size = 0;
    std::cout << "Tile (" << pos_x << ", " << pos_y << ") is now empty." << std::endl;
}