import connectionDB.Database;
import entities.Edge;
import entities.Graf;
import entities.Node;
import graphics.MainFrame;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import java.sql.Array;
import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        Database.initializeEntityManagerFactory();

        EntityManagerFactory emf = Database.getEntityManagerFactory();

        EntityManager em = emf.createEntityManager();
        Graf graph = new Graf();
        List<Node> nodes = new ArrayList<>();
        nodes = em.createNamedQuery("Node.findAll").getResultList();

        for(Node n: nodes){
            graph.addNode(n);
        }

        List<Edge> edges = new ArrayList<>();
        edges = em.createNamedQuery("Edge.findAll").getResultList();

        for(Edge e : edges){
            graph.addEdge(e);
        }

        System.out.println(graph.toString());

        MainFrame mainFrame = new MainFrame();
        mainFrame.setVisible(true);
    }
}
