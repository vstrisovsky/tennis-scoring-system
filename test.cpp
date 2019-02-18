#include <variant>
#include <iostream>

enum Point : unsigned short
{
    _love, _15, _30, _40 
};

struct PlayerOne {};
struct PlayerTwo {};

struct Points
{
    Point p1{_love};
    Point p2{_love};
};

struct Deuce
{
};

template<typename Player>
struct Advantage
{
};

template<typename Player>
struct Game
{
};

using Score = std::variant<Points, Deuce, Advantage<PlayerOne>, Advantage<PlayerTwo>, Game<PlayerOne>, Game<PlayerTwo>>;

void printScore(const Points& score)
{
    auto point2string = [](const Point& point) -> std::string
    {
        switch(point)
        {
            case _love: return "love";
            case _15: return "15";
            case _30: return "30";
            case _40: return "40";
        }
    };

    std::cout << point2string(score.p1) << " : " << point2string(score.p2) << '\n';
}

void printScore(const Deuce& score)
{
    std::cout << "Deuce\n";
}

void printScore(const Advantage<PlayerOne>& score)
{
    std::cout << "Advantage player one\n";
}

void printScore(const Advantage<PlayerTwo>& score)
{
    std::cout << "Advantage player one\n";
}

void printScore(const Game<PlayerOne>& score)
{
    std::cout << "Game player one\n";
}

void printScore(const Game<PlayerTwo>& score)
{
    std::cout << "Game player one\n";
}

Score pointPlayerOne(const Points& score)
{
    switch(score.p1)
    {
        case _love: return Points{_15, score.p2};
        case _15: return Points{_30, score.p2};
        case _30:
            if(score.p2 == _40)
                return Deuce();
            return Points{_40, score.p2};
        case _40: return Game<PlayerOne>();
    }
}

Score pointPlayerTwo(const Points& score)
{
    switch(score.p2)
    {
        case _love: return Points{score.p1, _15};
        case _15: return Points{score.p1, _30};
        case _30:
            if(score.p1 == _40)
                return Deuce();
            return Points{score.p2, _40};
        case _40: return Game<PlayerTwo>();
    }
}

Score pointPlayerOne(const Deuce& score)
{
    return Advantage<PlayerOne>();
}

Score pointPlayerTwo(const Deuce& score)
{
    return Advantage<PlayerTwo>();
}

Score pointPlayerOne(const Advantage<PlayerOne>& score)
{
    return Game<PlayerOne>();
}

Score pointPlayerTwo(const Advantage<PlayerOne>& score)
{
    return Deuce();
}

Score pointPlayerTwo(const Advantage<PlayerTwo>& score)
{
    return Game<PlayerTwo>();
}

Score pointPlayerOne(const Advantage<PlayerTwo>& score)
{
    return Deuce();
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