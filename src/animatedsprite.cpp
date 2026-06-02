#include "../include/animatedsprite.h"
#include <SFML/Graphics/Texture.hpp>

AnimatedSprite::AnimatedSprite(const sf::Texture &texture, sf::IntRect animationframe) : sf::Sprite(texture,animationframe) {}
void AnimatedSprite::AnimationStep(bool backward){
    if(getTextureRect().left == getTexture()->getSize().x-getTextureRect().width && !backward)
    {
        setTextureRect(sf::IntRect(0,getTextureRect().top,getTextureRect().width,getTextureRect().height));
        return;
    }
    if(getTextureRect().left == 0 && backward){
        setTextureRect(sf::IntRect(getTexture()->getSize().x-getTextureRect().width,getTextureRect().top,getTextureRect().width,getTextureRect().height));
        return;

    }
    setTextureRect(sf::IntRect(this->getTextureRect().left+(backward*(-1))*getTextureRect().width,getTextureRect().top,getTextureRect().width,getTextureRect().height));
    return;
}
