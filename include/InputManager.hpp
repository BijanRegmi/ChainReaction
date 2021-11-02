#pragma once

#include <SFML/Graphics.hpp>

class InputManager{
public:
    InputManager(){}
    ~InputManager(){}

    bool isSpriteClicked(sf::Sprite& sprite, sf::Mouse::Button button, sf::RenderWindow& window);

    bool isOverText(sf::Text& text, sf::RenderWindow& window);
};