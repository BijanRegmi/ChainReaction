#include "MainMenu.hpp"
#include <cmath>
#include <random>
#include <iostream>

// MainMenu
MainMenu::MainMenu(GameDataRef data):_data(data){}

void MainMenu::Init(){
    _data->res.LoadTexture("MenuBg", MENU_BG_PATH);
    _data->res.LoadTexture("Molecule", "res/molecule.png");

    _title.setString("C H A I N  R E A C T I O N");
    _title.setFont(_data->res.GetFont("Japanese"));
    _title.setCharacterSize(WIN_WIDTH/20);
    sf::FloatRect textrect = _title.getLocalBounds();
    _title.setOrigin(textrect.left+textrect.width/2, textrect.top+textrect.height/2);
    _title.setPosition(WIN_WIDTH*0.5, WIN_HEIGHT*0.2);

    _button.Init("Play", sf::Vector2f(WIN_WIDTH/3, WIN_HEIGHT/6), WIN_WIDTH/12, 0x00000000, _data->res.GetFont("Japanese"));

    _button.setPosition(sf::Vector2f(WIN_WIDTH*0.5, 0.8*WIN_HEIGHT));

    _background.setTexture(_data->res.GetTexture("MenuBg"));

    std::random_device rd;                                                      /////////////////////////////////
    std::mt19937 gen(rd());                                                     //  For uniform generation of  //
    std::uniform_int_distribution<int> rand_x(0, WIN_WIDTH);                    //  random number in range.    //
    std::uniform_int_distribution<int> rand_y(0, WIN_HEIGHT);                   //                             //
    std::uniform_int_distribution<int> vx(-WIN_WIDTH/500, WIN_WIDTH/500);       //                             //
    std::uniform_int_distribution<int> vy(-WIN_HEIGHT/500, WIN_HEIGHT/500);     /////////////////////////////////
    for (int i=0; i<MENU_PARTICLE_COUNT; i++){
        sf::Sprite sp;
        sp.setTexture(_data->res.GetTexture("Molecule"));
        sp.setScale(WIN_WIDTH/(7*sp.getLocalBounds().width), WIN_WIDTH/(7*sp.getLocalBounds().height));
        sp.setPosition(rand_x(gen), rand_y(gen));
        sf::FloatRect rect = sp.getLocalBounds();
        sp.setOrigin(rect.left+rect.width/2, rect.top+rect.height/2);
        
        particles[i].sprite = sp;
        particles[i].vx = vx(gen);
        particles[i].vy = vy(gen);
    }
}

void MainMenu::HandleInput(){
    while(_data->window.pollEvent(_data->event)){
        if ((_data->event.type == sf::Event::Closed) || (_data->event.type == sf::Event::KeyPressed && _data->event.key.code == sf::Keyboard::Escape))
            _data->window.close();
    }
}

void MainMenu::Update(){
    _button.isClicked(_data->window);
    updateParticles();
}

void MainMenu::Draw(){
    _data->window.clear();
    _data->window.draw(_background);
    for (auto x: particles)
        _data->window.draw(x.sprite);
    _button.draw(_data->window);
    _data->window.draw(_title);
    _data->window.display();
}

void MainMenu::updateParticles(){
    for (int i=0; i<MENU_PARTICLE_COUNT; i++){
        sf::Sprite& s = particles[i].sprite;
        s.move(particles[i].vx, particles[i].vy);
        s.rotate(3);
        sf::Vector2f rect = s.getPosition();
        if (rect.x < 0 || rect.x > WIN_WIDTH) particles[i].vx *= (-1);
        if (rect.y < 0 || rect.y > WIN_HEIGHT) particles[i].vy *= (-1);
    }
}
