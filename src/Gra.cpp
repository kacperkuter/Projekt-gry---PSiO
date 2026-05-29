#include "../include/gra.h"
Gra::Gra() : gameWindow(sf::VideoMode(800, 920), "TowerCLIMB")
{texture_men.set(TextureID::Brick_tile,"../../assets/backgrnd_textr.png");
    texture_men.set(TextureID::Torch,"../../assets/torch.png");
    texture_men.set(TextureID::GameWindow,texture_men.texturemap(gameWindow.getSize().x,gameWindow.getSize().y,
    std::vector<std::vector<TextureID>>(8,std::vector<TextureID>(8, TextureID::Brick_tile)),
    std::make_pair(0.f,0.f)));
    background.setTexture(texture_men.load(TextureID::GameWindow));
    torch.setTexture(texture_men.load(TextureID::Torch));
    torch.setTextureRect(sf::IntRect(0,0,32,32));
render.create(gameWindow.getSize().x,gameWindow.getSize().y);}

void Gra::renderOkna(){

    // gameWindow.draw(background);
    //gameWindow.draw(torch);

    //render.draw(background);
    //texture_men.UpdateRender(render,std::vector<TextureID>((gameWindow.getSize().x)/32,TextureID::Torch));
    //background.setTexture(render.getTexture());
    gameWindow.draw(background);
    gameWindow.display();

}
void Gra::handleEvents(){
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            gameWindow.close();
    }
}

