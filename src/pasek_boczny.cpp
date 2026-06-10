#include "pasek_boczny.h"

Pasek_boczny::Pasek_boczny(const sf::Vector2f& wymiary,const sf::Color& kolor_tla) : tlo(wymiary)
{tlo.setFillColor(kolor_tla);
    if(!font.loadFromFile("../../assets/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf")){
        throw std::runtime_error("nie znaleziono czcionki paska bocznego");
    };};
void Pasek_boczny::setPozycja(const sf::Vector2f& pozycja){
    pos = pozycja;
    tlo.setPosition(pos);
}
void Pasek_boczny::setWynik(const std::string wyniki){
    tekst_wyniku = sf::Text(wyniki,font,30);
    tekst_wyniku.setPosition(pos.x+20,10);
}