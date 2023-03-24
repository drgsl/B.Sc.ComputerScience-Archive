package TTPP;

import java.util.*;

/**
 * Abstract class describing a general location.
 */
public abstract class Location {
    /**
     * HashMap which contains the travel times (costs) from this location to others.
     */
    HashMap<Location, Integer> travelCost;

    /**
     * The name of the location
     */
    String name;

    /**
     * The description of the current location
     */
    String description;

    /**
     * The default constructor of the Location class.
     *
     * @param name The name of the location.
     */
    public Location(String name) {
        if (name == null) {
            System.out.println("Error! The name cannot be null!");
            return;
        }
        this.name = name;
        travelCost = new HashMap<>();
    }

    /**
     * Public function that adds a cost (time) from the current location to the one mentioned in the travelCost data.
     * If one of the parameters is null, the function prints a warning and adds nothing.
     * @param location the destination
     * @param cost the cost of going from the current location to the destination
     */
    public void addCost(Location location, Integer cost) {
        if (location == null) {
            System.out.println("Error! Location invalid! (null)");
            return;
        }
        if (cost == null) {
            System.out.println("Error! Cost invalid! (null)");
            return;
        }
        this.travelCost.put(location, cost);
    }

    public void setDescription(String description) {
        if (description == null) {
            System.out.println("Error! No description added! (null)");
            return;
        }
        this.description = description;
    }

    /**
     * Public getter for the travelCost data.
     * @return a reference to the travelCost data.
     */
    public HashMap<Location, Integer> getTravelCost() {
        return this.travelCost;
    }

    public Integer getTravelCostTo(Location location) {
        Integer temp = this.travelCost.get(location);
        if (temp == null)
            return -1;
        return  temp;
    }

    public String getName() {
        return this.name;
    }
}
