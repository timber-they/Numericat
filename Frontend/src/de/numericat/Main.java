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
    private static String outputPath;
    private static Timer timer;

    public static void main(String[] args) {
        if (args.length < 1) {
            System.err.println("Expected path to output file of backend");
            return;
        }
        outputPath = args[0];
        System.out.println("Got output file: " + outputPath);
        createWindow();

        ActionListener action = e -> {
            List<List<Coordinate>> data = getData();
            if (data == null) {
                currentLine = 0;
//                if (timer != null)
//                    timer.stop();
//                return;
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

    private static boolean skipLines(Scanner scanner, int lines) {
        for (int i = 0; i < lines; i++)
            if (!scanner.hasNextLine())
                return false;
            else
                scanner.nextLine();
        return true;
    }

    private static boolean skipTillEmptyLine(Scanner scanner) {
        while (scanner.hasNextLine())
            if (scanner.nextLine().isEmpty())
                return true;
        return false;
    }

    private static int currentLine = 0;

    private static List<List<Coordinate>> getData() {
        String line;
        String potentialLine;
        FileInputStream fis;
        try {
            fis = new FileInputStream(outputPath);
            Scanner sc = new Scanner(fis);

            if (!skipLines(sc, currentLine) || !sc.hasNextLine())
                return null;
            line = sc.nextLine();

            if (!skipTillEmptyLine(sc) || !skipLines(sc, currentLine) || !sc.hasNextLine())
                return null;
            potentialLine = sc.nextLine();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return null;
        }
        if (line == null || Objects.equals(line, "")) {
            System.out.println("Invalid line: " + line);
            return null;
        }

        currentLine++;
        List<List<Coordinate>> res = new ArrayList<>(2);
        res.add(lineToCoordinates(line, 0));
        if (potentialLine == null) {
            System.err.println("Didn't find potential line");
            return res;
        }
        res.add(lineToCoordinates(potentialLine, 1));
        System.out.println(line + "\n" + potentialLine);
        try {
            fis.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return res;
    }

    private static double getMaximumOfBlock(Scanner scanner) {
        double maximum = 0;
        String line = null;
        while(true) {
            line = scanner.nextLine();
            if(line != "" && scanner.hasNextLine())
            {
                String[] splitString = line.split(" ");
                for (int i = 0; i < splitString.length; i++) {
                    double tmp_Parse = Double.parseDouble(splitString[i]);
                    if (maximum < tmp_Parse) {
                        maximum = tmp_Parse;
                    }
                }
            }
            else
            {
                break;
            }
        }
        return maximum;
    }

    private static double[] getScalingFactor(String outputPath) {
        double[] scalingFactor = {0.0,0.0};
        Scanner scanner = null;
        FileInputStream inputStream = null;
        try {
            inputStream = new FileInputStream(outputPath);
            scanner = new Scanner(inputStream);
            scalingFactor[0] = getMaximumOfBlock(scanner);
            scalingFactor[1] = getMaximumOfBlock(scanner);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            scanner.close();
            try {
                inputStream.close();
                scanner.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("Scaling Factor 1:" + scalingFactor[0]);
            System.out.println("Scaling Factor 2:" + scalingFactor[1]);
        }
        return scalingFactor;
    }

    private static List<Coordinate> lineToCoordinates(String line, int idx) {
        String[] split = line.split(" ");
        double el = 0;
        double height = canvas.getHeight();
//      System.out.println("Got " + split.length + " data points");
        List<Coordinate> calculated = new ArrayList<>(split.length);
        double[] scalingFactor =  getScalingFactor(outputPath);
        for (int i = 0; i < split.length; i++) {
            el = (height / scalingFactor[idx]) * Double.parseDouble(split[i]);
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
            coordinates.add(new Coordinate(x, (Math.sin((x - deltaX) / 50.0) + 1) * 200));
        deltaX++;
        return coordinates;
    }
}
