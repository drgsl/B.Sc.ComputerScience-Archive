package graphics;
import daos.CityDAO;
import model.City;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.sql.SQLException;

import static java.lang.Math.*;

public class DrawingPanel extends JPanel {
    final MainFrame frame;
    Integer canvasWidth = 720, canvasHeight = 720;
    Integer stoneSize= 5;
    BufferedImage image;
    Graphics2D offscreen;

    public DrawingPanel(MainFrame frame) throws SQLException {
        this.frame=frame;
        createOffScreenImage();
        init();
    }

    void createOffScreenImage ()
    {
        image = new BufferedImage(
                canvasWidth, canvasHeight, BufferedImage.TYPE_INT_ARGB);
        offscreen = image.createGraphics();
        try {
            offscreen.drawImage(ImageIO.read(new File("C:\\Users\\drago\\Desktop\\FII\\AP (JAVA)\\teo\\Lab8 - Homework\\src\\main\\resources\\Mercator.jpg")),0,0,canvasWidth,canvasHeight,frame);
        } catch (IOException ex) {
            ex.printStackTrace();
        }
    }

    void init () throws SQLException {
        setPreferredSize(new Dimension(canvasWidth, canvasHeight));
        CityDAO cityDAO= new CityDAO();
        Double latitude;
        Double longitude;
        Double x;
        Double y;
        Double latRad;
        Double mercN;
        for (City city : cityDAO.findAll())
        {
            latitude    = city.getLatitude();
            longitude   = city.getLongitude();

            x = (longitude+180)*(((double) canvasWidth)/360);

            latRad = latitude* PI/180;

            mercN = log(tan((PI/4)+(latRad/2)));
            y = (((double)canvasHeight)/2)-(canvasWidth*mercN/(2*PI));

            offscreen.setColor(Color.RED);
            offscreen.drawOval((int)(x - stoneSize), (int)(y - stoneSize), 5, 5);
            offscreen.setColor(Color.DARK_GRAY);
            offscreen.setFont(new Font(Font.SANS_SERIF,  Font.BOLD, 10));
            offscreen.drawString(city.getName(),(int)(x - stoneSize)+10, (int)(y - stoneSize));


        }
    }

    @Override
    protected void paintComponent (Graphics graphics)
    {
        graphics.drawImage(image, 0, 0, this);
    }

}
