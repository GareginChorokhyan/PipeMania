#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

using Shape = std::vector<std::vector<char>>;

namespace Objects
{
    enum ShapeType
    {
        LeftRight,
        TopDown,
        RightTop,
        LeftTop,
        LeftDown,
        RightDown,
        Start,
        End
    };

    class Object
    {
    public:
        ShapeType type;
        int direct;

    public:
        Object(ShapeType newType) : type(newType){}
        virtual ~Object(){}

    public:
        virtual Shape getShape() const = 0;
        virtual int getDirection() const = 0;
        virtual void setDirection(int) = 0;
        virtual void generateShape() = 0;
        virtual void rotate() = 0;
        virtual void fill() = 0;
        virtual void unfill() = 0;  
        ShapeType getType() const
        {
            return type;
        }
    };
} // namespace Object

#endif // OBJECT_HPP