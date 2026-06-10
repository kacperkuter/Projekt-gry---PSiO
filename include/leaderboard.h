#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>
using TOP10 = std::vector<std::pair<std::string,unsigned int>>;
class Leaderboard
{
public:
    Leaderboard();
    std::string get_as_string();
    bool add_wynik(const std::string nazwa, const unsigned int wynik);
private:
    TOP10 TOP10;
};

#endif // LEADERBOARD_H
