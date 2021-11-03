#include "SplashScene.hpp"
#include "MainMenu.hpp"

SplashScene::SplashScene( GameDataRef data): _data(data){}

void SplashScene::Init(){
    _data->res.LoadFont("Japanese", "res/japanese.ttf");
    splash_string.setString("C H A I N  R E A C T I O N");
    splash_string.setFont(_data->res.GetFont("Japanese"));
    splash_string.setCharacterSize(WIN_WIDTH/20);

    _data->res.changeOrigin(splash_string);
    splash_string.setPosition(_data->window.getView().getCenter());

}

void SplashScene::HandleInput(){
    while(_data->window.pollEvent(_data->event)){
        if ((_data->event.type == sf::Event::Closed) || (_data->event.type == sf::Event::KeyPressed && _data->event.key.code == sf::Keyboard::Escape))
            _data->window.close();
    }
}

void SplashScene::Update(){
    if (_opacity<255){
        splash_string.setFillColor(sf::Color(255,255,255,_opacity));
        _opacity += 255.f/(FPS*SPLASH_SCREEN_TIME);
    } else {
        _data->handler.AddScene(std::make_unique<MainMenu>(_data), true);
    }
}

void SplashScene::Draw(){
    _data->window.clear();
    _data->window.draw(splash_string);
    _data->window.display();
}