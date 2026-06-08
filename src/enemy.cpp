#include "../include/enemy.h"

Enemy::Enemy(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz)
{
    // przeciwnik jako czerwony prostokat
    ksztalt.setSize(sf::Vector2f(30.f, 45.f));
    ksztalt.setFillColor(sf::Color::Red);
    ksztalt.setPosition(pozycja_startowa);

    platform_left = lewa_krawedz;
    platform_right = prawa_krawedz;

    predkosc_x = 80.f;
    predkosc_y = 50.f;
}

void Enemy::aktualizuj(float dt)
{
    sf::Vector2f pozycja = ksztalt.getPosition();
    

    pozycja.x += predkosc_x * dt;

    //blokada zeby nie wylecial za platforme
    if (pozycja.x <= platform_left)
    {
        pozycja.x = platform_left;
        predkosc_x = -predkosc_x;
    }
    else if (pozycja.x >= platform_right - ksztalt.getSize().x)
    {
        pozycja.x = platform_right - ksztalt.getSize().x;
        predkosc_x = -predkosc_x;
    }

    //ruch razem z platforma
    pozycja.y += predkosc_y * dt;

    ksztalt.setPosition(pozycja);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ksztalt, states);
}
