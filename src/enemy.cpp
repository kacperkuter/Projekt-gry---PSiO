#include "../include/enemy.h"
#include "../include/pocisk.h"

/*
========================================================================
STARA KLASA ENEMY
stara metoda generowania jako prostokat zaminiona zostaje na polimorfizm
========================================================================

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
========================================================================
*/

//  nowy konstruktor klasy bazowej Enemy
Enemy::Enemy(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz, TypPrzeciwnika t)
    : typ(t), punkty_zycia(100), obrazenia(10)
{
    ksztalt.setSize(sf::Vector2f(30.f, 45.f));
    ksztalt.setFillColor(sf::Color::Red);
    ksztalt.setPosition(pozycja_startowa);

    platform_left = lewa_krawedz;
    platform_right = prawa_krawedz;

    predkosc_x = 80.f;
    predkosc_y = 50.f; // Ruch razem z platformami
}

//aktualizacja klasy Enemy teraz juz przy uzyciu polimorfizmu
void Enemy::aktualizuj(float dt, sf::Vector2f pozycja_gracza, std::vector<std::unique_ptr<Pocisk>>& pociski)
{
    sf::Vector2f pozycja = ksztalt.getPosition();
    
    // Ruch w poziomie
    pozycja.x += predkosc_x * dt;

    //bloakda przed spadnięciem z platformy
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

    // Ruch razen z platforma
    pozycja.y += predkosc_y * dt;

    ksztalt.setPosition(pozycja);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(ksztalt, states);
}

// ==============================
// Goblin
// ===============================

Goblin::Goblin(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz)
    : Enemy(pozycja_startowa, lewa_krawedz, prawa_krawedz, TypPrzeciwnika::Goblin)
{
    ksztalt.setFillColor(sf::Color::Red);
    punkty_zycia = 50;
    obrazenia = 15;
    predkosc_x = 90.f; // szybszy niz inni przeciwnicy
}

void Goblin::aktualizuj(float dt, sf::Vector2f pozycja_gracza, std::vector<std::unique_ptr<Pocisk>>& pociski)
{
    //chodzenie/partol platformy
    Enemy::aktualizuj(dt, pozycja_gracza, pociski);
}

// =================
// Szkielet
// ==================
Szkielet::Szkielet(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz)
    : Enemy(pozycja_startowa, lewa_krawedz, prawa_krawedz, TypPrzeciwnika::Szkielet),
      czas_strzalu(0.f), cooldown_strzalu(2.0f)
{
    ksztalt.setFillColor(sf::Color::Blue);
    punkty_zycia = 40;
    obrazenia = 8;
    predkosc_x = 50.f;
}

void Szkielet::aktualizuj(float dt, sf::Vector2f pozycja_gracza, std::vector<std::unique_ptr<Pocisk>>& pociski)
{
    // Ruch patrolowy
    Enemy::aktualizuj(dt, pozycja_gracza, pociski);

    // strzela w gracza co dwie sekundy
    czas_strzalu += dt;
    if (czas_strzalu >= cooldown_strzalu)
    {
        sf::Vector2f srodek = ksztalt.getPosition() + sf::Vector2f(ksztalt.getSize().x / 2.f, ksztalt.getSize().y / 2.f);
        sf::Vector2f kierunek = pozycja_gracza - srodek;

        pociski.push_back(std::make_unique<Pocisk>(srodek, kierunek));
        czas_strzalu = 0.f;
    }
}
