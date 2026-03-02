#include "Window.hpp"

Window::Window(const Screen::Board& board) : board(board)
{
    initscr();
    curs_set(0);
    keypad(stdscr, true);
    getmaxyx(stdscr, height, width);
    halfdelay(5);
    noecho();
}

Window::~Window()
{
    endwin();
}

int Window::input() 
{
    return getch();
}

void Window::drawBoard() const
{    
    clear();
    refresh();
    const ObjectMatrix matrix = board.getBoard();

    for (int i = 0; i < (int)(matrix.size()-1) * 3; ++i)
    {
        for (int j = 0; j < (int)(matrix[0].size()-1) * 3; ++j)
        {
            if(i / 3 == board.selected.x && j / 3 == board.selected.y && i % 3 == 1 && j % 3 == 1)
                {
                    printw("*");
                    continue;
                }
            if (!matrix[i / 3][j / 3])
            {
                printw(".");
            }
            else
            {
                printw("%c",matrix[i / 3][j / 3]->getShape()[i % 3][j % 3]);
            }
            if((j+1) % 3 == 0)
            {
                printw("  ");
            }

        }
       if((i+1) % 3 == 0)
        {
            printw("\n");
        }  
       printw("\n");
    }

}

void Window::drawTime(int time) const
{
    printw("Timer:  00:%02d",time);
}

void Window::drawMenu(const Sections &sections, int selected) const
{
    clear();

    const int centerHeight = height / 2 - sections.size();
    const int centerWidth = width / 2 - 5;
    mvprintw(centerHeight-2,centerWidth,"Pipe Mania");
    for (int i = 0; i < (int)sections.size(); ++i)
    {
        if (selected == i)
        {
            mvprintw(centerHeight + i, centerWidth, "-%s\n", sections[i].c_str());
        }
        else
        {
            mvprintw(centerHeight + i, centerWidth, " %s\n", sections[i].c_str());
        }
    }

    refresh();
}

void Window::cleanWindow() const
{
    clear();
}

void Window::drawTextWin(const std::string &text) const
{
    mvprintw(35,0,"%s",text.c_str());
}

void Window::drawText(const std::string &text) const
{
    mvprintw(20,30,"%s",text.c_str());
}