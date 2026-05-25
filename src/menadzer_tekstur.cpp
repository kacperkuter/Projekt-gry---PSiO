
#include "../include/menadzer_tekstur.h"

Menadzer_tekstur::Menadzer_tekstur(){}
void Menadzer_tekstur::set(TextureID object, const std::string& file){
        if(textures[object].first!=file){
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

        if(texture->loadFromFile(file)){
            texture->setRepeated(true);
            this->textures[object].first = file;
            this->textures[object].second = std::move(texture);
        }
        else{
            throw std::runtime_error("Nie mozna zaladowac tekstury: "+file);
        }
        }
}
sf::Texture& Menadzer_tekstur::load(TextureID id){
    if(textures[id].second==nullptr){
        throw std::runtime_error("Brak przypisanej tekstury");
    }
    return *textures[id].second;
}