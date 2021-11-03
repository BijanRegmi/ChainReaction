#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class ResourceManager{
public:
    ResourceManager(){}
    ~ResourceManager(){};

    void LoadTexture(std::string name, std::string fileName);
    sf::Texture& GetTexture(std::string name);
    
    void LoadFont(std::string name, std::string fileName);
    sf::Font& GetFont(std::string name);

    void changeOrigin(sf::Text& text);
    void changeOrigin(sf::RectangleShape& rect);
private:
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;
};