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
            List<List<Coordinate>> data = getData();
            if (data == null)
            {
                if (timer != null)
                    timer.stop();
                return;
            }
            canvas.drawMultipleData(data);
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
    private static List<List<Coordinate>> getData()
    {
        String line = null;
        String lastLine = null;
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
            while (sc.hasNextLine())
            {
                lastLine = sc.nextLine();
                if (Objects.equals(line, "") && sc.hasNextLine())
                {
                    lastLine = sc.nextLine();
                    break;
                }
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
        List<List<Coordinate>> res = new ArrayList<>(2);
        res.add(lineToCoordinates(line));
        if (lastLine == null)
        {
            System.err.println("Didn't find potential line");
            return res;
        }
        res.add(lineToCoordinates(lastLine));
        System.out.println(line + "\n" + lastLine);
        return res;
    }

    private static List<Coordinate> lineToCoordinates(String line)
    {
        String[] split = line.split(" ");
//        System.out.println("Got " + split.length + " data points");
        List<Coordinate> calculated = new ArrayList<>(split.length);
        for (int i = 0; i < split.length; i++)
        {
            // TODO: Scale automatically
            double el = 500 * Double.parseDouble(split[i]);
            calculated.add(new Coordinate(i + 1, el));
        }

        return calculated;
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
