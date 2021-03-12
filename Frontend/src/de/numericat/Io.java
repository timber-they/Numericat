package de.numericat;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;

public final class Io {

    public static String outputPath;
    private static int currentLine = 0;
    private static List<List<List<Coordinate>>> allData = null;

    static double[] getScalingFactor(double height) {
        double[] scalingFactor = {0.0, 0.0};
        Scanner scanner = null;
        FileInputStream inputStream = null;
        try {
            inputStream = new FileInputStream(outputPath);
            scanner = new Scanner(inputStream);
            scalingFactor[0] = height / getMaximumOfBlock(scanner);
            scalingFactor[1] = height / getMaximumOfBlock(scanner);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } finally {
            try {
                if (inputStream != null)
                    inputStream.close();
                if (scanner != null)
                    scanner.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            System.out.println("Scaling Factor 1:" + scalingFactor[0]);
            System.out.println("Scaling Factor 2:" + scalingFactor[1]);
        }
        return scalingFactor;
    }

    private static double getMaximumOfBlock(Scanner scanner) {
        double maximum = 0;
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.isEmpty())
                break;
            String[] splitString = line.split(" ");
            for (int i = 0; i < splitString.length; i++) {
                double tmp_Parse = Double.parseDouble(splitString[i]);
                if (maximum < tmp_Parse) {
                    maximum = tmp_Parse;
                }
            }
        }
        return maximum;
    }

    private static List<Coordinate> lineToCoordinates(String line, double scalingFactor) {
        String[] split = line.split(" ");
        List<Coordinate> calculated = new ArrayList<>(split.length);

        for (int i = 0; i < split.length; i++) {
            calculated.add(new Coordinate(i + 1, scalingFactor * Double.parseDouble(split[i])));
        }
        return calculated;
    }

    static void reset() {
        currentLine = 0;
    }

    public static List<List<Coordinate>> getData(double[] scalingFactor) {
        if (allData == null)
            allData = readAllData(scalingFactor);
        if (allData == null)
            return null;
        if (currentLine >= allData.size())
            currentLine = 0;
        return allData.get(currentLine++);
    }

    private static List<List<List<Coordinate>>> readAllData(double[] scalingFactor) {
        FileInputStream fis = null;
        Scanner sc = null;
        try {
            List<List<List<Coordinate>>> res = new LinkedList<>();
            fis = new FileInputStream(outputPath);
            sc = new Scanner(fis);
            // Wavefunction
            String line;
            for (line = sc.nextLine(); sc.hasNextLine() && !line.isEmpty(); line = sc.nextLine()) {
                List<List<Coordinate>> data = new ArrayList<>(2);
                data.add(lineToCoordinates(line, scalingFactor[0]));
                res.add(data);
            }
            if (!sc.hasNextLine()) {
                System.err.println("Expected potential");
                return null;
            }

            // Potential
            line = sc.nextLine();
            for (int i = 0; i < res.size() && sc.hasNextLine(); i++, line = sc.nextLine()) {
                res.get(i).add(lineToCoordinates(line, scalingFactor[1]));
            }
            if (sc.hasNextLine()) {
                System.err.println("Didn't expect anymore potential lines");
            }
            return res;

        } catch (IOException e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                if (fis != null)
                    fis.close();
            } catch (IOException e) {
                e.printStackTrace();
            }

            if (sc != null)
                sc.close();
        }
    }
}
