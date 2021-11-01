#include "tile.hpp"

tile::tile(int pos_x, int pos_y, int max_size, int length):pos_x(pos_x), pos_y(pos_y), max_size(max_size), length(length){}

void tile::fill(int p, uint32_t c){
    occupied = true;
    player = p;
    
    // Add one new circle
    sf::CircleShape* a = new sf::CircleShape(0.3*length);
    a->setFillColor(sf::Color(c));
    circles.push_back(a);

    size++;

    realign();

    std::cout << "Player " << player << " placed on (" << pos_x << ", " << pos_y << ")" << std::endl;
}

void tile::realign(){
    int s = circles.size();
    if (s==1){
        circles[0]->setRadius(0.2*length);
        circles[0]->setOrigin(0.2*length, 0.2*length);
        circles[0]->setPosition((pos_x+0.5)*length, (pos_y+0.5)*length);
    } else if(s==2){
        circles[0]->setRadius(0.2*length);
        circles[0]->setOrigin(0.2*length, 0.2*length);
        circles[0]->setPosition((pos_x+0.4)*length, (pos_y+0.5)*length);
        circles[1]->setRadius(0.2*length);
        circles[1]->setOrigin(0.2*length, 0.2*length);
        circles[1]->setPosition((pos_x+0.6)*length, (pos_y+0.5)*length);
    } else if (s==3){
        circles[0]->setRadius(0.2*length);
        circles[0]->setOrigin(0.2*length, 0.2*length);
        circles[0]->setPosition((pos_x+0.4)*length, (pos_y+0.4)*length);
        circles[1]->setRadius(0.2*length);
        circles[1]->setOrigin(0.2*length, 0.2*length);
        circles[1]->setPosition((pos_x+0.6)*length, (pos_y+0.4)*length);
        circles[2]->setRadius(0.2*length);
        circles[2]->setOrigin(0.2*length, 0.2*length);
        circles[2]->setPosition((pos_x+0.5)*length, (pos_y+0.6)*length);
    }
}

void tile::remove(){
    delete circles.back();
    circles.pop_back();
    realign();
}

void tile::clear(){
    occupied = false;
    player = 0;
    size = 0;

    std::cout << "Tile (" << pos_x << ", " << pos_y << ") is now empty." << std::endl;
}

bool tile::overflow(){
    return (size>=max_size);
}

void tile::print_details(){
    std::cout << "(" << pos_x << ", " << pos_y << ", " << player << ", " << size << "/" << max_size << ")";
}