#include "Game.hpp"
#include "SplashScene.hpp"

Game::Game(int width, int height, std::string title){
    _data->window.create(sf::VideoMode(width, height), title);
    _data->window.setFramerateLimit(60);
    _data->handler.AddScene(std::make_unique<SplashScene>(_data));      // SceneRef(new SplashScene(_data))
    Run();
}

void Game::Run(){
    LoadResources();
    while(_data->window.isOpen()){
        _data->handler.ProcessSceneChanges();
        _data->handler.GetActiveScene()->HandleInput();
        _data->handler.GetActiveScene()->Update();
        _data->handler.GetActiveScene()->Draw();
    }
}

void Game::LoadResources(){
    _data->res.LoadFont("Japanese", FONT_PATH);
    _data->res.LoadSound("Intro", INTRO_SOUND_PATH);
    _data->res.LoadTexture("MenuBg", MENU_BG_PATH);
    _data->res.LoadTexture("Molecule", MOLECULE_PATH);
    _data->res.LoadSound("MenuSound", MENU_SOUND_PATH);
}