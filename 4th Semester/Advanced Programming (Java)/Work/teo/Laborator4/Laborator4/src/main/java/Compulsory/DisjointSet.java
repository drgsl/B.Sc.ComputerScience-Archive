package Compulsory;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DisjointSet {
    Map<Intersection, Intersection> parent;
    List<Street> minimumTree;

    DisjointSet()
    {
        parent = new HashMap<>();
    }

    public void makeSet(List<Intersection> inters)
    {
        for(Intersection i: inters)
            parent.put(i,i);
    }

    public Intersection find(Intersection i)
    {
        if(parent.get(i).equals(i)) return i;
        return find(parent.get(i));
    }

    public void union(Intersection a, Intersection b)
    {
        Intersection x = find(a);
        Intersection y = find(b);
        parent.put(x,y);
    }

    public List<Street> kruskal(List<Intersection> inters, List<Street> streets)
    {
        minimumTree = new ArrayList<>();
        int index = 0;
        while(minimumTree.size()!=inters.size()-1 && index<streets.size())
        {
            Street currentStreet = streets.get(index++);
            Intersection x = find(currentStreet.getFirstIntersection());
            Intersection y = find(currentStreet.getSecondIntersection());

            if(!x.equals(y)){
                minimumTree.add(currentStreet);
                union(x,y);
            }
        }
        return minimumTree;
    }

    public void printTree(List<Intersection> inters, List<Street> streets)
    {
        System.out.println("Strazile pe care trebuie amplasate cabluri sunt:");
        List<Street> mst = kruskal(inters, streets);
        for(Street s: mst)
            System.out.print(s.getName()+", ");
    }

}
