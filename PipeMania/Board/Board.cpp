#include "Board.hpp"
#include <ncurses.h>

Screen::Board::Board() : selected({0,0})
{   
    board = ObjectMatrix(height, std::vector<Objects::Object *>(width, 0));
};

LevelInfo Screen::Board::getLevelInfo(int level) const
{
    const static std::vector<LevelInfo> levels = {
        {5, 5, 1, 1, 2, 2, 3, 2,0},               // level1
        {5, 5, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 0},  // level2
        {0,0,1,1,2,2,3,2,2,1,1,1,4,4,0},          // level3
        {3,4,2,2,1,1,1,4,4,1,1,1,1,2,2,2,2,1,1,1,4,4,1,1,2,1,0},//level4
    };
    return levels[level];
}

Objects::ShapeType Screen::Board::getPipeTypeByDirection(int currentDirecton,int nextDirrection) 
{
    Objects::ShapeType type;

    if (currentDirecton == 0)
    {
        type = Objects::ShapeType::End;
    }
    else
    {
        if (nextDirrection != currentDirecton)
        {
            type = Objects::ShapeType::LeftDown;
        }
        else
        {
            type = Objects::ShapeType::TopDown;
        }
    }    
    return type;
}

void Screen::Board::init(int level)
{
    // clean board
    this->level = level;
    std::vector<int> pipeCords = getLevelInfo(level);
    const Position startPosition = {pipeCords[0], pipeCords[1]};

    board[startPosition.x][startPosition.y] = new Objects::Pipe(Objects::ShapeType::Start);

    int dirIndex = 2;
    Position currentPosition = startPosition;

    while (dirIndex != (int)pipeCords.size())
    {
        
        const int currentDirecton = pipeCords[dirIndex++];
        const int nextDirrection = pipeCords[dirIndex];

        currentPosition = getNextPosition(currentDirecton, currentPosition);
       
        const Objects::ShapeType type = getPipeTypeByDirection(currentDirecton,nextDirrection);
        
        board[currentPosition.x][currentPosition.y] = new Objects::Pipe(type);
}
    }

Screen::Position Screen::Board::getNextPosition(int currentDirecton, Position currentPosition)
{
    switch (currentDirecton)
    {
    case 1: // right
        currentPosition.y += 1;
        break;
    case 2: // down
        currentPosition.x += 1;
        break;
    case 3: // left
        currentPosition.y -= 1;
        break;
    case 4: // top
        currentPosition.x -= 1;
        break;
    }
    return currentPosition;
}

ObjectMatrix Screen::Board::getBoard() const
{
    return board;
}

void Screen::Board::rotateSelected()
{
    if(board[selected.x][selected.y])
        board[selected.x][selected.y]->rotate();
}

bool Screen::Board::checkWater()
{
    auto levelInfo = getLevelInfo(level);
    Position currentPosition = {levelInfo[0],levelInfo[1]};
    bool accessible = true;
    for(int i = 2;i < (int)getLevelInfo(level).size()-2; ++i)
    {
        currentPosition = getNextPosition(levelInfo[i],currentPosition);
        if(board[currentPosition.x][currentPosition.y]->getType() != checkDirection(levelInfo[i],levelInfo[i+1]) && accessible)
        { 
            accessible = false;
        }
        if(accessible)
        {
            board[currentPosition.x][currentPosition.y]->fill();
        }
        else
        {
            board[currentPosition.x][currentPosition.y]->unfill();
        } 
    }
    return accessible;
}

Objects::ShapeType Screen::Board::checkDirection(int dir_1,int dir_2)
{
    if(dir_1 == dir_2)
    {
        if(dir_1 == 2 || dir_1 == 4)
        {
            return Objects::ShapeType::TopDown;  
        }
        if(dir_1 == 1 || dir_1 == 3)
        {
            return Objects::ShapeType::LeftRight;
        }   
    }
    else 
    {
        if((dir_1 == 4 && dir_2 == 3) || (dir_1 == 1 && dir_2 == 2) )
        {
            return Objects::ShapeType::LeftDown;
        }
        if((dir_1 == 2 && dir_2 == 3) || (dir_1 == 1 && dir_2 == 4) )
        {
            return Objects::ShapeType::LeftTop;
        }
        if((dir_1 == 3 && dir_2 == 4) || (dir_1 == 2 && dir_2 == 1) )
        {
            return Objects::ShapeType::RightTop;
        }
        if((dir_1 == 3 && dir_2 == 2) || (dir_1 == 4 && dir_2 == 1) )
        {
            return Objects::ShapeType::RightDown;
        }
    }
    return Objects::ShapeType::End;
}

void Screen::Board::clear()
{
    for (auto &row : board)
    {
        for (auto &item : row)
        {
            if (item)
            {
                delete item;
                item = 0;
            }
        }
    }
}