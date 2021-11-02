#pragma once

#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Button.hpp"

// class Button {
// public:
//     Button(){}
// 	void Init(std::string str, sf::Vector2f size, sf::Font font, int charSize, sf::Color bgColor, sf::Color labelColor){
//         button.setSize(size);
//         button.setFillColor(bgColor);

//         btn_size = size;

//         label.setString(str);
//         label.setFont(font);
//         label.setCharacterSize(charSize);
//         // label.setColor(labelColor);

//         // Set origin to the mid
//         sf::FloatRect textrect = label.getLocalBounds();
//         label.setOrigin(textrect.left+textrect.width/2, textrect.top+textrect.height/2);
//         sf::FloatRect buttonrect = button.getLocalBounds();
//         button.setOrigin(buttonrect.left+buttonrect.width/2, buttonrect.top+buttonrect.height/2);
//     }
	
//     void setPosition(sf::Vector2f pos){
//         button.setPosition(pos);
//         label.setPosition(pos);
//     }

// 	bool isMouseOver(sf::RenderWindow& window){
//         sf::IntRect rect = button.getTextureRect();
    
//         if(rect.contains(sf::Mouse::getPosition()))
//             return true;
//         else
//             return false;
//     }
	
//     void draw(sf::RenderWindow &window){
//         window.draw(button);
//         window.draw(label);
//     }
// private:
// 	sf::Text label;
//     sf::Vector2f btn_size;
// 	sf::RectangleShape button;
// };

class MainMenu:public Scene{
public:
    MainMenu(GameDataRef data);

    void Init();

    void HandleInput();
    void Update();
    void Draw();
private:
    GameDataRef _data;
    sf::Sprite _background;
    sf::Sprite _PlayerCount;

    Button _button;

    int playerCount = 0;
};