#ifndef BOARD_HPP
#define BOARD_HPP

#include "../Objects/Pipe.hpp"

#include <vector>

using LevelInfo = std::vector<int>;
using ObjectMatrix = std::vector<std::vector<Objects::Object *>>;

namespace Screen
{
    struct Position
    {
        int x;
        int y;
    };

    class Board
    {
    private:
        ObjectMatrix board;
        int level;

    public:
        const int width = 20;
        const int height = 10;
        Position selected;
    public:
        Board();

    public:
        ObjectMatrix getBoard() const;
        void init(int level);
        void rotateSelected();
        bool checkWater();
        void clear();
        static Objects::ShapeType checkDirection(int,int);
    
    private:
        static Position getNextPosition(int currentDirecton, Position currentPosition);
        LevelInfo getLevelInfo(int level) const;
        static Objects::ShapeType getPipeTypeByDirection(int currentDirecton,int nextDirrection);   
    };
} // namespace Screen

#endif // BOARD_HPP
