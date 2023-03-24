package SAT;

import java.util.*;

public class School implements Comparable<School>{
    /**
     * The name of the school
     */
    String name;
    /**
     * The maximum capacity of the school. Once set, it should not be modified.
     */
    int capacity;
    /**
     * The number of available places to this particular school
     */
    int size;
    /**
     * The preferences for different students
     */
    List<Student> preferences;

    public School (String name, int capacity) {
        if (name == null) {
            System.out.println("Cannot create a school with no name!");
            return;
        }
        if (capacity <= 0 ) {
            System.out.println("Cannot create a school with below 1 capacity!");
            return;
        }
        this.name = name;
        this.capacity = capacity;
        this.size = capacity;
        this.preferences = new LinkedList<>();
    }

    public String getName() {
        return this.name;
    }

    public boolean isSpaceAvailable() {
        return this.size > 0;
    }

    public void occupyPlace() {
        if (this.size == 0) {
            System.out.println("No more places available at " + this.name + "!");
            return;
        }
        this.size--;
    }

    public void addStudentPreference(Student name) {
        this.preferences.add(name);
    }

    public List<Student> getPreferences() {
        return this.preferences;
    }

    /**
     * Function fro comparing schools.
     * @param s1 The school reference to be compared to
     * @return 0, if they are the same school. A positive value if the current school comes after the s1 school, and a negative value otherwise.
     */
    public int compareTo(School s1) {
        return this.name.compareTo(s1.getName());
    }

    @Override
    public String toString() {
        return getName();
    }
}
