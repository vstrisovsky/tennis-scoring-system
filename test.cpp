#include <variant>
#include <iostream>

enum Player : unsigned short
{
    _PlayerOne, _PlayerTwo
};

enum Point : unsigned short
{
    _love, _15, _30
};

struct Points
{
    Point p1{_love};
    Point p2{_love};
};

struct Forty
{
    Player player;
    Point p2;
};

struct Deuce
{
};

struct Advantage
{
    Player player;
};

struct Game
{
    Player player;
};

using Score = std::variant<Points, Forty, Deuce, Advantage, Game>;

void printScore(const Points& score)
{
    auto point2string = [](const Point& point) -> std::string
    {
        switch(point)
        {
            case _love: return "love";
            case _15: return "15";
            case _30: return "30";
        }
    };

    std::cout << point2string(score.p1) << " : " << point2string(score.p2) << '\n';
}

std::string player2string(Player player)
{
    switch(player)
    {
        case _PlayerOne:
            return "one";
        case _PlayerTwo:
            return "two";
    }
}

void printScore(const Deuce& score)
{
    std::cout << "Deuce\n";
}

void printScore(const Advantage& score)
{
    std::cout << "Advantage player " << player2string(score.player) << "\n";
}

void printScore(const Game& score)
{
    std::cout << "Game player " << player2string(score.player) << "\n";
}

Score pointPlayerOne(const Points& score)
{
    switch(score.p1)
    {
        case _love: return Points{_15, score.p2};
        case _15:   return Points{_30, score.p2};
        case _30:   return Forty{_PlayerOne, score.p2};
    }
}

Score pointPlayerTwo(const Points& score)
{
    switch(score.p2)
    {
        case _love: return Points{score.p1, _15};
        case _15:   return Points{score.p1, _30};
        case _30:   return Forty{_PlayerTwo, score.p1};
    }
}

Score pointPlayerOne(const Deuce& score)
{
    return Advantage{_PlayerOne};
}

Score pointPlayerTwo(const Deuce& score)
{
    return Advantage{_PlayerTwo};
}

Score pointPlayerOne(const Advantage& score)
{
    switch(score.player)
    {
        case _PlayerOne: return Game{_PlayerOne};
        case _PlayerTwo: return Deuce();
    }
}

Score pointPlayerTwo(const Advantage& score)
{
    switch(score.player)
    {
        case _PlayerOne: return Deuce();
        case _PlayerTwo: return Game{_PlayerTwo};
    }
}

Score pointPlayerOne(const Score& score)
{
    Score result;
    std::visit([&result](const auto& s){ result = pointPlayerOne(s);}, score);
    return result;
}

Score pointPlayerTwo(const Score& score)
{
    Score result;
    std::visit([&result](const auto& s){ result = pointPlayerTwo(s);}, score);
    return result;
}

void printScore(const Score& score)
{
    std::visit([](const auto& s){ printScore(s);}, score);
}

int main()
{
    Score s;
    printScore(s);
    s = pointPlayerOne(s);
    printScore(s);
    s = pointPlayerOne(s);
    printScore(s);
    s = pointPlayerOne(s);
    printScore(s);
    s = pointPlayerTwo(s);
    printScore(s);
    s = pointPlayerTwo(s);
    printScore(s);
    s = pointPlayerTwo(s);
    printScore(s);
    s = pointPlayerOne(s);
    printScore(s);
    s = pointPlayerTwo(s);
    printScore(s);
    return 0;
}