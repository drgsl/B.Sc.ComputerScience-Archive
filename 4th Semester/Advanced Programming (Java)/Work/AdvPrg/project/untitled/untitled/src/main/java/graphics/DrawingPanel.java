package graphics;

import entities.Edge;
import entities.Graf;
import entities.Node;
import entities.Solver;

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
    int canvasWidth = 1800, canvasHeight = 900, stoneSize=30;
    List<Line> lineList = new ArrayList<>();


    BufferedImage image; //the offscreen image
    Graphics2D offscreen; //the offscreen graphics
    //private Graf graf;

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


    public void paint(Graphics graphics) {

        Solver.solve();
        //System.out.println(entities.Solver.cycles[2]);
        //System.out.println(entities.Solver.cycleCost(entities.Solver.cycles[2]));

        Graf.setResultEdges(Solver.getCycleOfCost(ConfigPanel.requestedCost));

        for(Node node : Graf.getNodes()){
            graphics.setColor(Color.BLACK);
            graphics.drawOval(node.getX() - 5,node.getY() - 5,10,10);
            graphics.setColor(Color.red);
            graphics.drawString(node.getId()+" ",node.getX() - 5,node.getY() - 5);
        }

        for(Edge edge : Graf.getEdges()){
            graphics.setColor(Color.black);
            graphics.drawLine(edge.getSrc().getX(),edge.getSrc().getY(),edge.getDest().getX(),edge.getDest().getY());
            int x = (edge.getSrc().getX() + edge.getDest().getX()) / 2;
            int y = (edge.getSrc().getY() + edge.getDest().getY()) / 2;
            graphics.setColor(Color.blue);
            System.out.println(x + " " + y);
            graphics.drawString(edge.getWeight()+"km",x,y-10);
            graphics.drawString(edge.getName()+" ",x,y);
        }
        System.out.println(Graf.getResultEdges());
        graphics.setColor(Color.green);
        for(Edge edge : Graf.getResultEdges()){
            graphics.drawLine(edge.getSrc().getX(),edge.getSrc().getY(),edge.getDest().getX(),edge.getDest().getY());
            graphics.drawOval(edge.getSrc().getX() - 5,edge.getSrc().getY() - 5,10,10);
            graphics.drawOval(edge.getDest().getX() - 5,edge.getDest().getY() - 5,10,10);
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
