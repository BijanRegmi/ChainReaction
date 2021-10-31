#include "grid.hpp"

grid::grid(int x, int y):size_x(x), size_y(y){
    for (int i=0; i<y; ++i){
        std::vector<tile> horiz;
        for (int j=0; j<x; ++j){
            int m_size = 3;
            
            if (i == 0 || i == y-1) m_size -= 1;
            if (j == 0 || j == x-1) m_size -= 1;
            
            horiz.push_back(tile(j, i, m_size));  
        }
        m_grid.push_back(horiz);
    }
    std::cout << "Filling" << std::endl;
    printgrid();
}

void grid::printgrid(){
    std::cout << "--------------" << std::endl;
    for (auto x: m_grid){
        for (auto y: x) y.print_detail();
        std::cout << std::endl;
    }
    std::cout <<  "--------------" << std::endl;
}

bool grid::checkplayer(int p){
    for (auto x: m_grid)
        for (auto y: x)
            if(y.player == p)
                return true;
    return false;
}

bool grid::click(int x, int y, int p, bool force){
    std::cout << "Tile (" << x << ", " << y << ") is clicked by player " << p << std::endl;
    tile& t = m_grid[y][x];    
    if (!t.occupied){
        std::cout << "Tile is not filled." << std::endl;
        t.fill(p);
        return true;
    } else {
        std::cout << "Tile is filled." << std::endl;
        if (t.player != p && !force){
            std::cout << "Tile doesn't belong to this player " << p << std::endl;
            return false;
        } else {
            std::cout << "Tile belongs to this player" << std::endl;
            if (t.checkoverflow()){
                std::cout << "Tile is exploding" << std::endl;
                t.clear();
                if (x>0) click(x-1, y, p, 1);
                if (x<size_x-1) click(x+1, y, p, 1);
                if (y>0) click(x, y-1, p, 1);
                if (y<size_y-1) click(x, y+1, p, 1);
                return true;
            } else {
                std::cout << "Tile can't be exploded." << std::endl;
                t.fill(p);
            }
        }
        return true;
    }
}