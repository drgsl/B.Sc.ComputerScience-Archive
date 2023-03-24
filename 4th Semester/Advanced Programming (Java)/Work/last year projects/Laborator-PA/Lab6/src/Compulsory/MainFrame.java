package Compulsory;

import Optional.Bowtie;
import Optional.ShapePanel;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.nio.Buffer;
import java.util.Stack;

public class MainFrame extends JFrame {
    ConfigPanel configPanel;
    ControlPanel controlPanel;
    DrawingPanel canvas;
    ShapePanel shapePanel;



    // Stack for undo method
    Stack<BufferedImage> stackOfImages;

    public MainFrame() {
        super("PhotoBomb 2.0");
        stackOfImages = new Stack<>();
        init();
        stackOfImages.push(canvas.image);
    }

    private void init() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);

        configPanel = new ConfigPanel(this);
        canvas = new DrawingPanel(this);
        controlPanel = new ControlPanel(this);
        shapePanel = new ShapePanel(this);

        shapePanel.addShape("Regular Polygon");
        shapePanel.addShape("Bowtie");
        shapePanel.addShape("Snowflake");
        shapePanel.addShape("Free Drawing");

        add(configPanel, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER);
        add(controlPanel, BorderLayout.SOUTH);
        add(shapePanel, BorderLayout.EAST);

        pack();
    }

    public void addDrawnImage(BufferedImage img) {
        stackOfImages.push(img);
        System.out.println("added img");
    }

    public ConfigPanel getConfigPanel() {
        return configPanel;
    }

    public ControlPanel getControlPanel() {
        return controlPanel;
    }

    public DrawingPanel getCanvas() {
        return canvas;
    }

    public Stack<BufferedImage> getStackOfImages() {
        return stackOfImages;
    }

    public ShapePanel getShapePanel() {
        return shapePanel;
    }
}

