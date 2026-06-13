#ifndef PRZYCISK_H
#define PRZYCISK_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
class Przycisk : public sf::Drawable, public sf::Transformable
{
public:
    Przycisk(const sf::Vector2f &size, const sf::Text tekst);
    virtual ~Przycisk() = default;
    virtual void activate() = 0;
    const sf::Vector2f getSize() const {return korpus.getSize();}
    void setText(const sf::Text& t);
    void wycentrujTekst();
    sf::FloatRect getGlobalBounds() const
    {
        return getTransform().transformRect(korpus.getLocalBounds());
    }

protected:
    sf::RectangleShape korpus;
    sf::Text tekst;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

#endif // PRZYCISK_H
