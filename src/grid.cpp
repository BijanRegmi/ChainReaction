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
    for (auto x: m_grid){
        for (auto y: x){
            std::cout << "(" << y.pos_x << ", " << y.pos_y << ", " << y.player << ", " << y.size << "/" << y.max_size << ")";
        }
        std::cout << std::endl;
    }
}

bool grid::click(int x, int y, int p){
    tile& t = m_grid[y][x];    
    if (!t.occupied){
        std::cout << "Tile (" << x << ", " << y << ") is not filled." << std::endl;
        t.fill(p);
        return true;
    } else {
        if (t.player != p){
            return false;
        } else {
            if (t.checkoverflow()){
                t.clear();
                if (x!=0) m_grid[y][x-1].capture(p);
                if (x!=size_x-1) m_grid[y][x+1].capture(p);
                if (y!=0) m_grid[y-1][x].capture(p);
                if (y!=size_y-1) m_grid[y+1][x].capture(p);
            } else {
                t.add();
            }
            return true;
        }
    }
}