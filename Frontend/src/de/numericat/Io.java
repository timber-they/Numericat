package de.numericat;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.*;

public final class Io {

    public static String outputPath;
    private static int currentLine = 0;

    private static Queue<List<List<Coordinate>>> buffer;

    private static final int refreshInterval = 10;
    private static final int bufferSize = 10;

    private static final Object lock = new Object();

    static double[] getScalingFactor(double height) {
        double[] scalingFactor = {0.0,0.0};
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
        while(scanner.hasNextLine()) {
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

    static List<List<Coordinate>> getBufferedData(final double[] scalingFactor){
        synchronized (lock) {
            if (buffer == null) {
                buffer = new LinkedList<>();
                Timer timer = new Timer();
                timer.schedule(new TimerTask() {
                    @Override
                    public void run() {
                        refreshData(scalingFactor);
                    }
                }, 0, refreshInterval);
            }
        }

        while (buffer.isEmpty()) {
            System.out.println("Buffer not up to date, have to wait");
            try {
                synchronized (lock) {
                    lock.wait();
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        synchronized (lock) {
            return buffer.remove();
        }
    }

    static void refreshData(double[] scalingFactor){
        while (buffer.size() < bufferSize) {
            synchronized (lock) {
                List<List<Coordinate>> data = getData(scalingFactor);
                if (data == null) {
                    reset();
                    continue;
                }
                buffer.add(data);
                lock.notify();
            }
        }
    }

    static List<List<Coordinate>> getData(double[] scalingFactor) {
        String line;
        String potentialLine;
        FileInputStream fis = null;
        Scanner sc = null;
        try {
            try {
                fis = new FileInputStream(outputPath);
                sc = new Scanner(fis);

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
            res.add(lineToCoordinates(line, scalingFactor[0]));
            if (potentialLine == null) {
                System.err.println("Didn't find potential line");
                return res;
            }
            res.add(lineToCoordinates(potentialLine, scalingFactor[1]));
            try {
                fis.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return res;
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

    private static List<Coordinate> lineToCoordinates(String line, double scalingFactor) {
        String[] split = line.split(" ");
        List<Coordinate> calculated = new ArrayList<>(split.length);

        for (int i = 0; i < split.length; i++) {
            calculated.add(new Coordinate(i + 1, scalingFactor * Double.parseDouble(split[i])));
        }
        return calculated;
    }

    static void reset(){
        currentLine = 0;
    }
}
