#pragma once

#include <vector>
#include <iostream>
#include "tile.hpp"

class grid
{
private:
    std::vector< std::vector<tile> > m_grid;
    int size_x, size_y;
public:
    grid(int size_x, int size_y);
    bool click(int pos_x, int pos_y, int player);
    void printgrid();
};

