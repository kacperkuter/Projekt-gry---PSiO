#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    float platform_left;
    float platform_right;
    float predkosc_x;
    float predkosc_y;


    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Enemy(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz);
    void aktualizuj(float dt);
    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
};

#endif // ENEMY_H
