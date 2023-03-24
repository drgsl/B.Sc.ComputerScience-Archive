package Compulsory;

import java.util.*;
import java.util.stream.IntStream;
import java.util.stream.Stream;
import com.github.javafaker.Faker;
import org.jgrapht.Graph;

/**
 * @author Teodora Breahna
 */

public class Main {

    public static void main(String[] args) {


        /*creation of the intersections*/
        Faker faker = new Faker();
        HashSet<Intersection> intersectionsList = new HashSet<>();
        var nodeArray = IntStream.rangeClosed(0, 9)
                .mapToObj(i -> new Intersection(faker.address().streetAddressNumber()))
                .toArray(Intersection[]::new);
        intersectionsList.addAll(Arrays.asList(nodeArray));


        //we try to add an element with the same name
        intersectionsList.add(new Intersection("intersection_7"));
        intersectionsList.add(new Intersection("intersection_9"));
        intersectionsList.add(new Intersection("intersection_10"));

        HashMap<Intersection, Integer> intersectionsVerifying = new HashMap<>();

        for (Intersection i : intersectionsList) {
            intersectionsVerifying.put(i, 0);
        }

        for (Intersection i : intersectionsList) {
            int count = intersectionsVerifying.get(i);
            intersectionsVerifying.put(i, count + 1);
        }

        //Showing that there are no duplicates
        for (Intersection i : intersectionsVerifying.keySet()) {
            if (intersectionsVerifying.get(i) > 1) {
                System.out.println("Duplicates exist!");
            }
            System.out.println(i.getName() + " " + intersectionsVerifying.get(i));
        }

        List<Intersection> listInter = new ArrayList<>();
        for (Intersection i : intersectionsList) {
            listInter.add(i);
        }


        /*creation of the streets*/
        Street s1 = new Street(faker.address().streetName(), 2, listInter.get(1), listInter.get(2));
        Street s2 = new Street(faker.address().streetName(), 2, listInter.get(2), listInter.get(4));
        Street s3 = new Street(faker.address().streetName(), 2, listInter.get(2), listInter.get(3));
        Street s4 = new Street(faker.address().streetName(), 2, listInter.get(3), listInter.get(5));
        Street s5 = new Street(faker.address().streetName(), 1, listInter.get(4), listInter.get(3));
        Street s6 = new Street(faker.address().streetName(), 3, listInter.get(1), listInter.get(7));
        Street s7 = new Street(faker.address().streetName(), 2, listInter.get(1), listInter.get(3));
        Street s8 = new Street(faker.address().streetName(), 1, listInter.get(8), listInter.get(9));
        Street s9 = new Street(faker.address().streetName(), 3, listInter.get(4), listInter.get(5));
        Street s10 = new Street(faker.address().streetName(), 2, listInter.get(7), listInter.get(9));
        Street s11 = new Street(faker.address().streetName(), 2, listInter.get(3), listInter.get(6));
        Street s12 = new Street(faker.address().streetName(), 1, listInter.get(6), listInter.get(9));
        Street s13 = new Street(faker.address().streetName(), 3, listInter.get(5), listInter.get(9));
        Street s14 = new Street(faker.address().streetName(), 1, listInter.get(6), listInter.get(8));
        Street s15 = new Street(faker.address().streetName(), 1, listInter.get(7), listInter.get(8));
        Street s16 = new Street(faker.address().streetName(), 1, listInter.get(5), listInter.get(7));

        List<Street> streetList = new ArrayList<>();
        streetList.add(s1);
        streetList.add(s2);
        streetList.add(s3);
        streetList.add(s4);
        streetList.add(s5);
        streetList.add(s6);
        streetList.add(s7);
        streetList.add(s8);
        streetList.add(s9);
        streetList.add(s10);
        streetList.add(s11);
        streetList.add(s12);
        streetList.add(s13);
        streetList.add(s14);
        streetList.add(s15);
        streetList.add(s16);

        /**
         * sortarea strazilor crescator dupa lungime
         */
        Collections.sort(streetList, (Street first, Street second) ->
        {
            if (first.getLengthInKm() == second.getLengthInKm())
                return 0;
            if (first.getLengthInKm() < second.getLengthInKm())
                return -1;
            return 1;
        });


        for (Street s : streetList) {
            System.out.println(s.getName() + " " + s.getLengthInKm());
        }

        System.out.println("-----Optional-----");
        City c = new City();
        for (Street s : streetList) {
            c.addIntersection(s);
        }
        System.out.println("Strazile mai lungi de 1km care se intalnesc cu cel putin alte 2 strazi intr-o intersectie sunt:");
        c.query();


        DisjointSet cameras = new DisjointSet();
        cameras.makeSet(listInter);
        cameras.printTree(listInter,streetList);

        System.out.println();
        System.out.println("-----Bonus-----");
        Graf g= new Graf();
        g.printDFS(cameras.kruskal(listInter,streetList));


    }
}
