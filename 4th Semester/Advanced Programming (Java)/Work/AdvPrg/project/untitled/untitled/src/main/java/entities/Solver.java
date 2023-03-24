package entities;

import entities.Edge;
import entities.Graf;

import java.util.ArrayList;
import java.util.Vector;

public class Solver {

    static final int N = 100000;

    // variables to be used
    // in both functions
    @SuppressWarnings("unchecked")
    static Vector<Integer>[] graph = new Vector[N];
    @SuppressWarnings("unchecked")
    static Vector<Integer>[] cycles = new Vector[N];
    static int cyclenumber;

    // Function to mark the vertex with
    // different colors for different cycles
    static void dfs_cycle(int u, int p, int[] color,
                          int[] mark, int[] par)
    {

        // already (completely) visited vertex.
        if (color[u] == 2)
        {
            return;
        }

        // seen vertex, but was not completely visited -> cycle detected.
        // backtrack based on parents to find the complete cycle.
        if (color[u] == 1)
        {

            cyclenumber++;
            int cur = p;
            mark[cur] = cyclenumber;

            // backtrack the vertex which are
            // in the current cycle thats found
            while (cur != u)
            {
                cur = par[cur];
                mark[cur] = cyclenumber;
            }
            return;
        }
        par[u] = p;

        // partially visited.
        color[u] = 1;

        // simple dfs on graph
        for (int v : graph[u])
        {

            // if it has not been visited previously
            if (v == par[u])
            {
                continue;
            }
            dfs_cycle(v, u, color, mark, par);
        }

        // completely visited.
        color[u] = 2;
    }

    // add the edges to the graph
    static void addEdge(int u, int v)
    {
        graph[u].add(v);
        graph[v].add(u);
    }

    // Function to print the cycles
    static void printCycles(int edges, int mark[])
    {

        // push the edges that into the
        // cycle adjacency list
        for (int i = 1; i <= edges; i++)
        {
            if (mark[i] != 0)
                cycles[mark[i]].add(i);
        }

        // print all the vertex with same cycle
        for (int i = 1; i <= cyclenumber; i++)
        {
            // Print the i-th cycle
            System.out.printf("Cycle Number %d: ", i);
            for (int x : cycles[i])
                System.out.printf("%d ", x);
            System.out.print(" of cost " + cycleCost(cycles[i]));
            System.out.println();
        }
    }
    // Driver Code
    public static void solve()
    {

        for (int i = 0; i < N; i++)
        {
            graph[i] = new Vector<>();
            cycles[i] = new Vector<>();
        }

        for (Edge edge : Graf.getEdges()){
            addEdge(edge.getSrc().getId(),edge.getDest().getId());
            //System.out.println(edge.getSrc().getId() + " " + edge.getDest().getId());
        }

        // add edges
//        addEdge(1, 2);
//        addEdge(2, 3);
//        addEdge(3, 4);
//        addEdge(4, 1);
//        addEdge(4, 7);
//        addEdge(5, 6);
//        addEdge(3, 5);
//        addEdge(7, 8);
//        addEdge(6, 10);
//        addEdge(5, 9);
//        addEdge(10, 11);
//        addEdge(11, 12);
//        addEdge(11, 13);
//        addEdge(12, 13);

        // arrays required to color the
        // graph, store the parent of node
        int[] color = new int[N];
        int[] par = new int[N];

        // mark with unique numbers
        int[] mark = new int[N];

        // store the numbers of cycle
        cyclenumber = 0;
        int edges = 44;

        // call DFS to mark the cycles
        dfs_cycle(1, 0, color, mark, par);

        // function to print the cycles
        printCycles(edges, mark);
    }


    public static int cycleCost(Vector<Integer> nodes){
        int totalCost = 0;
        for (int i = 0; i<nodes.size(); i++){
            for (int j = 0; j<nodes.size(); j++){
//                System.out.println(
//                        Graph.getNodeById(nodes.elementAt(i)) + " " +
//                        Graph.getNodeById(nodes.elementAt(j)) + " " +
//                        Graph.getWeightBetweenNodes(
//                                Graph.getNodeById(nodes.elementAt(i)),
//                                Graph.getNodeById(nodes.elementAt(j))
//                        )
//                );
                totalCost+=Graf.getWeightBetweenNodes(
                                Graf.getNodeById(nodes.elementAt(i)),
                                Graf.getNodeById(nodes.elementAt(j))
                        );
            }
        }
        return totalCost;
    }

    public static ArrayList<Edge> getCycleOfCost(int cost){
        ArrayList<Edge> result = new ArrayList<Edge>();
        for (Vector<Integer> cycle : cycles){
            if (cycleCost(cycle) == cost){
                //System.out.println("yayy" + " " + cycle);
                for (Integer cycleEdgeSrc: cycle)
                    for (Edge edge: Graf.getEdges())
                        if(cycleEdgeSrc.equals(edge.getSrc().getId()))
                            for (Integer cycleEdgeDest: cycle)
                                if(cycleEdgeDest.equals(edge.getDest().getId()))
                                    result.add(edge);
                //System.out.println(result);
                return result;
            }
        }
        return result;
    }


}

