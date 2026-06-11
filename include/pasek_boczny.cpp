#include "pasek_boczny.h"
#include <stdexcept>

Pasek_boczny::Pasek_boczny(const sf::Vector2f& wymiary,const sf::Color& kolor_tla) : tlo(wymiary)
{
    tlo.setFillColor(kolor_tla);
    if(!font.loadFromFile("../../assets/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf")){
        throw std::runtime_error("nie znaleziono czcionki paska bocznego");
    };

    //PASEK HP
    hp_tlo.setSize(sf::Vector2f(260.f, 25.f));
    hp_tlo.setFillColor(sf::Color(60, 60, 60));
    hp_tlo.setOutlineColor(sf::Color(100, 100, 100));
    hp_tlo.setOutlineThickness(1.5f);


    hp_pasek.setSize(sf::Vector2f(260.f, 25.f));
    hp_pasek.setFillColor(sf::Color(46, 204, 113));


    tekst_hp.setFont(font);
    tekst_hp.setCharacterSize(22);
    tekst_hp.setFillColor(sf::Color::White);
    tekst_hp.setString("HP: 100 / 100");
}
void Pasek_boczny::setPozycja(const sf::Vector2f& pozycja){
    pos = pozycja;
    tlo.setPosition(pos);

    tekst_hp.setPosition(pos.x + 20.f, 800.f);
    hp_tlo.setPosition(pos.x + 20.f, 835.f);
    hp_pasek.setPosition(pos.x + 20.f, 835.f);
}
void Pasek_boczny::setWynik(const std::string wyniki){
    tekst_wyniku = sf::Text(wyniki,font,30);
    tekst_wyniku.setPosition(pos.x+20,10);
}

void Pasek_boczny::aktualizujHP(int hp, int max_hp){
    if (hp < 0) hp = 0;
    if (max_hp <= 0) max_hp = 100;

    tekst_hp.setString("HP: " + std::to_string(hp) + " / " + std::to_string(max_hp));

    float procent = static_cast<float>(hp) / static_cast<float>(max_hp);
    hp_pasek.setSize(sf::Vector2f(260.f * procent, 25.f));

    /* USUNIETO: Dynamiczna zmiana koloru paska HP w zależności od procentu zdrowia
    if (procent > 0.5f) {
        hp_pasek.setFillColor(sf::Color(46, 204, 113)); // Zielony (emerald)
    } else if (procent > 0.2f) {
        hp_pasek.setFillColor(sf::Color(241, 196, 15)); // Żółty (sunflower)
    } else {
        hp_pasek.setFillColor(sf::Color(231, 76, 60));  // Czerwony (alizarin)
    }
    */
}
