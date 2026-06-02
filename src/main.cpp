#include <cstdlib>
#include <ctime>
#include "../include/gra.h"
Gra game(6);
int main(){
    std::srand(std::time(nullptr));
    while(game.isOpen()){
        game.renderOkna();
        game.handleEvents();
    }
    return 0;
}