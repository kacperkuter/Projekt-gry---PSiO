#include "../include/levelmodule.h"
#include <SFML/Graphics/Texture.hpp>

LevelModule::LevelModule(const sf::Vector2f& size
                         , const sf::Texture *platform_texture
                         , const sf::Texture *torches_texture
                         , const sf::IntRect& torches_frame,
                         const std::vector<bool>& platform_placement
                         , const float position)
    :boundry(size)
//ustawiwa przeźroczysty prostokąt modułu i rysuje na nim platformy oraz pochodnie
{boundry.setFillColor(sf::Color::Transparent);
    //boundry.setOutlineColor(sf::Color::Red); //część debugingu pokazująca granice modułu
    //boundry.setOutlineThickness(1.f);
    boundry.setPosition(0,position*boundry.getSize().y-boundry.getSize().y);
    setPlatforms(platform_texture,platform_placement);
    setTorches(torches_texture,torches_frame);}
void LevelModule::animate(){
    for(auto& a : torches){
        a.AnimationStep();
    }
}
void LevelModule::setPlatforms(const sf::Texture* platform_texture,const std::vector<bool>& platforms_placement){
    //Ustawia platformy według klucza platforms_placement
    //TO DO (zamienić generowanie kilku platform obok siebie na jedną?):
    platforms.clear();
    sf::Vector2f platform_size(boundry.getSize().x/platforms_placement.size(),boundry.getSize().y/5.f);
    sf::RectangleShape temp(platform_size);
    temp.setTexture(platform_texture);
    //temp.setTexture(nullptr);
    //temp.setFillColor(sf::Color::Green);
    // bool platform_here = false;
    // float platform_x_position = 0;
    // int counter = 0;
     for(size_t i = 0; i<platforms_placement.size();++i){
    //     if(platforms_placement[i] && !platform_here){
    //         platform_here = true;
    //         temp.setPosition(sf::Vector2f(boundry.getSize().x/platforms_placement.size() * i,boundry.getPosition().y+boundry.getSize().y-platform_size.y));
    //     }
    //     else if(platforms_placement[i] && platform_here){
    //         counter++;
    //     }
    //     else if(platform_here && (!platforms_placement[i] || platforms_placement[i] == platforms_placement.back())){
    //         temp.setSize(sf::Vector2f(platform_size.x*counter,platform_size.y));
    //         platforms.emplace_back(temp);
    //         platform_here = false;
    //     }

        if(platforms_placement[i]){
            temp.setPosition(boundry.getPosition().x+(i*platform_size.x),boundry.getPosition().y+boundry.getSize().y-platform_size.y);
            platforms.emplace_back(temp);
        }

    }

}

void LevelModule::setTorches(const sf::Texture* torches_texture,const sf::IntRect torches_frame){
    //ustaiwa pochodnie w losowych miejscach na szerokości modułu
    torches.clear();
    sf::Vector2f size((32.f/128.f)*boundry.getSize().y,(32.f/100.f)*boundry.getSize().y);
    AnimatedSprite temp(*torches_texture);
    temp.setScale(
         size.x / torches_frame.width,
         size.y / torches_frame.height
        );
    temp.setTextureRect(torches_frame);
    int number =  boundry.getSize().x / size.x;
    for(int a = 0; a < number;++a){
        if(rand()%7 == 0){
            temp.setPosition(boundry.getPosition().x+(a*size.x+(((rand()%5)/10)*size.x)),(boundry.getPosition().y-size.y)+(boundry.getSize().y/2));
            torches.emplace_back(temp);
            a+=2;
        }
    }
}

void LevelModule::Move(const sf::Vector2f &offset){
    //definicja poruszania całym modułem
    boundry.move(offset);
    for(auto &torch : torches){torch.move(offset);}
    for(auto &platform : platforms) {platform.move(offset);}
}