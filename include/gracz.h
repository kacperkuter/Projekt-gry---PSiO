#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    sf::Vector2f predkosc;
    float szybkosc_ruchu;
    
    //zmienne do poruszania sie
    bool czy_na_ziemi;
    float grawitacja;
    float sila_skoku;

    // Statystyki / cechy gracza
    int punkty_zycia;
    int maks_punkty_zycia;
    int obrazenia_wrecz;
    int obrazenia_dystansowe;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Gracz();
    void aktualizuj(float dt);
    void obsluz_sterowanie();

    // Statystyki i walka
    int pobierz_hp() const { return punkty_zycia; }
    int pobierz_maks_hp() const { return maks_punkty_zycia; }
    int pobierz_obrazenia_wrecz() const { return obrazenia_wrecz; }
    int pobierz_obrazenia_dystansowe() const { return obrazenia_dystansowe; }
    void otrzymaj_obrazenia(int ile) { punkty_zycia -= ile; if (punkty_zycia < 0) punkty_zycia = 0; }
    void ulecz(int ile) { punkty_zycia += ile; if (punkty_zycia > maks_punkty_zycia) punkty_zycia = maks_punkty_zycia; }

    sf::FloatRect pobierz_granice() const { return ksztalt.getGlobalBounds(); }
    void ustaw_pozycje(float x, float y) { ksztalt.setPosition(x, y); }
    sf::Vector2f pobierz_pozycje() const { return ksztalt.getPosition(); }
    sf::Vector2f pobierz_predkosc() const { return predkosc; }
    void wylacz_predkosc_y() { predkosc.y = 0.f; }
    void ustaw_na_ziemi(bool na_ziemi) { czy_na_ziemi = na_ziemi; }
};

#endif
