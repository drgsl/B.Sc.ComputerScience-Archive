package Compulsory;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.stream.Collectors;

/**
 *
 */
public class City {
    private HashMap<Intersection, List<Street>>intersections;

    public City() {
        intersections = new HashMap<>();
    }

    /**
     * metoda ce adauga intr-o lista toate strazile ce se intalnesc intr-o intersectie
     * @param street
     */
    public void addIntersection(Street street)
    {
        if(!intersections.containsKey(street.getFirstIntersection())) {
            intersections.put(street.getFirstIntersection(), new ArrayList<Street>());
        }
        intersections.get(street.getFirstIntersection()).add(street);
        if(!intersections.containsKey(street.getSecondIntersection())) {
            intersections.put(street.getSecondIntersection(), new ArrayList<Street>());
        }
        intersections.get(street.getSecondIntersection()).add(street);
    }

    /**
     * metoda ce afiseaza toate strazile care trec printr-o intersectie
     */
    public void print()
    {
        for(Intersection i: intersections.keySet())
        {
            System.out.print(i.getName()+" leaga strazile: ");
            for(Street s: intersections.get(i))
                System.out.print(s.getName()+", ");
            System.out.println();
        }
    }

    /**
     * metoda ce afiseaza strazile cu lungimea mai mare de 1km ce se intalnesc cu cel putin alte 2 strazi intr-o intersectie
     */
    public void query()
    {
        HashSet<Street> set=new HashSet();
        for(Intersection i: intersections.keySet())
        {
            if(intersections.get(i).size()>=3){
                List<Street> intersected =
                        intersections.get(i).stream()
                                .filter(s -> s.getLengthInKm() > 1)
                                .toList();
                set.addAll(intersected);
            }
        }
        for(Street s: set)
            System.out.println(s.getName());
    }

    public List<Street> getStreets(Intersection i)
    {
        return intersections.get(i);
    }


}
