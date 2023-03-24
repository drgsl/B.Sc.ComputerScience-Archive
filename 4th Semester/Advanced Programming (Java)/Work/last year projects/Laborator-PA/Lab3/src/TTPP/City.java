package TTPP;

import java.util.*;

/**
 * Class describing a city which contains a name, a list of locations and methods to populate this city with different locations.
 */
public class City {
    String name;
    LinkedList<Location> locations;

    public City(String name) {
        if (name == null) {
            System.out.println("Error! No name provided for the city!");
            return;
        }
        this.name = name;
        locations = new LinkedList<>();
    }

    public String getName() {
        return this.name;
    }

    public Location getLocationAtIndex(Integer index) {
        if (this.locations.size() < index) {
            return null;
        }
        return this.locations.get(index);
    }

    public int getIndexOfLocation(Location location) {
        return this.locations.indexOf(location);
    }

    public void addLocation(Location location) {
        this.locations.add(location);
    }

    public void displayVisitableAndNotPayable() {
        LinkedList<Visitable> temp = new LinkedList<Visitable>();
        for (Location l : locations) {
            if (l instanceof Visitable && !(l instanceof Payable)) {
                temp.add((Visitable) l);
            }
        }

        System.out.println("--------------Before sorting: ");
        for (Visitable l : temp) {
            System.out.println(((Location) l).getName() + " (open hours: " + l.getOpeningHours() + ")");
        }

        System.out.println("\n\n--------------After sorting: ");
        temp.sort(new Comparator<Visitable>() {
            @Override
            public int compare(Visitable location1, Visitable location2) {
                if (location1.getOpeningHours().isBefore(location2.getOpeningHours())) {
                    return -1;
                }
                if (location1.getOpeningHours().isAfter(location2.getOpeningHours())) {
                    return 1;
                }
                return 0;
            }
        });

        for (Visitable l : temp) {
            System.out.println(((Location) l).getName() + " (open hours: " + l.getOpeningHours() + ")");
        }

    }
}
