#pragma once
#ifndef GRA_H
#define GRA_H
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"menadzer_tekstur.h"
class Gra
{
private:
    sf::RenderWindow gameWindow;
    sf::Sprite background;
    sf::RenderTexture render;
    sf::Sprite torch;
    Menadzer_tekstur texture_men;
public:
    Gra();
    void renderOkna();
    bool isOpen()const{return gameWindow.isOpen();}
    void handleEvents();
};

#endif // GRA_H




