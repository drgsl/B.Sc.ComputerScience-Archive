package TP;

/**
 * A class representing a destination in the Transportation Problem.
 * @author Adrian Peterca
 * @version 1.0
 */
public class Destination {
    private String name;
    private Integer demand;

    public Destination(String name, Integer demand) {
        setName(name);
        setDemand(demand);
    }

    @Override
    public String toString() {
        return getName();
    }

    /**
     * Compares the current Destination object with the one given as parameter (if it is of the same type).
     * @param obj the given parameter
     * @return true if the objects are equal (both the demand and the name are the same), false otherwise
     */
    @Override
    public boolean equals(Object obj) {
        if (!(obj instanceof Destination)) {
            return false;
        }

        Destination d = (Destination) obj;
        return this.getName().equals(d.getName()) && this.getDemand().equals(d.getDemand());
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDemand(Integer demand) {
        this.demand = demand;
    }

    public String getName() {
        return this.name;
    }

    public Integer getDemand() {
        return this.demand;
    }
}
