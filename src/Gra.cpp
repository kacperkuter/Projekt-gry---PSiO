#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

class Gra{
private:
    sf::RenderWindow gameWindow;
public:
    Gra() : gameWindow(sf::VideoMode(800, 600), "TowerCLIMB"){}
    void renderOkna(){
        gameWindow.display();
    }
    bool isOpen(){
        return gameWindow.isOpen();
    }
    void handleEvents(){
        sf::Event event;
        while (gameWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                gameWindow.close();
        }
    }
};
