#include "Gra.cpp"
Gra game;
int main(){
    while(game.isOpen()){
        game.renderOkna();
        game.handleEvents();
    }
    return 0;
}