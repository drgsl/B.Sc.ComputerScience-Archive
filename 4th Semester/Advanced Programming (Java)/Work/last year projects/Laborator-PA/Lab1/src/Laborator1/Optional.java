package Laborator1;

import java.util.*;

// Author: Peterca Adrian
public class Optional {
    static boolean largeInput = false;
    static long startTime, endTime;

    public static void optionalMain(String[] args) {
        if (args.length == 0) {
            System.out.println("No argument found");
            return;
        }

        int n = Integer.parseInt(args[0]);
        if (n <= 0) {
            System.out.printf("Invalid argument n = %d!", n);
            return;
        }
        if (n > 30000)
            largeInput = true;

        if (largeInput)
            startTime = System.nanoTime();

        // Construct the graph using a matrix
        int[][] graph = new int[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (i != j && graph[i][j] == 0) {
                    graph[j][i] = graph[i][j] = ((int) (Math.random() * 1000)) % 2;
                }
                else
                    graph[i][j] = 0;
            }
        }

        // Display the matrix
        if (!largeInput)
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    System.out.print(graph[i][j] + " ");
                }
                System.out.println();
            }
        DFS(graph);
        PartialTree(graph);

        if (largeInput) {
            endTime = System.nanoTime();
            System.out.printf("Total time in nanoseconds: %d\n", endTime - startTime);
        }
    }

    public static void DFS(int[][] graph) {
        Stack<Integer> s = new Stack<Integer>();

        int len = graph[0].length;
        boolean[] visitedNodes = new boolean[len];
        for (int i = 0; i < len; ++i)
            visitedNodes[i] = false;

        int currentConnectedComponent = 1;

        // Helps create a graph with 2 connected components
        /*
        for (int i = 0; i < len; ++i) {
            graph[0][i] = graph[i][0] = 0;
        }*/

        for (int i = 0; i < len; ++i)
        {
            if (!visitedNodes[i])
            {
                if (!largeInput)
                    System.out.printf("Componenta conexa %d : ", currentConnectedComponent++);
                s.push(i);
                visitedNodes[i] = true;
                System.out.printf("%d ", i);

                while (!s.empty())
                {
                    int node = s.pop();
                    for (int j = 0; j < len; ++j)
                        if (graph[node][j] == 1 && !visitedNodes[j]) {
                            s.push(j);
                            visitedNodes[j] = true;
                            if (!largeInput)
                                System.out.printf("%d ", j);
                        }
                }
                System.out.println();
            }
        }



    }

    public static void PartialTree(int[][] graph) {
        Queue<Integer> queue = new LinkedList<Integer>();

        int len = graph.length;
        boolean[] visitedNodes = new boolean[len];

        // Initialization
        int[][] tree = new int[len][len];
        for (int i = 0; i < len; ++i)
            for (int j = 0; j < len; j++)
                tree[i][j] = 0;

        queue.add(0);
        visitedNodes[0] = true;
        while (!queue.isEmpty()) {
            int node = queue.remove();

            for (int i = 0; i < len; i++)
                if (graph[node][i] == 1 && !visitedNodes[i]) {
                    queue.add(i);
                    visitedNodes[i] = true;
                    tree[i][node] = tree[node][i] = 1;
                }
        }

        if (!largeInput) {
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++)
                    System.out.printf("%d ", tree[i][j]);
                System.out.println();
            }
        }
    }
}
