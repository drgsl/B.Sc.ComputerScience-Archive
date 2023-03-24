package com.project.RouteSeeker;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.util.*;
import java.util.List;

/**
 * Clasa care genereaza tabla de joc (grid, cerculete, linii ingrosate)
 */

public class DrawingPanel extends JPanel {
    final MainFrame frame;
    int canvasWidth = 700, canvasHeight = 700, stoneSize=30;
    List<Line> lineList = new ArrayList<>();


    BufferedImage image; //the offscreen image
    Graphics2D offscreen; //the offscreen graphics
    public DrawingPanel(MainFrame frame) {
        this.frame = frame; createOffscreenImage(); init();
    }

    /**
     * Metoda care seteaza fundalul alb
     */
    private void createOffscreenImage() {
        image = new BufferedImage(
                canvasWidth, canvasHeight, BufferedImage.TYPE_INT_ARGB);
        offscreen = image.createGraphics();
        offscreen.setColor(Color.WHITE); //fill the image with white
        offscreen.fillRect(0, 0, canvasWidth, canvasHeight);
    }

    /**
     * Metoda care deseneaza liniile gridului si cerculetele din intersectii
     * @param g
     */
    public void paint(Graphics graphics) {
        for(Node node : Graph.getNodes()){
            graphics.drawOval(node.getX() - 5,node.getY() - 5,10,10);
            graphics.drawString("Text", 40, 120);
        }

        for(Edge edge : Graph.getEdges()){
            graphics.drawLine(edge.getSrc().getX(),edge.getSrc().getY(),edge.getDest().getX(),edge.getDest().getY());
        }
        System.out.println(Graph.getResultEdges());
        graphics.setColor(Color.green);
        for(Edge edge : Graph.getResultEdges()){
            graphics.drawLine(edge.getSrc().getX(),edge.getSrc().getY(),edge.getDest().getX(),edge.getDest().getY());
        }
    }

    private void init(){
        setPreferredSize(new Dimension(canvasWidth, canvasHeight));
        setBorder(BorderFactory.createEtchedBorder());
    }


    @Override
    public void update(Graphics g) { }

    //Draw the offscreen image, using the original graphics
    @Override
    protected void paintComponent(Graphics graphics) {
        graphics.drawImage(image, 0, 0, this);
    }
}
