package com.project.RouteSeeker;

import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {

        Graph graph = new Graph();

        Node n1 = new Node(1, 100, 100);
        Node n2 = new Node(2, 200, 100);

        Node n3 = new Node(3, 300, 100);
        Node n4 = new Node(4, 200, 200);
        Node n5 = new Node(5, 400, 200);
        Node n6 = new Node(6, 300, 300);

        Node n7 = new Node(7, 100, 200);
        Node n8 = new Node(8, 200, 300);

        Node n9 = new Node(9, 500, 200);

        Node n10 = new Node(10, 400, 400);
        Node n11 = new Node(11, 500, 400);
        Node n12 = new Node(12, 600, 400);
        Node n13 = new Node(13, 550, 500);

        Edge e1 = new Edge(n1, n2, 4);
        Edge e2 = new Edge(n2, n3, 4);
        Edge e3 = new Edge(n3, n4, 2);
        Edge e4 = new Edge(n4, n6, 4);
        Edge e5 = new Edge(n3, n5, 2);
        Edge e6 = new Edge(n4, n7, 4);
        Edge e7 = new Edge(n7, n8, 4);
        Edge e8 = new Edge(n5, n9, 4);
        Edge e9 = new Edge(n6, n10, 4);
        Edge e10 = new Edge(n10, n11, 4);
        Edge e11 = new Edge(n11, n12, 4);
        Edge e12 = new Edge(n12, n13, 4);
        Edge e13 = new Edge(n13, n11, 4);
        Edge e14 = new Edge(n5, n6, 4);

        graph.addNode(n1);
        graph.addNode(n2);
        graph.addNode(n3);
        graph.addNode(n4);
        graph.addNode(n5);
        graph.addNode(n6);
        graph.addNode(n7);
        graph.addNode(n8);
        graph.addNode(n9);
        graph.addNode(n10);
        graph.addNode(n11);
        graph.addNode(n12);
        graph.addNode(n13);

        graph.addEdge(e1);
        graph.addEdge(e2);
        graph.addEdge(e3);
        graph.addEdge(e4);
        graph.addEdge(e5);
        graph.addEdge(e6);
        graph.addEdge(e7);
        graph.addEdge(e8);
        graph.addEdge(e9);
        graph.addEdge(e10);
        graph.addEdge(e11);
        graph.addEdge(e12);
        graph.addEdge(e13);
        graph.addEdge(e14);

        System.out.println(graph.toString());

        Solver.solve();
        //System.out.println(Solver.cycles[2]);
        //System.out.println(Solver.cycleCost(Solver.cycles[2]));

        Graph.setResultEdges(Solver.getCycleOfCost(12));

        MainFrame mainFrame = new MainFrame();
        mainFrame.setVisible(true);
    }
}
