#pragma once
#include <utility>
#include <iostream>

class tile
{
    int size = 0;
    const int pos_x;
    const int pos_y;
    const int max_size;
    
public:
    int player = 0;
    
    bool occupied = false;
    
    tile(int position_x, int position_y, int thresh_size);
    
    void fill(int player);
    void clear();
    bool checkoverflow();

    void print_detail();
};
