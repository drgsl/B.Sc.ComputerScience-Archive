package Compulsory;

import java.util.Objects;

/**
 * clasa ce retine informatii despre o strada
 */
public class Street implements Comparable {

    private String name;
    private int lengthInKm;
    private Intersection firstIntersection;
    private Intersection secondIntersection;

    public Street(String name, int lengthInKm, Intersection firstIntersection, Intersection secondIntersection) {
        this.name = name;
        this.lengthInKm = lengthInKm;
        this.firstIntersection = firstIntersection;
        this.secondIntersection = secondIntersection;
    }

    public Intersection getFirstIntersection() {
        return firstIntersection;
    }

    public void setFirstIntersection(Intersection firstIntersection) {
        this.firstIntersection = firstIntersection;
    }

    public Intersection getSecondIntersection() {
        return secondIntersection;
    }

    public void setSecondIntersection(Intersection secondIntersection) {
        this.secondIntersection = secondIntersection;
    }

    public String getName() {
        return name;
    }

    public int getLengthInKm() {
        return lengthInKm;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setLengthInKm(int lengthInKm) {
        this.lengthInKm = lengthInKm;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Street)) return false;
        Street street = (Street) o;
        return getLengthInKm() == street.getLengthInKm() && getName().equals(street.getName()) && getFirstIntersection().equals(street.getFirstIntersection()) && getSecondIntersection().equals(street.getSecondIntersection());
    }

    @Override
    public int hashCode() {
        return Objects.hash(getName(), getLengthInKm(), getFirstIntersection(), getSecondIntersection());
    }

    @Override
    public int compareTo(Object o) {
        if (o == null) throw new NullPointerException();
        if (!(o instanceof Street))
            throw new ClassCastException("Incomparable obejects!");
        return (this.lengthInKm - ((Street) o).lengthInKm);
    }

}
