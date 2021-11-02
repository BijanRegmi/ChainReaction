#include "Button.hpp"

void Button::Init(std::string str, sf::Vector2f size, int charSize, uint32_t color, sf::Font& font) {
    button.setSize(size);
    button.setFillColor(sf::Color(color));
    button.setOutlineColor(sf::Color::Green);

    // Change origin for box
    sf::FloatRect rect = button.getLocalBounds();
    button.setOrigin(rect.left+rect.width/2, rect.top+rect.height/2);

    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(charSize);

    // Change origin for text
    sf::FloatRect trect = text.getLocalBounds();
    text.setOrigin(trect.left+trect.width/2, trect.top+trect.height/2);
}

void Button::setPosition(sf::Vector2f point) {
    button.setPosition(point);
    text.setPosition(point);
}

void Button::draw(sf::RenderWindow &window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    sf::FloatRect rect = button.getGlobalBounds();
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    if (rect.contains(mPos.x, mPos.y)){
        button.setOutlineThickness(1);
        return true;
    } else {
        button.setOutlineThickness(0);
        return false;
    }
}

bool Button::isClicked(sf::RenderWindow& window){
    if (isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        button.setFillColor(sf::Color::Green);
        return true;
    } else {
        button.setFillColor(sf::Color::Transparent);
        return false;
    }
}
