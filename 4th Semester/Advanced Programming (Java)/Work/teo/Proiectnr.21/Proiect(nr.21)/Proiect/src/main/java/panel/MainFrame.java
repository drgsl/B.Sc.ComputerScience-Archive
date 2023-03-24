package panel;

import javax.imageio.ImageIO;
import javax.swing.*;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;

import static java.awt.BorderLayout.*;

public class MainFrame extends JFrame {
    ConfigPanel configPanel;
    ControlPanel controlPanel;

    public MainFrame() {
        super("My game");
        init();
    }

    private void init() {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        configPanel = new ConfigPanel(this);
        configPanel.setLayout(new BoxLayout(configPanel, BoxLayout.PAGE_AXIS));
        configPanel.setBorder(BorderFactory.createEmptyBorder(50,100,200,100));
        configPanel.setPreferredSize(new Dimension(600, 400));
        controlPanel = new ControlPanel(this);
        controlPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        add(configPanel,CENTER);
        add(controlPanel, SOUTH);
        pack();
    }

    public ConfigPanel getConfigPanel() {
        return configPanel;
    }

}
