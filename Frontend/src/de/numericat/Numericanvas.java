package de.numericat;

import javax.swing.*;
import java.awt.*;

public class Numericanvas extends JPanel
{
    private int posY1 = 10;
    private int posY2 = 690;

    @Override
    public void paintComponent(Graphics g)
    {
        super.paintComponent(g);
        g.setColor(Color.BLACK);
        g.drawLine(10, posY1++, 990, posY2--);
    }
}
