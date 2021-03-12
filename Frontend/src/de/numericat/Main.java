package de.numericat;

import javax.swing.*;
import java.awt.*;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class Main {

    private static Numericanvas canvas;
    private static Timer timer;

    private static final Object lock = new Object();

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Expected path to output file of backend");
            return;
        }
        Io.outputPath = args[0];
        System.out.println("Got output file: " + Io.outputPath);
        createWindow();

        final double[] scalingFactor =  Io.getScalingFactor(canvas.getHeight());
        timer = new java.util.Timer();
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                List<List<Coordinate>> data = Io.getData(scalingFactor);
                canvas.drawMultipleData(data);
            }
        }, 0, 33);
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
