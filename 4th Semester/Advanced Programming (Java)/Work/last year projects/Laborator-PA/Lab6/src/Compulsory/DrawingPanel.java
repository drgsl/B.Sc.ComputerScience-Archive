package Compulsory;

import Optional.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.image.BufferedImage;

public class DrawingPanel extends JPanel {
    final MainFrame frame;
    final static int W = 800, H = 600;

    BufferedImage image; //the offscreen image
    Graphics2D graphics; //the "tools" needed to draw in the image

    public DrawingPanel(MainFrame frame) {
        this.frame = frame;
        createOffscreenImage();
        init();
    }
    private void createOffscreenImage() {
        image = new BufferedImage(W, H, BufferedImage.TYPE_INT_ARGB);
        graphics = image.createGraphics();
        graphics.setColor(Color.WHITE);
        graphics.fillRect(0, 0, W, H);
    }
    private void init() {
        setPreferredSize(new Dimension(W, H));
        setBorder(BorderFactory.createEtchedBorder());
        this.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {

                if (!getTypeOfDrawing().equals("Free Drawing")) {
                    frame.addDrawnImage(frame.canvas.image);
                    drawShape(e.getX(), e.getY());
                }
                else {
                    freeDraw(e.getX(), e.getY());
                }
                repaint();
            }
        });
        this.addMouseMotionListener(new MouseMotionListener() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (!getTypeOfDrawing().equals("Free Drawing")) {
                    return;
                }
                freeDraw(e.getX(), e.getY());
                repaint();
            }
            @Override
            public void mouseMoved(MouseEvent e) {

            }
        });

    }
    private void drawShape(int x, int y) {
        int size = (int) frame.getConfigPanel().sizeField.getValue();
        int sides = (int) frame.getConfigPanel().sidesField.getValue();


        graphics.setColor(getColorType());

        switch (getTypeOfDrawing()) {
            case "Regular Polygon" -> graphics.fill(new RegularPolygon(x, y, size, sides));
            case "Bowtie" -> graphics.fill(new Bowtie(x, y, size / 10));
            case "Snowflake" -> graphics.fill(new Snowflake(x, y, size / 10));
        }
    }
    private void freeDraw(int x, int y) {
        graphics.setColor(getColorType());
        int size = (int) frame.getConfigPanel().sizeField.getValue();
        graphics.fillOval(x, y, size, size);
    }

    private Color getColorType() {
        if (frame.getConfigPanel().colorCombo.getSelectedItem().toString().equals("Random")) {
            return new Color((int) (Math.random() * 255),(int) (Math.random() * 255),(int) (Math.random() * 255), (int) (Math.random() * 200 + 50));
        }
        return new Color(0, 0, 0);
    }

    public String getTypeOfDrawing() {
        //return (String) frame.getConfigPanel().shapeList.getSelectedItem();
        return frame.getShapePanel().getSelectedItem();
    }

    @Override
    public void update(Graphics g) { }

    @Override
    protected void paintComponent(Graphics g) {
        g.drawImage(image, 0, 0, this);
    }

}

