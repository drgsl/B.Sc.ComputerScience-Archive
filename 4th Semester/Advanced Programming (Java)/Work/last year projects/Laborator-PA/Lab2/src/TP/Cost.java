package TP;

import java.util.*;

/**
 * A class representing the cost from a Source object to a Destination object.
 * Used in the Transportation problem.
 */
public class Cost {
    Source from;
    Destination to;
    Integer cost;

    public Cost(Source from, Destination to, Integer cost) {
        setFrom(from);
        setTo(to);
        setCost(cost);
    }

    public void setFrom(Source from) {
        if (from == null) {
            System.out.println("Received an empty Source!");
            return;
        }
        this.from = from;
    }

    public void setTo(Destination to) {
        if (to == null) {
            System.out.println("Received an empty Destination!");
            return;
        }
        this.to = to;
    }

    public void setCost(Integer cost) {
        if (cost == null) {
            System.out.println("Received an empty Integer for cost!");
            return;
        }
        this.cost = cost;
    }

    public Source getFrom() {
        return this.from;
    }

    public Destination getTo() {
        return this.to;
    }

    public Integer getCost() {
        return this.cost;
    }
}
