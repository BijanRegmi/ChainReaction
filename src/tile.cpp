#include "tile.hpp"

tile::tile(int x, int y, int m):pos_x(x), pos_y(y),max_size(m){}

void tile::fill(int p){
    occupied = true;
    player = p;
    size++;
    std::cout << "Player " << player << " placed on (" << pos_x << ", " << pos_y << ")" << std::endl;
}

bool tile::checkoverflow(){ return (size>=max_size); }

void tile::print_detail(){
    std::cout << "(" << pos_x << ", " << pos_y << ", " << player << ", " << size << "/" << max_size << ")";
}

void tile::clear(){
    occupied = false;
    player = 0;
    size = 0;
    std::cout << "Tile (" << pos_x << ", " << pos_y << ") is now empty." << std::endl;
}