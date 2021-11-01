#include "grid.hpp"

int main(){
    const int length = 100;
    const int g_X = 5;
    const int g_Y = 4;
    
    sf::Event ev;
    sf::RenderWindow win(sf::VideoMode(500, 500), "GRID");
    win.setFramerateLimit(60);
    
    grid g(g_X, g_Y, &win);

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Q)
                win.close();
            if (ev.type == sf::Event::MouseButtonPressed){
                g.handleinput(ev);
            }
        }
        g.render();
    }
}