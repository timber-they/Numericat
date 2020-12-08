package de.numericat;

import javax.swing.*;
import java.awt.*;

public class Main {

    private static Numericanvas canvas;

    public static void main(String[] args) {
        createWindow();
        new Timer(10, e -> canvas.repaint()).start();
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
}
