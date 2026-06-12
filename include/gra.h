#pragma once
#ifndef GRA_H
#define GRA_H
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include"menadzer_tekstur.h"
#include"levelmodule.h"
#include"gracz.h"
#include"enemy.h"
//#include"pocisk.h"
#include"pasek_boczny.h"
#include"leaderboard.h"
#include"przyciskstart.h"

class Gra
{

public:
    enum class stanGry{
        Menu,
        Rozgrywka,
        GameOver
    };

    Gra(int tilenumber);
    void renderOkna();
    bool isOpen()const{return gameWindow.isOpen();}
    void handleEvents();
    void handleMenuEvents(sf::Event &event);
    void handleGameplayEvents(sf::Event &event);
    void handleGameOverEvents(sf::Event &event);
    void updateGame(float dt);
    void startMenu();
    void startGameplay();
    void gameOver();
    void resetGame();
    void animacjaTla();
    void updateGameplay(float dt);

    std::string enteredName;
    sf::Text nameText;
    sf::Font font;

    stanGry getState() const {return stan;}
    LevelModule createLevel(const float &position = 0);
    std::list<std::unique_ptr<LevelModule>> createLevels(unsigned int nolevels);

private:
    int tilenumber = 1;
    float predkosc_poziomu = 50;
    inline static const unsigned szerokosc_okna_gry = 800;
    inline static const unsigned wysokosc_okna_gry = 920;
    inline static const unsigned szerokosc_paska_bocznego = 300;
    int wynik = 0;

    stanGry stan = stanGry::Menu;
    sf::RenderWindow gameWindow;
    Pasek_boczny pasek_boczny;
    Leaderboard leaderboard;
    sf::Sprite background;
    sf::RenderTexture render;
    Menadzer_tekstur texture_men;
    PrzyciskStart przyciskStart;
    std::list<std::unique_ptr<LevelModule>> levels;
    Gracz gracz;
    std::list<std::unique_ptr<Enemy>> enemies;
    //  std::vector<std::unique_ptr<Pocisk>> pociski;
    void generujPrzeciwnikowDlaModulu(LevelModule& modul);
};
#endif // GRA_H
