#include <cstdlib>
#include <ctime>
#include "../include/gra.h"

int main(){
    std::srand(std::time(nullptr));
    Gra game(6);
    sf::Clock zegar;
    while(game.isOpen()){
        float dt = zegar.restart().asSeconds();
        game.handleEvents();
        game.updateGame(dt);
        game.renderOkna();
    }
    return 0;
}