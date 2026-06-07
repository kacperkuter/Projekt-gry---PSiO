#pragma once
#ifndef GRA_H
#define GRA_H
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"menadzer_tekstur.h"
#include"levelmodule.h"
#include"gracz.h"
class Gra
{
private:
    int tilenumber = 0;
    float predkosc_poziomu = 50;
    sf::Clock zegar;
    sf::RenderWindow gameWindow;
    sf::Sprite background;
    sf::RenderTexture render;
    Menadzer_tekstur texture_men;
    std::list<std::unique_ptr<LevelModule>> levels;
    Gracz gracz;
public:
    Gra(int tilenumber);
    void renderOkna();
    bool isOpen()const{return gameWindow.isOpen();}
    void handleEvents();
    LevelModule createLevel(const float &position = 0);
    std::list<std::unique_ptr<LevelModule>> createLevels(unsigned int nolevels);
};

#endif // GRA_H




