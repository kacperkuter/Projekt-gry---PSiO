#include "../include/gra.h"
#include<iostream>
Gra::Gra(int tilenumber) : gameWindow(sf::VideoMode(800, 920), "TowerCLIMB"), tilenumber(tilenumber)
{texture_men.set(TextureID::Brick_tile,"../../assets/backgrnd_textr.png");
    texture_men.set(TextureID::Torch,"../../assets/torch.png");
    texture_men.set(TextureID::GameWindow,texture_men.texturemap(gameWindow.getSize().x,gameWindow.getSize().y,
    std::vector<std::vector<TextureID>>(tilenumber,std::vector<TextureID>(tilenumber, TextureID::Brick_tile)),std::make_pair(0.f,0.f)));
    background.setTexture(texture_men.load(TextureID::GameWindow));
    render.create(gameWindow.getSize().x,gameWindow.getSize().y);
    texture_men.set(TextureID::Platform,"../../assets/wood1.jpg");
levels = createLevels(9);
zegar.restart();}

void Gra::renderOkna(){
    gameWindow.clear();


    gameWindow.draw(background);
    for(auto& a : levels){
        gameWindow.draw(*a);
    }
    gameWindow.draw(gracz);
    gameWindow.display();

}
void Gra::handleEvents(){
    float dt = zegar.restart().asSeconds();
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            gameWindow.close();
    }

    gracz.obsluz_sterowanie();
    gracz.aktualizuj(dt);

    { // porusza platfomami i dodaje nowy moduł platform u góry i gdy najniższy moduł zejdzie poniżej zadanej wartości
        if(!levels.empty()){
            for( auto& a : levels){
                if(a){
                    a->Move(sf::Vector2f(0,predkosc_poziomu*dt));

                }
            }
                if(levels.begin()->get()->getBoundry().getPosition().y > gameWindow.getSize().y + 2*(levels.begin()->get()->getBoundry().getSize().y)){
                    levels.pop_front();
                    levels.emplace_back(std::make_unique<LevelModule>(createLevel()));
                }
        }
    }

    // Wykrywanie kolizji z platformami
    sf::FloatRect gracz_box = gracz.pobierz_granice();
    for (auto& modul : levels)
    {
        if (modul)
        {
            for (auto& platforma : modul->getPlatforms())
            {
                sf::FloatRect platforma_box = platforma.getGlobalBounds();
                if (gracz_box.intersects(platforma_box))
                {
                    // Obliczamy poprzednią dolną pozycję gracza przed ruchem w tej klatce
                    float poprzedni_spod = gracz_box.top + gracz_box.height - (gracz.pobierz_predkosc().y * dt);
                    
                    // Jeśli gracz spadał i znajdował się powyżej platformy
                    if (gracz.pobierz_predkosc().y >= 0.f && poprzedni_spod <= platforma_box.top + 10.f)
                    {
                        // Umieszczamy gracza na platformie
                        gracz.ustaw_pozycje(gracz_box.left, platforma_box.top - gracz_box.height);
                        gracz.wylacz_predkosc_y();
                        gracz.ustaw_na_ziemi(true);
                        gracz_box = gracz.pobierz_granice(); // Aktualizacja boxa gracza
                    }
                }
            }
        }
    }

}
LevelModule Gra::createLevel(const float& position){ // tworzy nowy moduł platform o losowym ustawieniu
    std::vector<bool> platforms;
    for(int i = 0;i < tilenumber; ++i){
        platforms.emplace_back(rand()%2);
    }
    if(std::all_of(platforms.begin(),platforms.end(),[](const auto& a){return a!=true;})){ platforms[rand()%tilenumber] = 1; }
    else if(std::all_of(platforms.begin(),platforms.end(),[](const auto & a){return a==true;})){ platforms[rand()%tilenumber] = 0; }
    for(auto p : platforms){
        std::cout<<p;
    }
    std::cout<<std::endl;

    return LevelModule(sf::Vector2f(gameWindow.getSize().x,gameWindow.getSize().y/tilenumber),&texture_men.load(TextureID::Platform),&texture_men.load(TextureID::Torch),sf::IntRect(0,0,32,32),platforms,position);
    ;
}
std::list<std::unique_ptr<LevelModule>> Gra::createLevels(unsigned int nolevels){ // tworzy n początkowych modułów platform
    std::list<std::unique_ptr<LevelModule>> list;
    for(unsigned int i = 0; i < nolevels; ++i){
        list.emplace_front(std::make_unique<LevelModule>(createLevel(i)));
    }
    return list;

}
