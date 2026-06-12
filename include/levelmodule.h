#ifndef LEVELMODULE_H
#define LEVELMODULE_H
#include "animatedsprite.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <list>
#include<SFML/Graphics/Drawable.hpp>
#include<SFML/Graphics/Transformable.hpp>
class LevelModule : public sf::Drawable, public sf::Transformable
{
public:
    LevelModule(const sf::Vector2f& size
                ,const sf::Texture* platform_texture
                ,const sf::Texture* torches_texture
                ,const sf::IntRect& torches_frame
                ,const std::vector<bool>& platform_placement
                ,const float position = 0
                );
    const sf::RectangleShape& getBoundry() const {return boundry;};
    const std::list<sf::RectangleShape>& getPlatforms() const {return platforms;};

    void Move(const sf::Vector2f& offset);
    void setPlatforms(const sf::Texture* platform_texture, const std::vector<bool>& platforms_placement);
    void setTorches(const sf::Texture* torches_texture, const sf::IntRect torches_frame);
    void animate();

private:
    sf::RectangleShape boundry;
    std::list<sf::RectangleShape> platforms;
    std::list<AnimatedSprite> torches;

    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override
    {
        target.draw(boundry, states);
        for(const auto& o : platforms){
        target.draw(o, states);

        }
        for(const auto& o : torches){
            target.draw(o, states);
        }
    }
};

#endif // LEVELMODULE_H
