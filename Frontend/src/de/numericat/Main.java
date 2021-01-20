package de.numericat;

import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import java.awt.*;

public class Main {

    private static Numericanvas canvas;

    public static void main(String[] args) {
        createWindow();
        new Timer(10, e -> canvas.drawData(getTestData())).start();
    }

    private static void createWindow(){

        //Create and set up the window
        JFrame frame = new JFrame ("Visualisation");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        canvas = new Numericanvas();
        frame.getContentPane().add(canvas);

        //Display the window
        frame.setLocationRelativeTo(null);
        frame.setPreferredSize(new Dimension(1000, 700));
        frame.pack();
        frame.setVisible(true);
    }

    // Just for demonstrational purposes - will later be removed
    private static final double dx = 1;
    private static final double maxX = 1000;
    private static double deltaX = 0;
    private static List<Coordinate> getTestData() {
        List<Coordinate> coordinates = new ArrayList<>((int) (maxX / dx));
        for (double x = 1; x < maxX; x += dx)
            coordinates.add(new Coordinate(x, (Math.sin((x-deltaX) / 50.0) + 1) * 200));
        deltaX++;
        return coordinates;
    }
}
