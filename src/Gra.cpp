#include "../include/gra.h"
#include<iostream>
#include<algorithm>

Gra::Gra(int tilenumber) : gameWindow(sf::VideoMode(szerokosc_okna_gry + szerokosc_paska_bocznego, wysokosc_okna_gry), "TowerCLIMB"), tilenumber(tilenumber),
    pasek_boczny(sf::Vector2f(szerokosc_paska_bocznego,wysokosc_okna_gry),sf::Color(255,193,46))
{
    texture_men.set(TextureID::Brick_tile,"../../assets/backgrnd_textr.png");
    texture_men.set(TextureID::Torch,"../../assets/torch.png");
    texture_men.set(TextureID::GameWindow,texture_men.texturemap(szerokosc_okna_gry,wysokosc_okna_gry,
    std::vector<std::vector<TextureID>>(tilenumber,std::vector<TextureID>(tilenumber, TextureID::Brick_tile)),std::make_pair(0.f,0.f)));
    background.setTexture(texture_men.load(TextureID::GameWindow));
    render.create(szerokosc_okna_gry,wysokosc_okna_gry);
    texture_men.set(TextureID::Platform,"../../assets/wood1.jpg");
    levels = createLevels(9);
    for (auto& lvl : levels)
    {
        if (lvl)
            generujPrzeciwnikowDlaModulu(*lvl);
    }
    pasek_boczny.setPozycja(sf::Vector2f(szerokosc_okna_gry,0));
    leaderboard.add_wynik("player",200);
    leaderboard.add_wynik("player 2",100);
    pasek_boczny.setWynik(leaderboard.get_as_string());
    zegar.restart();
}

void Gra::renderOkna(){
    render.clear();

    render.draw(background);
    for(auto& a : levels){
        render.draw(*a);
    }
    
    // rysowanie przeciwnika
    for (auto& e : enemies)
    {
        if (e)
            render.draw(*e);
    }

    // rysowanie pociskow
    for (auto& p : pociski)
    {
        if (p)
            render.draw(*p);
    }

    render.draw(gracz);
    render.display();

    gameWindow.clear();
    sf::Sprite oknogry(render.getTexture());
    gameWindow.draw(oknogry);
    gameWindow.draw(pasek_boczny);
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
            e->aktualizuj(dt, gracz.pobierz_pozycje(), pociski);
    }

    // aktualizacja pociskow
    for (auto& p : pociski)
    {
        if (p)
            p->aktualizuj(dt);
    }

    /*
    ========================================================================
    STARE USUWANIE POCISKÓW
    Usuwal pocisk kiedy wyleci za ekran, kod zostal updateowany zeby usuwal pocisk przy zderzeniu
z platforma co pozwala zeby pociski przez nia nie przelatywaly i sie nei stackowaly na gracza
    ========================================================================
    // usuwanie pociskow poza ekranem
    pociski.erase(std::remove_if(pociski.begin(), pociski.end(), [this](const std::unique_ptr<Pocisk>& p) {
        return !p || p->pobierz_granice().top > wysokosc_okna_gry || p->pobierz_granice().top + p->pobierz_granice().height < 0.f;
    }), pociski.end());
    ========================================================================
    */

    /*
    ========================================================================
    STARE USUWANIE POCISKÓW WRAZ Z KOLIZJAMI Z PLATFORMAMI (ZAKOMENTOWANE ZGODNIE Z ZALECENIEM)
    Ten kod usuwał pociski przy wyjściu za ekran oraz po zderzeniu z platformami.
    ========================================================================
    // usuwanie pociskow (poza ekranem oraz przy kolizji z platformami)
    pociski.erase(std::remove_if(pociski.begin(), pociski.end(), [this](const std::unique_ptr<Pocisk>& p) {
        if (!p) return true;

        // 1. Warunek wyjścia poza ekran
        if (p->pobierz_granice().top > wysokosc_okna_gry || p->pobierz_granice().top + p->pobierz_granice().height < 0.f)
            return true;

        // 2. Warunek kolizji z platformami
        sf::FloatRect pocisk_box = p->pobierz_granice();
        for (const auto& modul : levels)
        {
            if (modul)
            {
                for (const auto& platforma : modul->getPlatforms())
                {
                    if (pocisk_box.intersects(platforma.getGlobalBounds()))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }), pociski.end());
    ========================================================================
    */

    // usuwanie pociskow (poza ekranem, kolizja z platformami, kolizja z graczem)
    pociski.erase(std::remove_if(pociski.begin(), pociski.end(), [this](const std::unique_ptr<Pocisk>& p) {
        if (!p) return true;

        // 1. Warunek wyjścia poza ekran
        if (p->pobierz_granice().top > wysokosc_okna_gry || p->pobierz_granice().top + p->pobierz_granice().height < 0.f)
            return true;

        // 2. Warunek kolizji z platformami
        sf::FloatRect pocisk_box = p->pobierz_granice();
        for (const auto& modul : levels)
        {
            if (modul)
            {
                for (const auto& platforma : modul->getPlatforms())
                {
                    if (pocisk_box.intersects(platforma.getGlobalBounds()))
                    {
                        return true; // kolizja z platformą - usuń pocisk
                    }
                }
            }
        }

        if (pocisk_box.intersects(gracz.pobierz_granice()))
        {
            gracz.otrzymaj_obrazenia(10); // Obrażenia od pocisku szkieleta
            return true; // kolizja z graczem - usuń pocisk
        }

        return false;
    }), pociski.end());


    { // porusza platfomami i dodaje nowy moduł platform u góry i gdy najniższy moduł zejdzie poniżej zadanej wartości
        if(!levels.empty()){
            for( auto& a : levels){
                if(a){
                    a->Move(sf::Vector2f(0,predkosc_poziomu*dt));

                }
            }
                if(levels.begin()->get()->getBoundry().getPosition().y > wysokosc_okna_gry + 2*(levels.begin()->get()->getBoundry().getSize().y)){
                    levels.pop_front();
                    auto nowy_modul = std::make_unique<LevelModule>(createLevel());
                    generujPrzeciwnikowDlaModulu(*nowy_modul);
                    levels.emplace_back(std::move(nowy_modul));
                }
        }
    }

    // kolizja z platforma
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


    {
        sf::FloatRect gracz_box = gracz.pobierz_granice();
        for (auto& e : enemies)
        {
            if (e && e->pobierz_typ() == TypPrzeciwnika::Goblin && gracz_box.intersects(e->pobierz_granice()))
            {
                gracz.otrzymaj_obrazenia(e->pobierz_obrazenia());
                break;
            }
        }
    }

    // usun przeciwnika jezeli zejdzie ponizej ekranu
    enemies.remove_if([this](const std::unique_ptr<Enemy>& e) {
        return e && e->pobierz_granice().top > wysokosc_okna_gry;
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

    return LevelModule(sf::Vector2f(szerokosc_okna_gry,wysokosc_okna_gry/tilenumber),&texture_men.load(TextureID::Platform),&texture_men.load(TextureID::Torch),sf::IntRect(0,0,32,32),platforms,position);
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
    // generuj przeciwnika z 30% szansy na platformie
    for (const auto& platforma : modul.getPlatforms())
    {
        // 30% szansy na przeciwnika na danej platformie
        if (rand() % 100 < 30)
        {
            sf::FloatRect bounds = platforma.getGlobalBounds();

            float enemy_x = bounds.left + (bounds.width / 2.f) - 15.f;
            float enemy_y = bounds.top - 45.f;
            /*
            ==========================================
            STARA GENERACJA PRZECIWNIKA
            =============================================
            enemies.emplace_back(std::make_unique<Enemy>(
                sf::Vector2f(enemy_x, enemy_y),
                bounds.left,
                bounds.left + bounds.width,
                TypPrzeciwnika::Goblin
            ));
            ===========================================
            */
            if (rand() % 2 == 0)
            {
                enemies.emplace_back(std::make_unique<Goblin>(
                    sf::Vector2f(enemy_x, enemy_y),
                    bounds.left,
                    bounds.left + bounds.width
                ));
            }
            else
            {
                enemies.emplace_back(std::make_unique<Szkielet>(
                    sf::Vector2f(enemy_x, enemy_y),
                    bounds.left,
                    bounds.left + bounds.width
                ));
            }
        }
    }
}
