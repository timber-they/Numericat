package de.numericat;

import javax.swing.*;
import java.awt.*;

public class Main {

    public static void main(String[] args) {
        createWindow();
    }

    private static void createWindow(){

        //Create and set up the window
        JFrame frame = new JFrame ("simple GUI");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        JLabel textLabel = new JLabel("Im cool" ,SwingConstants.CENTER);
        textLabel.setPreferredSize(new Dimension(300, 100));
        frame.getContentPane().add(textLabel, BorderLayout.CENTER);
        //Display the window
        frame.setLocationRelativeTo(null);
        frame.pack();
        frame.setVisible(true);
    }
}
