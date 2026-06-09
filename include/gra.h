#pragma once
#ifndef GRA_H
#define GRA_H
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"menadzer_tekstur.h"
#include"levelmodule.h"
#include"gracz.h"
#include"enemy.h"
#include"pasek_boczny.h"
class Gra
{
private:
    int tilenumber = 0;
    float predkosc_poziomu = 50;
    inline static const unsigned szerokosc_okna_gry = 800;
    inline static const unsigned wysokosc_okna_gry = 920;
    inline static const unsigned szerokosc_paska_bocznego = 300;

    sf::Clock zegar;
    sf::RenderWindow gameWindow;
    Pasek_boczny pasek_boczny;
    sf::Sprite background;
    sf::RenderTexture render;
    Menadzer_tekstur texture_men;
    std::list<std::unique_ptr<LevelModule>> levels;
    Gracz gracz;
    std::list<std::unique_ptr<Enemy>> enemies;
    void generujPrzeciwnikowDlaModulu(LevelModule& modul);
public:
    Gra(int tilenumber);
    void renderOkna();
    bool isOpen()const{return gameWindow.isOpen();}
    void handleEvents();
    LevelModule createLevel(const float &position = 0);
    std::list<std::unique_ptr<LevelModule>> createLevels(unsigned int nolevels);
};

#endif // GRA_H




