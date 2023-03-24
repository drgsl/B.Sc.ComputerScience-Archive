package project;

import java.util.ArrayList;
import java.util.List;

public class City {
    List<List<Intersection>> adjacencyList = new ArrayList<>();

    public List<List<Intersection>> getAdjacencyList() {
        return adjacencyList;
    }

    public void setAdjacencyList(List<List<Intersection>> adjacencyList) {
        this.adjacencyList = adjacencyList;
    }

    public City(List<Street> streets) {
        // adjacency list memory allocation
        for (int i = 0; i < streets.size(); i++)
            adjacencyList.add(i, new ArrayList<>());

        // add edges to the graph
        for (Street s : streets)
        {
            // allocate new node in adjacency List from src to dest
            adjacencyList.get(s.getSrc()).add(new Intersection(s.getDest()));
        }
    }

    // print adjacency list for the graph
    public static void printGraph(City city)  {
        int src_vertex = 0;
        int list_size = city.getAdjacencyList().size();

        System.out.println("The contents of the graph:");
        while (src_vertex < list_size) {
            //traverse through the adjacency list and print the edges
            for (Intersection edge : city.getAdjacencyList().get(src_vertex)) {
                System.out.print("Vertex:" + src_vertex + " ==> " + edge.getId() +
                        "\t");
            }

            System.out.println();
            src_vertex++;
        }
    }
}
