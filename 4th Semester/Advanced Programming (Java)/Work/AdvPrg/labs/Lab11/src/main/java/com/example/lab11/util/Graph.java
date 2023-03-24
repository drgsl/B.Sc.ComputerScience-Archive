package com.example.lab11.util;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Graph {
    private int n;
    private final List[] adjacency;
    private int time = 0;


    public Graph(int n) {
        this.n = n;
        adjacency = new LinkedList[n];
        for (int i = 0; i < n; ++i)
            adjacency[i] = new LinkedList<Integer>();
    }


    public void addEdge(int v, int w) {
        if (!adjacency[v].contains(w)) {
            adjacency[v].add(w);
        }
        if (!adjacency[w].contains(v)) {
            adjacency[w].add(v);
        }
    }


    private void FindCutVerticesRecursive(int u, boolean visited[], int disc[], int low[], int parent[], boolean ap[]) {

        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++time;

        Iterator<Integer> i = adjacency[u].iterator();
        while (i.hasNext()) {
            int v = i.next();
            if (!visited[v]) {
                children++;
                parent[v] = u;
                FindCutVerticesRecursive(v, visited, disc, low, parent, ap);
                low[u] = Math.min(low[u], low[v]);

                if (parent[u] == -1 && children > 1)
                    ap[u] = true;

                if (parent[u] != -1 && low[v] >= disc[u])
                    ap[u] = true;
            } else if (v != parent[u])
                low[u] = Math.min(low[u], disc[v]);
        }
    }

    public List<Integer> findCutVertices() {
        boolean visited[] = new boolean[n];
        int disc[] = new int[n];
        int low[] = new int[n];
        int parent[] = new int[n];
        boolean ap[] = new boolean[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            visited[i] = false;
            ap[i] = false;
        }

        for (int i = 0; i < n; i++)
            if (visited[i] == false)
                FindCutVerticesRecursive(i, visited, disc, low, parent, ap);
        List<Integer> cutVertices = new ArrayList<>();
        for (int i = 0; i < n; i++)
            if (ap[i] == true) {
                cutVertices.add(i);
            }
        return cutVertices;
    }
}
