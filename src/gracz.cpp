#include "../include/gracz.h"

Gracz::Gracz()
{
    // Ustawienie początkowego kształtu gracza (np. prostokąt 40x60 pikseli)
    ksztalt.setSize(sf::Vector2f(40.f, 60.f));
    ksztalt.setFillColor(sf::Color::Green);
    ksztalt.setPosition(380.f, 700.f); // Pozycja startowa

    szybkosc_ruchu = 200.f; // Prędkość poruszania się gracza
    predkosc = sf::Vector2f(0.f, 0.f);
}

void Gracz::obsluz_sterowanie()
{
    predkosc.x = 0.f;

    // Ruch w lewo i prawo za pomocą strzałek lub klawiszy A/D
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        predkosc.x = -szybkosc_ruchu;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        predkosc.x = szybkosc_ruchu;
    }
}

void Gracz::aktualizuj(float dt)
{
    // Przemieszczenie gracza na podstawie prędkości i czasu klatki (dt)
    ksztalt.move(predkosc * dt);
}

void Gracz::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(ksztalt, states);
}
