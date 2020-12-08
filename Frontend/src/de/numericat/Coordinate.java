package de.numericat;

public class Coordinate
{
    // I don't care about encapsulation for coordinates
    public double x;
    public double y;

    public Coordinate(double x, double y)
    {
        this.x = x;
        this.y = y;
    }

    public int roundX()
    {
        return (int) Math.round(x);
    }

    public int roundY()
    {
        return (int) Math.round(y);
    }
}
