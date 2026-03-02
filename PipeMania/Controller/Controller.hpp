#ifndef Controller_HPP
#define Controller_HPP

#include "../Objects/Pipe.hpp"
#include "../Window/Window.hpp"
#include "../Board/Board.hpp"
#include "../FileSystem/FileSystem.hpp"

#include <algorithm>
#include <string>
#include <vector>
#include <ctime>

enum Keys
{
    Up = 259,
    Down = 258,
    Left = 260,
    Right = 261, 
    Enter = 10,
    Esc = 27
};

class Controller
{
private:
    Screen::Board board;
    const Window win;
    int level = 0;
    int timer = 0;
    bool playQuit = false;

public:
    Controller() : win(board){}
    ~Controller() {}

public:
    int buttonCheck();

public:
    void play();
    void menu();
    void options();
    void records();
};

#endif // Controller_HPP
