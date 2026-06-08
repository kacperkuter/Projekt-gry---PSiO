#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    sf::Vector2f predkosc;
    float szybkosc_ruchu;
    
    // Zmienne fizyczne
    bool czy_na_ziemi;
    float grawitacja;
    float sila_skoku;

    // Metoda wymagana przez sf::Drawable do rysowania gracza na ekranie
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Gracz();
    void aktualizuj(float dt);
    void obsluz_sterowanie();

    // Gettery i settery do fizyki i kolizji
    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
    void ustaw_pozycje(float x, float y) { ksztalt.setPosition(x, y); }
    sf::Vector2f pobierz_pozycje() const { return ksztalt.getPosition(); }
    sf::Vector2f pobierz_predkosc() const { return predkosc; }
    void wylacz_predkosc_y() { predkosc.y = 0.f; }
    void ustaw_na_ziemi(bool na_ziemi) { czy_na_ziemi = na_ziemi; }
};

#endif
