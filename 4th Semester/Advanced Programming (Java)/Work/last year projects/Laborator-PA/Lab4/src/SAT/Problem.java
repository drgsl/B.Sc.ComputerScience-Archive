package SAT;
import java.util.*;

/**
 * A class describing an instance of the SAT problem.
 * It consists of a list of students and a list of schools.
 */
public class Problem {
    List<Student> studentList;
    List<School> schoolList;

    public Problem() {
        this.studentList = new LinkedList<>();
        this.schoolList = new LinkedList<>();
    }

    public void addStudent(Student s) {
        this.studentList.add(s);
    }

    public void addSchool(School s) {
        this.schoolList.add(s);
    }

    public List<School> getSchoolList() {
        return this.schoolList;
    }

    public List<Student> getStudentList() {
        return studentList;
    }
}
