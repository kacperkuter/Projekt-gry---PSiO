#include "../include/pocisk.h"
#include <cmath>

Pocisk::Pocisk(sf::Vector2f pozycja, sf::Vector2f kierunek)
{
    ksztalt.setSize(sf::Vector2f(12.f, 4.f));
    ksztalt.setFillColor(sf::Color::Yellow); //tak jak wczesniej przeciwnik pocisk zostaje jako zolty prostokat
    ksztalt.setPosition(pozycja);


    float dlugosc = std::sqrt(kierunek.x * kierunek.x + kierunek.y * kierunek.y);
    if (dlugosc != 0.f)
    {
        predkosc = (kierunek / dlugosc) * 300.f;
    }
    else
    {
        predkosc = sf::Vector2f(-300.f, 0.f);
    }
}

void Pocisk::aktualizuj(float dt)
{
    // lot pocisku z jakas predkoscia wlasna ale zalezny od opadania ekranui
    ksztalt.move(predkosc * dt + sf::Vector2f(0.f, 50.f * dt));
}

void Pocisk::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ksztalt, states);
}
