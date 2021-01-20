package de.numericat;

import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import java.awt.*;
import java.util.Objects;
import java.util.Scanner;

public class Main {

    private static Numericanvas canvas;
    private static String outputPath;
    private static Timer timer;

    public static void main(String[] args) {
        if (args.length < 1)
        {
            System.err.println("Expected path to output file of backend");
            return;
        }
        outputPath = args[0];
        System.out.println("Got output file: " + outputPath);
        createWindow();

        ActionListener action = e -> {
            List<Coordinate> data = getData();
            if (data == null)
            {
                if (timer != null)
                    timer.stop();
                return;
            }
            canvas.drawData(data);
        };
        timer = new Timer(10, action);
        timer.start();
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

    private static int currentLine = 0;
    private static List<Coordinate> getData()
    {
        String line = null;
        FileInputStream fis;
        try
        {
            fis = new FileInputStream(outputPath);
            Scanner sc = new Scanner(fis);
            int i;
            if (sc.hasNextLine())
                line = sc.nextLine();
            for (i = 0; i < currentLine && sc.hasNextLine(); i++, line = sc.nextLine())
                if (Objects.equals(line, ""))
                    break;
            if (i != currentLine)
            {
                System.err.println("Reached end of file");
                return null;
            }
        } catch (FileNotFoundException e)
        {
            e.printStackTrace();
            return null;
        }
        if (line == null || Objects.equals(line, ""))
        {
            System.out.println("Invalid line: " + line);
            return null;
        }

        currentLine++;
        String[] split = line.split(" ");
        System.out.println("Got " + split.length + " data points");
        List<Coordinate> res = new ArrayList<>(split.length);
        for (int i = 0; i < split.length; i++)
        {
            double el = Double.parseDouble(split[i]);
            res.add(new Coordinate(i + 1, el));
        }
        return res;
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
