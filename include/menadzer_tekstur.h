#pragma once
#ifndef MENADZER_TEKSTUR_H
#define MENADZER_TEKSTUR_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
enum class TextureID{
    Player,
    GameWindow,
    Brick_tile,
    Platform,
    Torch
};

class Menadzer_tekstur
{
private:
    std::map<TextureID,std::unique_ptr<sf::Texture>> textures;
public:
    Menadzer_tekstur();
    void set(TextureID, const std::string&);
    void set(TextureID, sf::Texture);
    sf::Texture& load(TextureID);
    sf::Texture texturemap(float _windowsize_x,float _windowsize_y,
                                             const std::vector<std::vector<TextureID>>& texturemap,
                           std::pair<float,float> tilesize = std::make_pair(0,0));
    void UpdateRender(
        sf::RenderTexture& target,
        const std::vector<TextureID>& row
        );
};

#endif // MENADZER_TEKSTUR_H
