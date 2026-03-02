#ifndef PIPE_HPP
#define PIPE_HPP

#include "Object.hpp"

namespace Objects
{
    class Pipe : public Object
    {
    private:
        Shape pipe;

    public:
        Pipe(ShapeType newType);

    public:
        Shape getShape() const;
        int getDirection() const;
        void setDirection(int direct);
        void generateShape();
        void rotate();
        void fill();
        void unfill();
    };
} // namespace Object

#endif // PIPE_HPP