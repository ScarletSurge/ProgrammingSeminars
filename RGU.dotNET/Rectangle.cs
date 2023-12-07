namespace RGU.dotNET;

public class Rectangle
{
    private double _length, _width;

    public Rectangle(
        double length,
        double width)
    {
        _length = length;
        _width = width;
    }

    public Rectangle(
        double length):
        this(length, length)
    {
        
    }
}

public class Square :
    Rectangle
{
    public Square(
        double length)
        : base(length)
    {
        
    }
}