#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Pocisk;

/*
========================================================================
STARA KLASA BAZOWA
stary przeciwnik ktory po prostu chodzil po platformei zmieniony na polimorfizm
========================================================================
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
========================================================================
*/

enum class TypPrzeciwnika {
    Goblin,
    Szkielet,
    Nietoperz
};

// nowy bazowy Enemy z uzyciem polimorfizmu
class Enemy : public sf::Drawable
{
protected:
    sf::RectangleShape ksztalt;
    float platform_left;
    float platform_right;
    float predkosc_x;
    float predkosc_y;
    TypPrzeciwnika typ;

    //cechy przeciwnika
    int punkty_zycia;
    int obrazenia;

    // metoda rysowania
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Enemy(sf::Vector2f pozycja_startowa, float lewa_krawedz, float prawa_krawedz, TypPrzeciwnika t);
    virtual ~Enemy() = default;

    //metoda wirtualna aktualizacji kotra przyjmuje pozycję gracza oraz listę pocisków (dla szkieletów)

    virtual void aktualizuj(float dt, sf::Vector2f pozycja_gracza, std::vector<std::unique_ptr<Pocisk>>& pociski);

    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
    TypPrzeciwnika pobierz_typ() const { return typ; }
    int pobierz_obrazenia() const { return obrazenia; }
};

#endif // ENEMY_H
