#pragma once
#ifndef MENADZER_TEKSTUR_H
#define MENADZER_TEKSTUR_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
enum class TextureID{
    Player,
    GameWindow
};

class Menadzer_tekstur
{
private:
    std::map<TextureID,std::pair<std::string,std::unique_ptr<sf::Texture>>> textures;
public:
    Menadzer_tekstur();
    void set(TextureID, const std::string&);
    sf::Texture& load(TextureID);
};

#endif // MENADZER_TEKSTUR_H
