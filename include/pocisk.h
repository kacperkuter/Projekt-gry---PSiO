#ifndef POCISK_H
#define POCISK_H

#include <SFML/Graphics.hpp>

class Pocisk : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    sf::Vector2f predkosc;
    bool przez_gracza; // Czy pocisk został wystrzelony przez gracza

    // Rysowanie pocisku
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Pocisk(sf::Vector2f pozycja, sf::Vector2f kierunek, bool przez_gracza = false, sf::Color kolor = sf::Color::Yellow);
    void aktualizuj(float dt);
    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
    bool czy_przez_gracza() const { return przez_gracza; }
};

#endif // POCISK_H
