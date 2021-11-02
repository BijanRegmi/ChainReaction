#include "ResourceManager.hpp"

void ResourceManager::LoadTexture(std::string name, std::string fileName){
    sf::Texture tex;
    if (tex.loadFromFile(fileName))
        _textures[name]=tex;
}

sf::Texture& ResourceManager::GetTexture(std::string name){
    return _textures.at(name);
}

void ResourceManager::LoadFont(std::string name, std::string fileName){
    sf::Font font;
    if (font.loadFromFile(fileName))
        _fonts[name]=font;
}

sf::Font& ResourceManager::GetFont(std::string name){
    return _fonts.at(name);
}