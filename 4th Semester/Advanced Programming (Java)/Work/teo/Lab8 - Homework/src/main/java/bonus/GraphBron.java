package bonus;

import org.jgrapht.Graph;
import org.jgrapht.alg.clique.BronKerboschCliqueFinder;

import java.sql.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;

public class GraphBron extends BronKerboschCliqueFinder {
    private Connection con;

    public GraphBron(Graph graph){ super(graph); }

    public void makeClique(){
        super.lazyRun();
        List<HashSet<Integer>> list = new ArrayList<>();
        List<HashSet<Integer>> list2 = new ArrayList<>();
        list = super.allMaximalCliques;
        list2 = list.stream().filter(c -> c.size() >= 3).toList();
        //System.out.println(list2);

        CityMaker city = new CityMaker();
        for(HashSet<Integer> h: list2){
            System.out.print("[ ");
            for(Integer i:h){
                //System.out.println(i);
                System.out.print(city.findById(i) + ", ");
            }
            System.out.println("]");
        }

    }


}


