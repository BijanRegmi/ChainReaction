#include "grid.hpp"

grid::grid(int x, int y, int l):size_x(x), size_y(y), length(l){
    for (int i=0; i<y; ++i){
        std::vector<tile> horiz;
        for (int j=0; j<x; ++j){
            int m_size = 4;
            
            if (i == 0 || i == y-1) m_size -= 1;
            if (j == 0 || j == x-1) m_size -= 1;
            
            horiz.push_back(tile(j, i, m_size, length));
        }
        m_grid.push_back(horiz);
    }
    std::cout << "Filling" << std::endl;
    
    _texture.create(x*l, y*l);
    this->setTexture(_texture.getTexture());

    printgrid();
}

void grid::printgrid(){
    std::cout << "--------------" << std::endl;
    for (auto x: m_grid){
        for (auto y: x) y.print_details();
        std::cout << std::endl;
    }
    std::cout <<  "--------------" << std::endl;
}

void grid::draw_grid(){
    // Stack overflow jindabad
    int numLines = size_x+size_y-2;
    sf::VertexArray grid(sf::Lines, 2*(numLines));
    
    for(int i=0; i < size_x-1; i++){
        int r = i+1;
        int rowY = length*r;
        grid[i*2].position = {0, rowY};
        grid[i*2+1].position = {length*size_y, rowY};
    }
    
    for(int i=size_x-1; i < numLines; i++){
        int c = i-size_x+2;
        int colX = length*c;
        grid[i*2].position = {colX, 0};
        grid[i*2+1].position = {colX, length*size_x};
    }
    
    _texture.draw(grid);
}

bool grid::checkplayer(int p){
    for (auto x: m_grid)
        for (auto y: x)
            if(y.player == p)
                return true;
    return false;
}

void grid::explosion(int x, int y){
    tile& t = m_grid[y][x];
    int p = t.player;
    if (t.overflow()){
        std::cout << "Tile (" << x << ", " << y << ") is exploding" << std::endl;
        t.clear();
        if (x>0){
            if (click(x-1, y, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                // animate_move(true, false, -1, t.circles[0]);
                t.remove();
            }
        }
        if (x<size_x-1){
            if (click(x+1, y, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                // animate_move(true, false, -1, t.circles[0]);
                t.remove();
            }
        }
        if (y>0){
            if (click(x, y-1, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                // animate_move(true, false, -1, t.circles[0]);
                t.remove();
            }
        }
        if (y<size_y-1){
            if (click(x, y+1, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                // animate_move(true, false, -1, t.circles[0]);
                t.remove();
            }
        }
    } else {
        std::cout << "Tile can't be exploded." << std::endl;
    }
}

bool grid::click(int x, int y, int p, bool force){
    std::cout << "Tile (" << x << ", " << y << ") is clicked by player " << p << std::endl;
    tile& t = m_grid[y][x];    
    if (!t.occupied){
        std::cout << "Tile is not filled." << std::endl;
        t.fill(p, colors[p]);
        return true;
    } else {
        std::cout << "Tile is filled." << std::endl;
        if (t.player != p && !force){
            std::cout << "Tile doesn't belong to this player " << p << std::endl;
            return false;
        } else {
            std::cout << "Tile belongs to this player" << std::endl;
            t.fill(p, colors[p]);
            explosion(x, y);
        }
        return true;
    }
}

void grid::animate_move(bool x, bool y, int dir, sf::CircleShape* c){
    int moved = 0;
    int anim_const = dir*length/8;
    while(moved != dir*length){
        c->move(x*anim_const, y*anim_const);
        moved += anim_const;
    }
}

void grid::render(){
    _texture.clear();
    draw_grid();
    for (int i=0; i<size_y; i++){
        for (int j=0; j<size_x; j++){
            tile& t = m_grid[i][j];
            if (t.occupied){
                for (auto c: t.circles){
                    if (c!=nullptr)
                        _texture.draw(*c);
                }
            }
        }
    }
    _texture.display();
}