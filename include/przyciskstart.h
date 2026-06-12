#ifndef PRZYCISKSTART_H
#define PRZYCISKSTART_H

#include "przycisk.h"
class PrzyciskStart : public Przycisk
{
public:
    PrzyciskStart(const sf::Vector2f& size, const sf::Text& tekst);
    void activate() override;
    bool isActive() const {return active;}
private:
    sf::Font font;
    bool active = false;
};

#endif // PRZYCISKSTART_H
