#include "../include/gra.h"
Gra game;
int main(){
    while(game.isOpen()){
        game.renderOkna();
        game.handleEvents();
    }
    return 0;
}