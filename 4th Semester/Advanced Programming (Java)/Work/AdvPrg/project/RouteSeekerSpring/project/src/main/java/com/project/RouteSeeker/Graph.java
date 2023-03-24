package com.project.RouteSeeker;

import java.util.ArrayList;
import java.util.List;

public class Graph {
    private static ArrayList<Node> nodes = new ArrayList<>();
    private static ArrayList<Edge> edges = new ArrayList<>();
    private static ArrayList<Edge> resultEdges = new ArrayList<>();

    private int adjMat[][];

    public void addNode(Node newNode){
        nodes.add(newNode);
    }

    public void addEdge(Edge newEdge){
        edges.add(newEdge);
    }

    @Override
    public String toString() {
        return "Graph{" +
                "nodes=" + nodes +
                ", edges=" + edges +
                '}';
    }

    public static ArrayList<Node> getNodes() {
        return nodes;
    }

    public void setNodes(ArrayList<Node> nodes) {
        this.nodes = nodes;
    }

    public static ArrayList<Edge> getEdges() {
        return edges;
    }

    public void setEdges(ArrayList<Edge> edges) {
        this.edges = edges;
    }

    public static Node getNodeById(int id){
        for (Node n: nodes){
            if(n.getId() == id){
                return n;
            }
        }
        return null;
    }


    public static int getWeightBetweenNodes(Node src, Node dest){
        for(Edge e:edges){
            if(e.getSrc() == src && e.getDest() == dest){
                return e.getWeight();
            }
        }
        return 0;
    }

    public static ArrayList<Edge> getResultEdges() {
        return resultEdges;
    }

    public static void setResultEdges(ArrayList<Edge> resultEdges) {
        Graph.resultEdges = resultEdges;
    }
}
