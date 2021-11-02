#include "MainMenu.hpp"
#include <iostream>

// MainMenu
MainMenu::MainMenu(GameDataRef data):_data(data){}

void MainMenu::Init(){
    _data->res.LoadTexture("MenuBg", MENU_BG_PATH);

    _button.Init("Play", sf::Vector2f(200, 50), 10, 0x00000000, _data->res.GetFont("Japanese"));

    _button.setPosition(_data->window.getView().getCenter());

    _background.setTexture(_data->res.GetTexture("MenuBg"));
}

void MainMenu::HandleInput(){
    while(_data->window.pollEvent(_data->event)){
        if ((_data->event.type == sf::Event::Closed) || (_data->event.type == sf::Event::KeyPressed && _data->event.key.code == sf::Keyboard::Escape))
            _data->window.close();
    }
}

void MainMenu::Update(){
    _button.isClicked(_data->window);
}

void MainMenu::Draw(){
    _data->window.clear();
    _data->window.draw(_background);
    _button.draw(_data->window);
    _data->window.display();
}