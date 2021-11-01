#include "grid.hpp"

int main(){
    const int length = 80;
    const int g_X = 5;
    const int g_Y = 5;
    
    sf::Event ev;
    sf::RenderWindow win(sf::VideoMode(g_X*length, g_Y*length), "GRID");
    win.setFramerateLimit(60);
    
    grid g(g_X, g_Y, length, &win);

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