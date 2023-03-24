package Compulsory;

import java.util.*;

public class Graf {
    private Map<Intersection, List<Intersection>> adiacenta;
    private Map<Intersection, Boolean> vizitat;
    private List<Intersection> dfs;
    private Intersection last = new Intersection();

    public void Graf() {

    }

    public void addInt(Intersection a, Intersection b)
    {
        if(!adiacenta.containsKey(a))
            adiacenta.put(a, new ArrayList<Intersection>());
        adiacenta.get(a).add(b);
    }

    public List<Intersection> DFS(List<Street> mst){
        adiacenta= new HashMap<>();
        vizitat= new HashMap<>();
        dfs= new ArrayList<>();

        for(Street s: mst)
        {
            addInt(s.getFirstIntersection(),s.getSecondIntersection());
        }
        for(Intersection i: adiacenta.keySet())
        {
            vizitat.put(i,false);
            last=i;
        }

        Stack<Intersection> stack = new Stack<>();
        stack.push(last);

        while(!stack.empty())
        {
            last=stack.peek(); //ia primul elem din stiva
            stack.pop();

            if(last!=null) {
                if(vizitat.get(last).equals(false))
                {
                    dfs.add(last);
                    vizitat.put(last,true);
                }

                for(Intersection i: adiacenta.get(last))
                {
                    if(!vizitat.get(i))
                        stack.push(i);
                }
            }

        }
        return dfs;
    }

    public void printDFS(List<Street>mst)
    {
        List<Intersection> dfs2 = DFS(mst);
        for(Intersection i: dfs)
            System.out.println(i.getName());
    }


}
