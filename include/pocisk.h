#ifndef POCISK_H
#define POCISK_H

#include <SFML/Graphics.hpp>

class Pocisk : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    sf::Vector2f predkosc;

    // Rysowanie pocisku
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Pocisk(sf::Vector2f pozycja, sf::Vector2f kierunek);
    void aktualizuj(float dt);
    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
};

#endif // POCISK_H
