import java.util.*;
import java.util.stream.IntStream;
import java.util.stream.Stream;

import SAT.*;
import com.github.javafaker.Faker;

public class Main {
    /**
     * The variables are declared as static because we want to use them in the
     * compulsory() and optional() functions (which are static).
     */
    static Student s0;
    static Student s1;
    static Student s2;
    static Student s3;

    static School h0;
    static School h1;
    static School h2;


    public static void main(String[] args) {

        compulsory();
        optional();
    }

    public static void compulsory() {
        System.out.println("COMPULSORY\n\n");
        s0 = new Student("S0");
        s1 = new Student("S1");
        s2 = new Student("S2");
        s3 = new Student("S3");

        h0 = new School("H0", 1);
        h1 = new School("H1", 2);
        h2 = new School("H2", 2);

        s0.addSchoolPreference(h0);
        s0.addSchoolPreference(h2);
        s0.addSchoolPreference(h1);

        s1.addSchoolPreference(h0);
        s1.addSchoolPreference(h1);
        s1.addSchoolPreference(h2);

        s2.addSchoolPreference(h0);
        s2.addSchoolPreference(h1);

        s3.addSchoolPreference(h0);
        s3.addSchoolPreference(h2);

        h0.addStudentPreference(s3);
        h0.addStudentPreference(s0);
        h0.addStudentPreference(s1);
        h0.addStudentPreference(s2);

        h1.addStudentPreference(s0);
        h1.addStudentPreference(s2);
        h1.addStudentPreference(s1);

        h2.addStudentPreference(s0);
        h2.addStudentPreference(s1);
        h2.addStudentPreference(s3);


        Stream<Student> studentStream = Stream.of(s0, s1, s2, s3);
        Stream<School> schoolStream = Stream.of(h0, h1, h2);

        List<Student> studentList = new LinkedList<>();
        studentList.add(s2);
        studentList.add(s3);
        studentList.add(s0);
        studentList.add(s1);

        studentList.sort(new Comparator<Student>() {
            @Override
            public int compare(Student s1, Student s2) {
                return s1.getName().compareTo(s2.getName());
            }
        });

        Set<School> schoolSet = new TreeSet<>();
        schoolSet.add(h0);
        schoolSet.add(h1);
        schoolSet.add(h2);
        Map<Student, List<School>> studentMap = new HashMap<>();

        studentMap.put(s0, s0.getPreferences());
        studentMap.put(s1, s1.getPreferences());
        studentMap.put(s2, s2.getPreferences());
        studentMap.put(s3, s3.getPreferences());

        Map<School, List<Student>> schoolMap = new TreeMap<>();

        schoolMap.put(h0, h0.getPreferences());
        schoolMap.put(h1, h1.getPreferences());
        schoolMap.put(h2, h2.getPreferences());

        for (Student s : studentList) {
            System.out.print("Preferences for " + s.getName() + " : ");
            List<School> schoolListForStudent = studentMap.get(s);
            for (School i : schoolListForStudent) {
                System.out.print(i + " ");
            }
            System.out.println();
        }

        System.out.println("--------------------------------");

        for (School s : schoolSet) {
            System.out.print("Preference for " + s.getName() + " : ");
            List<Student> studentListForSchool = schoolMap.get(s);
            for (Student i : studentListForSchool) {
                System.out.print(i + " ");
            }
            System.out.println();
        }
    }

    public static void optional() {
        System.out.println("\n\nOPTIONAL\n\n");

        Stream<Student> streamOfStudents = Stream.of(s0, s1, s2, s3);
        Stream<School> streamOfSchools = Stream.of(h0, h1, h2);

        List<School> targetSchools = Arrays.asList(h0, h2);
        System.out.println("School target list: " + targetSchools);
        System.out.println("students who want to get into the above mentioned schools: ");
        streamOfStudents.filter(student -> student.getPreferences().containsAll(targetSchools)).forEach(System.out::println);

        System.out.println("Schools that accept S0 as a student:");
        streamOfSchools.filter(school -> school.getPreferences().contains(s0)).forEach(System.out::println);

        Problem P = new Problem();
        P.addStudent(s0);
        P.addStudent(s1);
        P.addStudent(s2);
        P.addStudent(s3);

        P.addSchool(h0);
        P.addSchool(h1);
        P.addSchool(h2);

        Algorithm a = new Algorithm(P);

        a.solve().printMatching();


        System.out.println("\n----------------------------\nUsing random generated strings\n");

        // Using third-party library
        Faker faker = new Faker();

        Problem P2 = new Problem();

        Student[] students = new Student[100];
        for (int i = 0; i < students.length; i++) {
            students[i] = new Student(faker.name().name());
            students[i].setScore(faker.number().numberBetween(1, 100));
            P2.addStudent(students[i]);
        }

        School[] schools = new School[20];
        for (int i = 0; i < schools.length; i++) {
            schools[i] = new School(faker.university().name(), 5);
            P2.addSchool(schools[i]);
            for (int j = 0; j < 5; j++) {
                students[i * 5 + j].addSchoolPreference(schools[i]);
            }
        }

        Algorithm greedy2 = new Algorithm(P2);
        greedy2.solve().printMatching();

    }
}
