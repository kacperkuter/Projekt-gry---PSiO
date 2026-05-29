
#include "../include/menadzer_tekstur.h"
Menadzer_tekstur::Menadzer_tekstur(){}
void Menadzer_tekstur::set(TextureID object, const std::string& file){
        std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

        if(texture->loadFromFile(file)){
            texture->setRepeated(true);
            this->textures[object] = std::move(texture);
        }
        else{
            throw std::runtime_error("Nie mozna zaladowac tekstury: "+file);
        }
}
void Menadzer_tekstur::set(TextureID object, sf::Texture a_texture){
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>(a_texture);
    if(texture){
        textures[object] = std::move(texture);
    }
}
sf::Texture& Menadzer_tekstur::load(TextureID id){
    if(textures[id]==nullptr){
        throw std::runtime_error("Brak przypisanej tekstury");
    }
    return *textures[id];
}
void Menadzer_tekstur::UpdateRender(
    sf::RenderTexture& target,
    const std::vector<TextureID>& row
    ){
    sf::RenderTexture temp;

    temp.create(
        target.getSize().x,
        target.getSize().y
        );

    float tileSize =
        static_cast<float>(target.getSize().x) / row.size();

    // przesunięcie starego obrazu
    sf::Sprite old(target.getTexture());

    old.setPosition(0, tileSize);

    temp.clear(sf::Color::Transparent);
    temp.draw(old);

    // nowy rząd
    sf::Sprite tile;

    for(int x = 0; x < row.size(); ++x)
    {
        tile.setTexture(*textures[row[x]]);

        tile.setScale(
            tileSize / tile.getTexture()->getSize().x,
            tileSize / tile.getTexture()->getSize().y
            );

        tile.setPosition(
            x * tileSize,
            0
            );

        temp.draw(tile);
    }

    temp.display();

    // zapis do target
    target.clear(sf::Color::Transparent);

    sf::Sprite result(temp.getTexture());

    target.draw(result);

    target.display();
}
sf::Texture Menadzer_tekstur::texturemap(float _windowsize_x,float _windowsize_y,
                                         const std::vector<std::vector<TextureID>>& _mapinfo,
                                         std::pair<float,float> _tilesize ){

    float windowsize_x = _windowsize_x;
    float windowsize_y = _windowsize_y;
    std::pair<float,float> tilesize = _tilesize;
    std::vector<std::vector<TextureID>> mapinfo = _mapinfo;

    if(tilesize.first==0&&tilesize.second==0){tilesize=std::make_pair(_windowsize_x/_mapinfo[0].size(),_windowsize_y/_mapinfo.size());}


    sf::RenderTexture cache;
    cache.create(windowsize_x, windowsize_y);
    sf::Sprite temp;
    cache.clear(sf::Color::Transparent);
    for(int i = 0; i<mapinfo.size();++i){
        for(int k = 0;k<mapinfo[i].size();++k){
            sf::Texture& t_info = *textures[mapinfo[i][k]];
            temp.setTexture(t_info);
            temp.setScale(
                tilesize.first/t_info.getSize().x,
                tilesize.second/t_info.getSize().y
                );
            temp.setPosition(tilesize.first*k,tilesize.second*i);
            cache.draw(temp);
        }
    }
    cache.display();
    sf::Texture resized_texture;
    resized_texture.loadFromImage(cache.getTexture().copyToImage());

    return resized_texture;}