package TP;

import java.util.*;


/**
 * An abstract class describing a Source object for the Transportation problem.
 * @author Peterca Adrian
 * @version 1.0
 */
public abstract class Source {
    protected String name;
    protected int initialSupply;
    protected int remainingSupply;

    @Override
    public String toString() {
        return getName();
    }

    /** Compares both the name of the source and its initial supply.
     * @param obj refers to an object that may be of type Source.
     * @return whether or not the current object is equal to the one stored in the parameter.
     */
    @Override
    public boolean equals(Object obj) {
        if (! (obj instanceof Source)) {
            return false;
        }
        Source s = (Source) obj;
        return this.getName().equals(s.getName()) && this.getInitialSupply().equals(s.getInitialSupply());
    }

    public void setName(String newName) {
        this.name = newName;
    }

    public void setInitialSupply(Integer newSupply) {
        this.initialSupply = newSupply;
        this.remainingSupply = newSupply;
    }

    public String getName() {
        return this.name;
    }

    public Integer getInitialSupply() {
        return initialSupply;
    }

    public Integer getRemainingSupply() {
        return remainingSupply;
    }

    /**
     * Method used for extracting a specific amount of supplies from a given source.
     * @param amount indicates how many units of supplies it should extract.
     * @return whether or not the extraction was possible. The only case when it returns false is when the requested amount is bigger than the current amount.
     */
    public boolean extractSupply(int amount) {
        if (remainingSupply >= amount) {
            remainingSupply -= amount;
            return true;
        }
        return false;
    }
}
