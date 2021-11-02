#include "InputManager.hpp"
#include <iostream>

bool InputManager::isSpriteClicked(sf::Sprite& sprite, sf::Mouse::Button button, sf::RenderWindow& window){
    if (!sf::Mouse::isButtonPressed(button)) return false;
    
    sf::IntRect rect = sprite.getTextureRect();
    if (rect.contains(sf::Mouse::getPosition()))
        return true;
    else
        return false;
}

bool InputManager::isOverText(sf::Text& text, sf::RenderWindow& window){
    sf::FloatRect rect = text.getLocalBounds();
    std::cout << rect.left << " " << rect.width;
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    if (rect.contains(mPos.x, mPos.y))
        return true;
    else
        return false;
}

