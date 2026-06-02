#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H
#include <SFML/Graphics/Sprite.hpp>
class AnimatedSprite : public sf::Sprite
{
public:
    AnimatedSprite(const sf::Texture& texture, sf::IntRect animationframe = sf::IntRect());
    void AnimationStep(bool backward = false);
};

#endif // ANIMATEDSPRITE_H
