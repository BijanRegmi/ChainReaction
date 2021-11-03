#include "tile.hpp"

tile::tile(int pos_x, int pos_y, int max_size, int len_x, int len_y, GameDataRef data):pos_x(pos_x), pos_y(pos_y), max_size(max_size), len_x(len_x), len_y(len_y), _data(data){}

void tile::fill(int p){
    occupied = true;
    player = p;
    
    // Add one new circle
    int length = std::min(len_y, len_x);
    sf::CircleShape a = sf::CircleShape(0.2*length);
    a.setOrigin(0.2*length, 0.2*length);
    circles.push_back(a);

    size++;

    Update();

}

void tile::Update(){
    // Reposition
    int s = circles.size();
    if (s==0){player = 0; return;}
    if (s==1){
        circles[0].setPosition((pos_x+0.5)*len_x, (pos_y+0.5)*len_y);
    } else if(s==2){
        circles[0].setPosition((pos_x+0.4)*len_x, (pos_y+0.5)*len_y);
        circles[1].setPosition((pos_x+0.6)*len_x, (pos_y+0.5)*len_y);
    } else if (s==3){
        circles[0].setPosition((pos_x+0.4)*len_x, (pos_y+0.4)*len_y);
        circles[1].setPosition((pos_x+0.6)*len_x, (pos_y+0.4)*len_y);
        circles[2].setPosition((pos_x+0.5)*len_x, (pos_y+0.6)*len_y);
    } else if (s==4){
        circles[0].setPosition((pos_x+0.4)*len_x, (pos_y+0.4)*len_y);
        circles[1].setPosition((pos_x+0.6)*len_x, (pos_y+0.4)*len_y);
        circles[2].setPosition((pos_x+0.4)*len_x, (pos_y+0.6)*len_y);
        circles[3].setPosition((pos_x+0.6)*len_x, (pos_y+0.6)*len_y);
    }

    // Set texture
    std::string name = "Player"+std::to_string(player);
    texture = _data->res.GetTexture(name);
    for (int i=0, j=circles.size(); i<j; ++i)
        circles[i].setTexture(&texture, true);
}

void tile::remove(){
    circles.pop_back();
    Update();
}

void tile::makeVaccant(){
    occupied = false;
    size = 0;
}

bool tile::overflow(){
    return (size>=max_size);
}

void tile::Draw(){
    if (!occupied) return;
    for (int i=0; i<size; i++){
        circles[i].rotate(size);
        _data->window.draw(circles[i]);
    }
}
