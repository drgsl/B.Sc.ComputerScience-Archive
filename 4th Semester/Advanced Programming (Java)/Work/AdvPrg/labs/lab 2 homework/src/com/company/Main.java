package com.company;

import java.security.KeyStore;



/**
 * @author Bobu Dragos Andrei
 * Main Class
 */
public class Main {

    public static void main(String[] args) {

        Problem problem = new Problem();

        problem.addRoom(new ComputerLab("401", 30, "WINDOWS"));
        problem.addRoom(new ComputerLab("403", 30, "LINUX"));
        problem.addRoom(new ComputerLab("405", 30, "WINDOWS"));
        problem.addRoom(new LectureHall("309", 100, true));
        problem.addRoom(new ComputerLab("401", 30, "WINDOWS"));

        problem.addEvent(new Event("C1", 100, 8, 9));
        problem.addEvent(new Event("C2", 100, 10, 12));
        problem.addEvent(new Event("L1", 30, 8, 10));
        problem.addEvent(new Event("L2", 30, 8, 10));
        problem.addEvent(new Event("L3", 30, 10, 12));
        problem.addEvent(new Event("C1", 100, 8, 9));


        Solution solution = new Solution(problem);

        for (int i = 0; i < solution.getSelectedEvents().size(); i++) {
            System.out.println(solution.getSelectedEvents().get(i) + " - " + solution.getSelectedRooms().get(i));
        }
    }
}




