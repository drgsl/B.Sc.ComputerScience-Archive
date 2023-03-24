package panel;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import static java.awt.BorderLayout.CENTER;

public class MainFrame extends JFrame {
    ConfigPanel configPanel;
    ControlPanel controlPanel;

    public MainFrame() {
        super("Address Verifier");
        init();
    }

    private void init() {
        BufferedImage myImage = null;
        try {
            myImage = ImageIO.read(new File("background.jpg"));
        } catch (IOException e) {
            e.printStackTrace();
        }
        setContentPane(new ImagePanel(myImage));
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        configPanel = new ConfigPanel(this);
        configPanel.setLayout(new BoxLayout(configPanel, BoxLayout.PAGE_AXIS));
        configPanel.setBorder(BorderFactory.createEmptyBorder(50, 90, 200, 90));
        configPanel.setPreferredSize(new Dimension(600, 400));
        controlPanel = new ControlPanel(this);
        controlPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        configPanel.add(controlPanel);
        add(configPanel, CENTER);
        pack();
    }

    public ConfigPanel getConfigPanel() {
        return configPanel;
    }

}
