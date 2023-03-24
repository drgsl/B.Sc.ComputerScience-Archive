package SAT;

import java.util.*;

public class Solution {
    Map<Student, School> matching;

    public Solution() {
        matching = new HashMap<>();
    }

    public void addPair(Student student, School school) {
        matching.put(student, school);
    }

    public boolean exists(Student student) {
        return matching.get(student) == null;
    }

    public void printMatching() {
        for (Student student : matching.keySet()) {
            System.out.println("Student " + student + " is assigned to school " + matching.get(student) + ".");
        }
    }

    public School getSchoolForStudent(Student student) {
        return matching.get(student);
    }

}
