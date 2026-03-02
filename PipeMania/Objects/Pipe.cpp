#include "Pipe.hpp"
#include <vector>

Objects::Pipe::Pipe(ShapeType newType) : Object(newType)
{
    generateShape();
    setDirection((int)type);
}

Shape Objects::Pipe::getShape() const
{
    return pipe;
}

int Objects::Pipe::getDirection() const
{
    return direct;
}
void Objects::Pipe::setDirection(int direct)
{
    this->direct = direct;
}
void Objects::Pipe::generateShape()
{
    switch (type)
    {
    case ShapeType::TopDown:
        pipe = {
            {'#', ' ', '#'},
            {'#', ' ', '#'},
            {'#', ' ', '#'}};
        break;
    case ShapeType::LeftRight:
        pipe = {
            {'#', '#', '#'},
            {' ', ' ', ' '},
            {'#', '#', '#'}};
        break;
    case ShapeType::RightTop:
        pipe = {
            {'#', ' ', '#'},
            {'#', ' ', ' '},
            {'#', '#', '#'}};
        break;
    case ShapeType::LeftTop:
        pipe = {
            {'#', ' ', '#'},
            {' ', ' ', '#'},
            {'#', '#', '#'}};
        break;
    case ShapeType::RightDown:
        pipe = {
            {'#', '#', '#'},
            {'#', ' ', ' '},
            {'#', ' ', '#'}};
        break;
    case ShapeType::LeftDown:
        pipe = {
            {'#', '#', '#'},
            {' ', ' ', '#'},
            {'#', ' ', '#'}};
        break;
    case ShapeType::Start:
        pipe = {
            {'#', '-', '#'},
            {'-', ' ', '-'},
            {'#', '-', '#'}};
        break;
    case ShapeType::End:
        pipe = {
            {'#', '-', '#'},
            {'-', ' ', '-'},
            {'#', '-', '#'}};
        break;
    }
}

void Objects::Pipe::rotate()
{
    switch (type)
    {
    case ShapeType::TopDown:
        type = ShapeType::LeftRight;     
        break;
    case ShapeType::LeftRight:
        type = ShapeType::TopDown;  
        break;
    case ShapeType::RightTop:
        type = ShapeType::RightDown;  
        break;
    case ShapeType::LeftTop:
        type = ShapeType::RightTop;        
        break;
    case ShapeType::RightDown:
        type = ShapeType::LeftDown;  
        break;
    case ShapeType::LeftDown:
        type = ShapeType::LeftTop;  
        break;
    case ShapeType::Start:
    case ShapeType::End:
        break;
    }
    generateShape();
}

void Objects::Pipe::fill()
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(pipe[i][j] == ' ')
            {
                pipe[i][j] = '~';
            }
        }
    }
}

void Objects::Pipe::unfill()
{
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            if(pipe[i][j] == '~')
            {
                pipe[i][j] = ' ';
            }
        }
    }
}