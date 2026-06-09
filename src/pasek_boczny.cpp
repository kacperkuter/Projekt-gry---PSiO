#include "pasek_boczny.h"

Pasek_boczny::Pasek_boczny(const sf::Vector2f& wymiary,const sf::Color& kolor_tla) : tlo(wymiary) {tlo.setFillColor(kolor_tla);};
void Pasek_boczny::setPozycja(const sf::Vector2f& pozycja){
    pos = pozycja;
    tlo.setPosition(pos);
}