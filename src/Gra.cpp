#include "../include/gra.h"
#include<iostream>
#include<algorithm>


Gra::Gra(int tilenumber) : gameWindow(sf::VideoMode(szerokosc_okna_gry + szerokosc_paska_bocznego, wysokosc_okna_gry), "TowerCLIMB"), tilenumber(tilenumber),
    pasek_boczny(sf::Vector2f(szerokosc_paska_bocznego,wysokosc_okna_gry),sf::Color(255,193,46)), przyciskStart(sf::Vector2f(300,150),sf::Text())
{
    texture_men.set(TextureID::Brick_tile,"../../assets/backgrnd_textr.png");
    texture_men.set(TextureID::Torch,"../../assets/torch.png");
    texture_men.set(TextureID::GameWindow,texture_men.texturemap(szerokosc_okna_gry,wysokosc_okna_gry,
    std::vector<std::vector<TextureID>>(tilenumber,std::vector<TextureID>(tilenumber, TextureID::Brick_tile)),std::make_pair(0.f,0.f)));
    background.setTexture(texture_men.load(TextureID::GameWindow));
    render.create(szerokosc_okna_gry,wysokosc_okna_gry);
    texture_men.set(TextureID::Platform,"../../assets/wood1.jpg");
    levels = createLevels(9);
    pasek_boczny.setPozycja(sf::Vector2f(szerokosc_okna_gry,0));
    przyciskStart.setPosition(szerokosc_okna_gry/2.f - przyciskStart.getSize().x / 2.f,wysokosc_okna_gry / 2.f - (przyciskStart.getSize().y + 50.f));
    font.loadFromFile("../../assets/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf");

    nameText.setFont(font);
    nameText.setCharacterSize(28);
    nameText.setFillColor(sf::Color::White);

    pasek_boczny.setWynik(leaderboard.get_as_string());
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
    if(stan == stanGry::Menu){render.draw(przyciskStart);}
    if(stan == stanGry::GameOver)
    {
        sf::Text title;
        title.setFont(font);
        title.setString("GAME OVER");
        title.setCharacterSize(40);
        title.setPosition(250.f, 150.f);

        sf::Text prompt;
        prompt.setFont(font);
        prompt.setString("Enter name:");
        prompt.setCharacterSize(25);
        prompt.setPosition(250.f, 250.f);

        nameText.setString(enteredName);
        nameText.setPosition(250.f, 300.f);

        render.draw(title);
        render.draw(prompt);
        render.draw(nameText);
    }
    render.display();

    gameWindow.clear();
    sf::Sprite oknogry(render.getTexture());
    gameWindow.draw(oknogry);

    // Aktualizacja paska HP
    pasek_boczny.aktualizujHP(gracz.pobierz_hp(), gracz.pobierz_maks_hp());

    gameWindow.draw(pasek_boczny);
    gameWindow.display();
}

void Gra::handleEvents(){
    sf::Event event;
    while (gameWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            gameWindow.close();
        switch(stan){
        case Gra::stanGry::Menu: {
            handleMenuEvents(event);
            break;
        }
        case Gra::stanGry::Rozgrywka:{
            handleGameplayEvents(event);
            break;
        }
        case Gra::stanGry::GameOver:{
            handleGameOverEvents(event);
            break;
        }
        }
    }
}
void Gra::updateGame(float dt){

    switch (stan) {
    case stanGry::Rozgrywka:{
        updateGameplay(dt);
        animacjaTla();
        break;
    }
    case stanGry::Menu:{
        animacjaTla();
        break;
    }
    case stanGry::GameOver:{

        break;
    }
    default:
        break;
    }
}

void Gra::handleMenuEvents(sf::Event& event){
        if(event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePos =
                gameWindow.mapPixelToCoords(
                    sf::Mouse::getPosition(gameWindow)
                    );

            if(przyciskStart.getGlobalBounds().contains(mousePos))
            {
                startGameplay();
            }
        }
}
//atak gracza na blisko
void Gra::handleGameplayEvents(sf::Event& event){
    /* STARY KOD - ZAKOMENTOWANY ZGODNIE Z ZALECENIEM
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        if (gracz.moze_atakowac())
        {
            gracz.wykonaj_atak();
            sf::FloatRect attack_box = gracz.pobierz_zasieg_ataku();

            for (auto& e : enemies)
            {
                if (e && attack_box.intersects(e->pobierz_granice()))
                {
                    e->otrzymaj_obrazenia(gracz.pobierz_obrazenia_wrecz());
                }
            }
        }
    }
    */
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (gracz.moze_atakowac())
            {
                gracz.wykonaj_atak();
                sf::FloatRect attack_box = gracz.pobierz_zasieg_ataku();

                for (auto& e : enemies)
                {
                    if (e && attack_box.intersects(e->pobierz_granice()))
                    {
                        e->otrzymaj_obrazenia(gracz.pobierz_obrazenia_wrecz());
                    }
                }
            }
        }
        else if (event.mouseButton.button == sf::Mouse::Right)
        {
            if (gracz.moze_strzelic())
            {
                sf::Vector2f srodek_gracza = gracz.pobierz_pozycje() + sf::Vector2f(20.f, 30.f); // Środek gracza (rozmiar 40x60)
                sf::Vector2f pozycja_myszy = gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow));
                sf::Vector2f kierunek = pozycja_myszy - srodek_gracza;

                // Tworzymy czerwony pocisk przez gracza
                pociski.push_back(std::make_unique<Pocisk>(srodek_gracza, kierunek, true, sf::Color::Red));
                gracz.reset_cooldown_strzalu();
            }
        }
    }
}
void Gra::handleGameOverEvents(sf::Event &event){
    {
        if(event.type == sf::Event::Closed){
                gameWindow.close();
        }
        if(event.type == sf::Event::TextEntered)
        {
            char c = static_cast<char>(event.text.unicode);

            // BACKSPACE
            if(c == 8)
            {
                if(!enteredName.empty())
                    enteredName.pop_back();
            }
            // NORMALNE ZNAKI
            else if(c >= 32 && c <= 126)
            {
                if(enteredName.size() < 12)
                    enteredName += c;
            }
        }

        // ENTER = zapis
        if(event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Enter)
        {
            if(enteredName.empty())
            { enteredName = "Player";}

            leaderboard.add_wynik(enteredName, wynik);
            resetGame();
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

    return LevelModule(sf::Vector2f(szerokosc_okna_gry,wysokosc_okna_gry/tilenumber),&texture_men.load(TextureID::Platform),&texture_men.load(TextureID::Torch),sf::IntRect(0,0,32,32),platforms,position);
}

std::list<std::unique_ptr<LevelModule>> Gra::createLevels(unsigned int nolevels){ // tworzy n początkowych modułów platform
    std::list<std::unique_ptr<LevelModule>> list;
    for(unsigned int i = 0; i < nolevels; ++i){
        list.emplace_front(std::make_unique<LevelModule>(createLevel(i)));
    }
    return list;
}
void Gra::startGameplay()
{
    enemies.clear();
    wynik = 0;

    for(auto lvl = levels.begin();*lvl!=levels.back();lvl++)
    {
        generujPrzeciwnikowDlaModulu(*lvl->get());
    }
    pasek_boczny.setWynik(leaderboard.get_as_string());

    stan = stanGry::Rozgrywka;
}
void Gra::gameOver(){
    stan = stanGry::GameOver;
    enteredName.clear();
    enemies.clear();
}
void Gra::resetGame()
{
    enemies.clear();
    wynik = 0;

    gracz = Gracz();

    levels = createLevels(9);
    pasek_boczny.setWynik(leaderboard.get_as_string());
    stan = stanGry::Menu;
}
void Gra::animacjaTla(){
    for(auto& a : levels){
        a->animate();
    }
}

void Gra::updateGameplay(float dt){
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

    // usuwanie pociskow (poza ekranem, kolizja z platformami, kolizja z graczem)
    pociski.erase(std::remove_if(pociski.begin(), pociski.end(), [this](const std::unique_ptr<Pocisk>& p) {
        if (!p) return true;

        //Warunek wyjścia poza ekran
        if (p->pobierz_granice().top > wysokosc_okna_gry || p->pobierz_granice().top + p->pobierz_granice().height < 0.f)
            return true;

        // Warunek kolizji z platformami
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

        /* STARY KOD - ZAKOMENTOWANY ZGODNIE Z ZALECENIEM
        if (pocisk_box.intersects(gracz.pobierz_granice()))
        {
            gracz.otrzymaj_obrazenia(10);
            return true; // kolizja z graczem
        }
        */
        // Kolizja pocisku wroga z graczem
        if (!p->czy_przez_gracza() && pocisk_box.intersects(gracz.pobierz_granice()))
        {
            gracz.otrzymaj_obrazenia(10); // Obrażenia od pocisku wroga
            return true; // kolizja z graczem
        }

        // Kolizja pocisku gracza z przeciwnikami
        if (p->czy_przez_gracza())
        {
            for (auto& e : enemies)
            {
                if (e && pocisk_box.intersects(e->pobierz_granice()))
                {
                    e->otrzymaj_obrazenia(gracz.pobierz_obrazenia_dystansowe()); // Obrażenia dystansowe gracza
                    return true; // kolizja z wrogiem
                }
            }
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
                wynik++;
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

    //atak goblina z cooldownem
    {
        sf::FloatRect gracz_box = gracz.pobierz_granice();
        for (auto& e : enemies)
        {
            if (e && e->pobierz_typ() == TypPrzeciwnika::Goblin && gracz_box.intersects(e->pobierz_granice()))
            {
                if (e->moze_atakowac())
                {
                    gracz.otrzymaj_obrazenia(e->pobierz_obrazenia());
                    e->uruchom_cooldown_ataku(1.2f); // 1.2 sekundy przerwy przed kolejnym atakiem
                }
                break;
            }
        }
    }

    // usun przeciwnika jezeli zejdzie ponizej ekranu lub zostanie zabity
    /*
    enemies.remove_if([this](const std::unique_ptr<Enemy>& e) {
        return e && e->pobierz_granice().top > wysokosc_okna_gry;
    });
    */

    enemies.remove_if([this](const std::unique_ptr<Enemy>& e) {
        return e && (e->czy_martwy() || e->pobierz_granice().top > wysokosc_okna_gry);
    });
    if(gracz.pobierz_hp() <= 0){
        gameOver();
    }
}

void Gra::generujPrzeciwnikowDlaModulu(LevelModule& modul)
{
    // generuj przeciwnika z 30% szansy na platformie
    for (const auto& platforma : modul.getPlatforms())
    {

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
                bounds.left + bounds.width//,
                //TypPrzeciwnika::Goblin
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
