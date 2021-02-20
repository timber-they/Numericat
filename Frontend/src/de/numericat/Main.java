package de.numericat;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.Scanner;

public class Main {

    private static Numericanvas canvas;
    private static Timer timer;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Expected path to output file of backend");
            return;
        }
        Io.outputPath = args[0];
        System.out.println("Got output file: " + Io.outputPath);
        createWindow();

        final double[] scalingFactor =  Io.getScalingFactor(canvas.getHeight());
        ActionListener action = e -> {
            List<List<Coordinate>> data = Io.getData(scalingFactor);
            if (data == null) {
                Io.reset();
                return;
            }
            canvas.drawMultipleData(data);
        };
        timer = new Timer(10, action);
        timer.start();
    }

    private static void createWindow() {

        //Create and set up the window
        JFrame frame = new JFrame("Visualisation");
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
