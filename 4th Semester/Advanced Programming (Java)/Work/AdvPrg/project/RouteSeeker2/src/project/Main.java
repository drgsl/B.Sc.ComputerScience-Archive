package project;

import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
// define edges of the graph
        List<Street> edges = Arrays.asList(new Street("Street1",0, 1, 2),
                new Street("Street2",0, 2, 4),
                new Street("Street3",1, 2, 4),
                new Street("Street4",2, 0, 5),
                new Street("Street5",2, 1, 4),
                new Street("Street6",3, 2, 3),
                new Street("Street7",4, 5, 1),
                new Street("Street8",5, 4, 3));

        // call graph class Constructor to construct a graph
        City graph = new City(edges);

        // print the graph as an adjacency list
        City.printGraph(graph);

        MainFrame mainFrame = new MainFrame();
        mainFrame.setVisible(true);
    }
}
