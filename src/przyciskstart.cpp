#include "../include/przyciskstart.h"

PrzyciskStart::PrzyciskStart(const sf::Vector2f& size, const sf::Text& tekst) : Przycisk(size, tekst)
{font.loadFromFile("../../assets/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf");
    Przycisk::tekst = sf::Text("START",font,60);
    Przycisk::korpus.setFillColor(sf::Color(255,193,46));
    Przycisk::wycentrujTekst();}
void PrzyciskStart::activate(){
    active = !active;
}