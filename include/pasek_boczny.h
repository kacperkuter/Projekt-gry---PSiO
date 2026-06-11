#ifndef PASEK_BOCZNY_H
#define PASEK_BOCZNY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
class Pasek_boczny : public sf::Drawable
{
public:
    Pasek_boczny(const sf::Vector2f& wymiary, const sf::Color& kolor_tla = sf::Color::Black);
    void setWynik(const std::string wyniki);
    void setPozycja(const sf::Vector2f& pozycja);
    void aktualizujHP(int hp, int max_hp);


    void draw(sf::RenderTarget& target,
              sf::RenderStates states) const override{
        target.draw(tlo,states);
        target.draw(tekst_wyniku,states);
        target.draw(hp_tlo,states);
        target.draw(hp_pasek,states);
        target.draw(tekst_hp,states);
    }

private:
    sf::Font font;
    sf::Vector2f pos = {0,0};

    sf::Text tekst_wyniku;
    sf::RectangleShape tlo;

    sf::Text tekst_hp;
    sf::RectangleShape hp_tlo;
    sf::RectangleShape hp_pasek;
};

#endif // PASEK_BOCZNY_H
