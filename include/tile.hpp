#pragma once
#include <utility>
#include <iostream>

class tile
{
    
public:
    int size = 0;
    int max_size;
    
    bool occupied = false;
    int player = 0;
    
    int pos_x;
    int pos_y;
    
    tile(int position_x, int position_y, int thresh_size);
    
    bool fill(int player);
    void add();
    void capture(int player);
    
    void clear();
    bool checkoverflow();
};
