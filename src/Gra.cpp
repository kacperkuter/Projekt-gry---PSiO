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
    for (auto& lvl : levels)
    {
        if (lvl)
            generujPrzeciwnikowDlaModulu(*lvl);
    }
    zegar.restart();}

void Gra::renderOkna(){
    gameWindow.clear();


    gameWindow.draw(background);
    for(auto& a : levels){
        gameWindow.draw(*a);
    }
    
    //rysowanie przeciwnika
    for (auto& e : enemies)
    {
        if (e)
            gameWindow.draw(*e);
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

    for (auto& e : enemies)
    {
        if (e)
            e->aktualizuj(dt);
    }

    { // porusza platfomami i dodaje nowy moduł platform u góry i gdy najniższy moduł zejdzie poniżej zadanej wartości
        if(!levels.empty()){
            for( auto& a : levels){
                if(a){
                    a->Move(sf::Vector2f(0,predkosc_poziomu*dt));

                }
            }
                if(levels.begin()->get()->getBoundry().getPosition().y > gameWindow.getSize().y + 2*(levels.begin()->get()->getBoundry().getSize().y)){
                    levels.pop_front();
                    auto nowy_modul = std::make_unique<LevelModule>(createLevel());
                    generujPrzeciwnikowDlaModulu(*nowy_modul);
                    levels.emplace_back(std::move(nowy_modul));
                }
        }
    }

    // kolizka z platforma
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
                    float poprzedni_spod = gracz_box.top + gracz_box.height - (gracz.pobierz_predkosc().y * dt);
                    
                    if (gracz.pobierz_predkosc().y >= 0.f && poprzedni_spod <= platforma_box.top + 10.f)
                    {
                        gracz.ustaw_pozycje(gracz_box.left, platforma_box.top - gracz_box.height);
                        gracz.wylacz_predkosc_y();
                        gracz.ustaw_na_ziemi(true);
                        gracz_box = gracz.pobierz_granice();
                    }
                }
            }
        }
    }

    // usun przeciwnika jezeli zejdzie ponizej ekranu
    enemies.remove_if([this](const std::unique_ptr<Enemy>& e) {
        return e && e->pobierz_granice().top > gameWindow.getSize().y;
    });

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

void Gra::generujPrzeciwnikowDlaModulu(LevelModule& modul)
{
    //generuj przeciwnika z 30% szansy na platformie
    for (const auto& platforma : modul.getPlatforms())
    {
        // 30% szansy na przeciwnika na danej platformie
        if (rand() % 100 < 30)
        {
            sf::FloatRect bounds = platforma.getGlobalBounds();

            float enemy_x = bounds.left + (bounds.width / 2.f) - 15.f;
            float enemy_y = bounds.top - 45.f;
            enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(enemy_x, enemy_y),
                bounds.left,
                bounds.left + bounds.width
            ));
        }
    }
}
