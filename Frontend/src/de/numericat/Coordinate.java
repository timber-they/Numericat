package de.numericat;

public class Coordinate
{
    private final double x;
    private final double y;

    public Coordinate(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public int roundX() {
        return (int) Math.round(x);
    }

    public int roundY() {
        return (int) Math.round(y);
    }
}
