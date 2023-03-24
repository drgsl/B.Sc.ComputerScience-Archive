package SAT;

import java.util.*;

public class Algorithm {
    Problem problem;
    Solution solution;

    public Algorithm(Problem p) {
        this.problem = p;
        this.solution = new Solution();
    }

    public Solution solve() {

        // Sort the list (descending order) according to the scores and, if the scores are the same, order them alphabetically
        problem.studentList.sort(new Comparator<Student>() {
            @Override
            public int compare(Student o1, Student o2) {
                // Compare their scores
                if (o1.getScore() > o2.getScore()) return -1;
                else if (o1.getScore() < o2.getScore()) return 1;

                // Compare their names
                return -o1.getName().compareTo(o2.getName());
            }
        });

        // For each student (starting from the one with the highest score), search for the first available place.
        for (Student student : problem.studentList) {
            for (School school : student.getPreferences()) {
                if (school.isSpaceAvailable()) {
                    this.solution.addPair(student, school);
                    school.occupyPlace();
                    break;
                }
            }
        }

        return this.solution;
    }

}
