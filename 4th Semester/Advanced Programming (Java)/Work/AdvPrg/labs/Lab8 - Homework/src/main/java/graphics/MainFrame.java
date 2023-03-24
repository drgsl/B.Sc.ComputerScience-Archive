package graphics;
import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.io.IOException;
import java.sql.SQLException;

import static java.awt.BorderLayout.*;

public class MainFrame extends JFrame {
    DrawingPanel canvas;

    public MainFrame() throws IOException, SQLException {
        super("World Map");
        this.setIconImage(ImageIO.read(new File("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\teo\\Lab8 - Homework\\src\\main\\resources\\Mercator.jpg")));
        init();
    }

    private void init() throws SQLException {
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        canvas= new DrawingPanel(this);
        add(canvas, CENTER);

        pack();
    }
}

