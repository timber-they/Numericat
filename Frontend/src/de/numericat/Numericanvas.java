package de.numericat;


import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class Numericanvas extends JPanel
{
    private List<Coordinate> coordinates = new ArrayList<>(0);

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.BLACK);
        for (int i = 1; i < coordinates.size(); i++)
            g.drawLine(coordinates.get(i-1).roundX(), getSize().height - coordinates.get(i-1).roundY(),
                    coordinates.get(i).roundX(), getSize().height - coordinates.get(i).roundY());
    }

    public void drawData(List<Coordinate> coordinates) {
        this.coordinates = coordinates;
        repaint();
    }
}
