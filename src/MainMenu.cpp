#include "MainMenu.hpp"
#include "grid.hpp"
#include <string>
#include <random>
#include <iostream>

// MainMenu
MainMenu::MainMenu(GameDataRef data):_data(data){}

void MainMenu::Init(){
    sf::Font& font = _data->res.GetFont("Japanese");

    // Initiate the title
    _title.setString(TITLE);
    _title.setFont(font);
    _title.setCharacterSize(WIN_WIDTH/20);
    _data->res.changeOrigin(_title);
    _title.setPosition(WIN_WIDTH*0.5, WIN_HEIGHT*0.2);

    // Tile Count
    tile_size.setString("Tile: 3x3");
    tile_size.setFont(font);
    tile_size.setCharacterSize(WIN_WIDTH/20);
    _data->res.changeOrigin(tile_size);
    tile_size.setPosition(0.1*WIN_WIDTH-tile_size.getGlobalBounds().left, WIN_HEIGHT*0.8);

    // Play Button
    _button.Init("Play", sf::Vector2f(WIN_WIDTH/5, WIN_HEIGHT/10), WIN_WIDTH/20, 0x00000000, font);
    _button.setPosition(sf::Vector2f(WIN_WIDTH*0.5, 0.8*WIN_HEIGHT));

    // Player count text
    playerCount.setString("Players: 2");
    playerCount.setFont(font);
    playerCount.setCharacterSize(WIN_WIDTH/20);
    _data->res.changeOrigin(playerCount);
    playerCount.setPosition(0.9*WIN_WIDTH-playerCount.getGlobalBounds().width-playerCount.getGlobalBounds().left, WIN_HEIGHT*0.8);

    // Background
    _background.setTexture(_data->res.GetTexture("MenuBg"));

    // Sound
    _menuSound.setBuffer(_data->res.GetSound("MenuSound"));
    _menuSound.setLoop(true);
    _menuSound.play();

    // Particles
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
        else if(_data->event.type == sf::Event::MouseWheelScrolled)
            OnScroll(_data->event);
    }
}

void MainMenu::Update(){
    if (_button.isClicked(_data->window)){
        _menuSound.stop();

        std::string t_str = tile_size.getString();
        std::string p_str = playerCount.getString();

        int t_x = t_str.at(6) - '0';
        int t_y = t_str.at(8) - '0';
        int p = p_str.back() - '0';

        _data->handler.AddScene(std::make_unique<grid>(_data, t_x, t_y, p), false);
    }
    updateParticles();
}

void MainMenu::Draw(){
    _data->window.clear();
    _data->window.draw(_background);
    for (auto x: particles)
        _data->window.draw(x.sprite);
    _button.draw(_data->window);
    _data->window.draw(_title);
    _data->window.draw(playerCount);
    _data->window.draw(tile_size);
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

void MainMenu::OnScroll(sf::Event& e){
    if (_data->inp.isOverText(playerCount, _data->window)){
        std::string curr = playerCount.getString();
        int next;
        if (e.mouseWheelScroll.delta > 0){
            next = curr.back()-'0'+1;
            if (next>6) next = 6;
        }
        else{
            next = curr.back()-'0'-1;
            if (next<2) next = 2;
        }
        playerCount.setString("Players: "+std::to_string(next));
    } else if(_data->inp.isOverText(tile_size, _data->window)){
        std::string str = tile_size.getString();

        float mposx = e.mouseWheelScroll.x;
        float l_lpos = tile_size.findCharacterPos(6).x;
        float l_rpos = tile_size.findCharacterPos(7).x;

        float r_lpos = tile_size.findCharacterPos(8).x;

        int next;
        if (mposx < l_rpos && mposx > l_lpos){
            
            if (e.mouseWheelScroll.delta>0)
                next = str.at(6)-'0'+1;
            else
                next = str.at(6)-'0'-1;
            
            if (next>9) next = 9;
            if (next<3) next = 3;
            tile_size.setString(str.replace(6, 1, std::to_string(next)));
        }
        else if (mposx>r_lpos){
            
            if (e.mouseWheelScroll.delta>0)
                next = str.at(8)-'0'+1;
            else
                next = str.at(8)-'0'-1;
            
            if (next>9) next = 9;
            if (next<3) next = 3;
            tile_size.setString(str.replace(8, 1, std::to_string(next)));

        }
    }
}
