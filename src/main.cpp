#include "grid.hpp"

int main(){
    grid g(5, 5, 100);
    sf::RenderWindow win(sf::VideoMode(500, 500), "GRID");
    win.setFramerateLimit(60);
    sf::Event ev;
    // g.click(0,0,1);
    // g.click(0,0,1);
    // g.click(0,0,1);
    // g.click(0,0,1);
    // g.click(0,0,1);
    // g.click(0,0,1);    
    // g.click(0,0,1);    
    g.printgrid();

    while(win.isOpen()){
        while(win.pollEvent(ev)){
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Q)
                win.close();
            if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space){
                std::cout << std::endl << "ORIGINAL CLICK" << std::endl;
                if (g.click(2,2,1))
                    g.printgrid();
            }

        }
        g.render();

        win.clear();
        win.draw(g);
        win.display();
    }
}