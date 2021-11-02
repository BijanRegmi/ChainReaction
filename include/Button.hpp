#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(){}
	
	void Init(std::string str, sf::Vector2f size, int charSize, uint32_t color, sf::Font& font);
	void setPosition(sf::Vector2f point);

	void draw(sf::RenderWindow& window);

	bool isMouseOver(sf::RenderWindow& window);
	bool isClicked(sf::RenderWindow& window);
private:
	sf::RectangleShape button;
	sf::Text text;
};