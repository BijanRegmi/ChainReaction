#include "Game.hpp"
#include "SplashScene.hpp"

Game::Game(int width, int height, std::string title){
    _data->window.create(sf::VideoMode(width, height), title);
    _data->window.setFramerateLimit(60);
    _data->handler.AddScene(std::make_unique<SplashScene>(_data));      // SceneRef(new SplashScene(_data))
    Run();
}

void Game::Run(){
    while(_data->window.isOpen()){
        _data->handler.ProcessSceneChanges();
        _data->handler.GetActiveScene()->HandleInput();
        _data->handler.GetActiveScene()->Update();
        _data->handler.GetActiveScene()->Draw();
    }
}