#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Board/Board.hpp"
#include <ncurses.h>

#include <string>
#include <vector>

class Window
{
private:
    using Sections = std::vector<std::string>;
    
    const Screen::Board& board;
    int height;
    int width;

public:
    Window(const Screen::Board& board);
    ~Window();

public:
    void cleanWindow() const;
    void drawTextWin(const std::string &text) const;
    void drawText(const std::string &text) const;
    void drawBoard() const;
    void drawMenu(const Sections &, int selected) const;
    int static input();
    void drawTime(int) const;
};

#endif // WINDOW_HPP