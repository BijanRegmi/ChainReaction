#include "grid.hpp"

int main(){
    grid a(8, 4);
    a.click(4, 2, 1);
    a.printgrid();
    a.click(5, 2, 2);
    a.printgrid();
    a.click(5, 2, 2);
    a.printgrid();
    a.click(5, 2, 2);
    a.printgrid();
    a.click(5, 2, 2);
    a.printgrid();    
}