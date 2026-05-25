#include "../include/gra.h"

Gra::Gra() : gameWindow(sf::VideoMode(800, 600), "TowerCLIMB")
{texture_men.set(TextureID::GameWindow,"../../assets/backgrnd_textr.png");
    background.setTexture(texture_men.load(TextureID::GameWindow));}

void Gra::renderOkna(){
    background.setTextureRect(sf::IntRect(0,0,800,600));
    gameWindow.draw(background);
    gameWindow.display();
}
void Gra::handleEvents(){
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            gameWindow.close();
    }
}

