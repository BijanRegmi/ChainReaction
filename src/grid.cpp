#include "grid.hpp"

grid::grid(int x, int y, sf::RenderWindow* w):size_x(x), size_y(y), target(w){
    sf::Vector2u size = w->getSize();
    len_x = size.x/x;
    len_y = size.y/y;
    for (int i=0; i<y; ++i){
        std::vector<tile> horiz;
        for (int j=0; j<x; ++j){
            int m_size = 4;
            
            if (i == 0 || i == y-1) m_size -= 1;
            if (j == 0 || j == x-1) m_size -= 1;
            
            horiz.push_back(tile(j, i, m_size, len_x, len_y));
        }
        m_grid.push_back(horiz);
    }
    std::cout << "Filling" << std::endl;
    
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
    
    for(int i=0; i < size_y-1; i++){
        int r = i+1;
        float rowY = len_y*r;
        grid[i*2].position = {0, rowY};
        grid[i*2+1].position = {len_x*size_x, rowY};
    }
    
    for(int i=size_y-1; i < numLines; i++){
        int c = i-size_y+2;
        float colX = len_x*c;
        grid[i*2].position = {colX, 0};
        grid[i*2+1].position = {colX, len_y*size_y};
    }
    
    target->draw(grid);
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
                t.remove();
            }
        }
        if (x<size_x-1){
            if (click(x+1, y, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                t.remove();
            }
        }
        if (y>0){
            if (click(x, y-1, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
                t.remove();
            }
        }
        if (y<size_y-1){
            if (click(x, y+1, p, 1)){
                printgrid();
                std::cout << "Removing tile(" << x <<", " << y << ") circle " << std::endl;
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
        fill(t, p);
        return true;
    } else {
        std::cout << "Tile is filled." << std::endl;
        if (t.player != p && !force){
            std::cout << "Tile doesn't belong to this player " << p << std::endl;
            return false;
        } else {
            std::cout << "Tile belongs to this player" << std::endl;
            fill(t, p);
            explosion(x, y);
        }
        return true;
    }
}

void grid::fill(tile& t, int p){
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    t.fill(p, colors[p]);
    render();
}

void grid::handleinput(sf::Event& e){
    if (e.key.code == sf::Mouse::Left){
        sf::Vector2i mPos = sf::Mouse::getPosition(*target);
        click(mPos.x/len_x, mPos.y/len_y, 1);
    }
}


void grid::render(bool c){
    if (c) target->clear();
    draw_grid();
    for (int i=0; i<size_y; i++){
        for (int j=0; j<size_x; j++){
            tile& t = m_grid[i][j];
            if (t.occupied){
                for (int i=0, j=t.getsize(); i<j; ++i){
                    target->draw(*t.circles[i]);
                }
            }
        }
    }
    target->display();
}