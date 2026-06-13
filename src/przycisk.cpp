#include "../include/przycisk.h"
#include <SFML/Graphics/RenderTarget.hpp>

Przycisk::Przycisk(const sf::Vector2f &size,const sf::Text tekst) : korpus(size), tekst(tekst){    sf::FloatRect bounds = tekst.getLocalBounds();

    this->tekst.setPosition(
        (size.x - bounds.width) / 2.f - bounds.left,
        (size.y - bounds.height) / 2.f - bounds.top
        );}

void Przycisk::setText(const sf::Text& t)
{
    tekst = t;
    wycentrujTekst();
}

void Przycisk::wycentrujTekst()
{
    sf::FloatRect bounds = tekst.getLocalBounds();

    tekst.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
        );

    sf::Vector2f size = korpus.getSize();

    tekst.setPosition(
        size.x / 2.f,
        size.y / 2.f
        );
}



void Przycisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    target.draw(korpus, states);
    target.draw(tekst, states);
}