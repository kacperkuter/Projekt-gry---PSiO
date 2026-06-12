#include "../include/gracz.h"

Gracz::Gracz()
{
    //prostokat jako gracz
    ksztalt.setSize(sf::Vector2f(40.f, 60.f));
    ksztalt.setFillColor(sf::Color::Green);
    ksztalt.setPosition(380.f, 840.f); // Pozycja startowa

    szybkosc_ruchu = 250.f; // Prędkość poruszania się gracza lewo/prawo
    predkosc = sf::Vector2f(0.f, 0.f);


    czy_na_ziemi = false;
    grawitacja = 700.f;     // sila sciagania w dol
    sila_skoku = 480.f;     // Siła skoku w górę

    // Inicjalizacja statystyk gracza (życie, obrażenia wręcz, obrażenia na odległość)
    maks_punkty_zycia = 100;
    punkty_zycia = maks_punkty_zycia;
    obrazenia_wrecz = 20;
    obrazenia_dystansowe = 15;
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

    // Skok
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && czy_na_ziemi)
    {
        predkosc.y = -sila_skoku;
        czy_na_ziemi = false;
    }
}

void Gracz::aktualizuj(float dt)
{
    // grawitacja jezeli w powietrzu
    if (!czy_na_ziemi)
    {
        predkosc.y += grawitacja * dt;
    }
    else
    {
        // poruszanie sie z platforma

        if (ksztalt.getPosition().y < 400.f - ksztalt.getSize().y - 1.f)
        {
            predkosc.y = 50.f;
        }
        else
        {
            predkosc.y = 0.f;
        }
    }

    czy_na_ziemi = false;

    ksztalt.move(predkosc * dt);

    //blokada zeby nie wyjsc za granice okna
    sf::Vector2f pozycja = ksztalt.getPosition();
    if (pozycja.x < 0.f)
    {
        ksztalt.setPosition(0.f, pozycja.y);
    }
    else if (pozycja.x > 800.f - ksztalt.getSize().x)
    {
        ksztalt.setPosition(800.f - ksztalt.getSize().x, pozycja.y);
    }

    //nie mozesz wyskoczyc powyzej ekran
    if (pozycja.y < 0.f)
    {
        ksztalt.setPosition(pozycja.x, 0.f);
        predkosc.y = 0.f;
    }

    // jezeli na dole ekranu to sie nie porusza w dol
    if (pozycja.y >= 920.f - ksztalt.getSize().y)
    {
        ksztalt.setPosition(pozycja.x, 920.f - ksztalt.getSize().y);
        predkosc.y = 0.f;
        czy_na_ziemi = true;
    }
}

void Gracz::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    target.draw(ksztalt, states);
}
