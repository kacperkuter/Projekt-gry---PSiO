#include "../include/gracz.h"

Gracz::Gracz()
{
    // Ustawienie początkowego kształtu gracza (np. prostokąt 40x60 pikseli)
    ksztalt.setSize(sf::Vector2f(40.f, 60.f));
    ksztalt.setFillColor(sf::Color::Green); // Zielony kolor gracza, aby był dobrze widoczny
    ksztalt.setPosition(380.f, 700.f); // Pozycja startowa (blisko dołu ekranu)

    szybkosc_ruchu = 250.f; // Prędkość poruszania się gracza lewo/prawo
    predkosc = sf::Vector2f(0.f, 0.f);

    // Inicjalizacja zmiennych fizycznych
    czy_na_ziemi = false;
    grawitacja = 700.f;     // Siła grawitacji ciągnąca postać w dół
    sila_skoku = 480.f;     // Siła skoku skierowana w górę (ujemna oś Y)
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

    // Skok – dozwolony tylko wtedy, gdy gracz stoi na ziemi lub platformie
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && czy_na_ziemi)
    {
        predkosc.y = -sila_skoku;
        czy_na_ziemi = false;
    }
}

void Gracz::aktualizuj(float dt)
{
    // Aplikacja grawitacji, jeśli nie stoimy na stabilnym podłożu
    if (!czy_na_ziemi)
    {
        predkosc.y += grawitacja * dt;
    }
    else
    {
        // Jeśli stoimy na platformie, poruszamy się w dół razem z nią
        // (chyba że jesteśmy na samym dole ekranu)
        if (ksztalt.getPosition().y < 920.f - ksztalt.getSize().y - 1.f)
        {
            predkosc.y = 50.f; // Poruszanie w dół z prędkością platformy (predkosc_poziomu)
        }
        else
        {
            predkosc.y = 0.f;
        }
    }

    // Resetujemy stan na_ziemi przed ruchem – kolizje z platformami w tej klatce go zaktualizują
    czy_na_ziemi = false;

    // Przemieszczenie gracza na podstawie prędkości i czasu klatki (dt)
    ksztalt.move(predkosc * dt);

    // Ograniczenie ruchu do granic okna gry (szerokość: 800)
    sf::Vector2f pozycja = ksztalt.getPosition();
    if (pozycja.x < 0.f)
    {
        ksztalt.setPosition(0.f, pozycja.y);
    }
    else if (pozycja.x > 800.f - ksztalt.getSize().x)
    {
        ksztalt.setPosition(800.f - ksztalt.getSize().x, pozycja.y);
    }

    // Ograniczenie dolnej krawędzi ekranu (wysokość: 920) jako podłoga awaryjna
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
