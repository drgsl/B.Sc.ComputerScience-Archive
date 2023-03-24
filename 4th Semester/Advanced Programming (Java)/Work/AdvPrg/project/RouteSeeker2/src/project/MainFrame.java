package project;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.Stack;

import static java.awt.BorderLayout.CENTER;

public class MainFrame extends JFrame {
    ConfigPanel configPanel;
    ControlPanel controlPanel;
    DrawingPanel canvas;

    public MainFrame() {
        super("My Game");
        setSize(200,100);
        init();
    }

    private void init() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);


        configPanel = new ConfigPanel(this);
        controlPanel = new ControlPanel(this);
        canvas = new DrawingPanel(this);


        add(configPanel, BorderLayout.NORTH);
        add(canvas, BorderLayout.CENTER);
        add(controlPanel, BorderLayout.SOUTH);

        //arrange the components in the container (frame)
        //JFrame uses a BorderLayout by default
        add(canvas, CENTER); //this is BorderLayout.CENTER


        //invoke the layout manager
        pack(); //seteaza size
    }

    public ConfigPanel getConfigPanel() {
        return configPanel;
    }

    /**
     * Metoda ce salveaza graful in format png
     */
    public void save()  {
        //Constructs a BufferedImage of one of the predefined image types.
        BufferedImage bufferedImage = new BufferedImage(this.getSize().width, this.getSize().height, BufferedImage.TYPE_INT_RGB);
        Graphics g = bufferedImage.createGraphics();

        this.paint(g);
        g.dispose();

        try{
            ImageIO.write(bufferedImage,"png",
                    new File("SavedFrame.png"));}
        catch (Exception ignored) {}
    }
}
