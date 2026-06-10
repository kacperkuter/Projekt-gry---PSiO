#include "leaderboard.h"
#include <algorithm>

Leaderboard::Leaderboard() : TOP10(10,std::pair<std::string,int>("-----",0)){}

bool Leaderboard::add_wynik(const std::string nazwa, const unsigned int wynik){
    auto it = std::find_if(TOP10.begin(),TOP10.end(),[wynik](const auto &a){return wynik >= a.second;});
    if(it==TOP10.end()){return false;}
    TOP10.insert(it,{nazwa,wynik});
    if(TOP10.size() > 10){
        TOP10.pop_back();
    }
    return true;
}
std::string Leaderboard::get_as_string(){
    std::string res = "TOP 10\n";
    for(auto i = TOP10.begin();i!=TOP10.end();++i){
        res = res+i->first+' '+std::to_string(i->second)+'\n';
    }
    return res;
}