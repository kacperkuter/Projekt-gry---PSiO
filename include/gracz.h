#ifndef GRACZ_H
#define GRACZ_H

#include <SFML/Graphics.hpp>

class Gracz : public sf::Drawable
{
private:
    sf::RectangleShape ksztalt;
    sf::Vector2f predkosc;
    float szybkosc_ruchu;

    // Metoda wymagana przez sf::Drawable do rysowania gracza na ekranie
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Gracz();
    void aktualizuj(float dt);
    void obsluz_sterowanie();
};

#endif
