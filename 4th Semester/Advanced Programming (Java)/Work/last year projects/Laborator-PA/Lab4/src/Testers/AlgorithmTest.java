package Testers;

import SAT.*;
import com.github.javafaker.Faker;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AlgorithmTest {

    Student s0;
    Student s1;
    Student s2;
    Student s3;

    School h0;
    School h1;
    School h2;

    Faker faker;

    Problem P;

    @BeforeEach
    void setUp() {
        faker = new Faker();

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

        P = new Problem();
        P.addStudent(s0);
        P.addStudent(s1);
        P.addStudent(s2);
        P.addStudent(s3);

        P.addSchool(h0);
        P.addSchool(h1);
        P.addSchool(h2);
    }

    @Test
    void solve() {
        Algorithm greedy = new Algorithm(P);
        Solution s = greedy.solve();

        Assertions.assertEquals(h0, s.getSchoolForStudent(s3));
        Assertions.assertEquals(h1, s.getSchoolForStudent(s1));
        Assertions.assertEquals(h1, s.getSchoolForStudent(s2));
        Assertions.assertEquals(h2, s.getSchoolForStudent(s0));
    }
}