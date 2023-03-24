package com.company;

import java.util.ArrayList;
import java.util.List;


/**
 * Class for solving the problem
 */
public class Solution {
    private Problem problem;
    private List<Room> selectedRooms = new ArrayList<Room>();
    private List<Event> selectedEvents = new ArrayList<Event>();

    /**
     * creates a solution for a given problem
     * @param problem
     */
    public Solution(Problem problem) {
        this.problem = problem;
        solve(problem);
    }

    /**
     * sets the problem variable to a set problem
     * @param problem
     */
    public void setProblem(Problem problem) {
        this.problem = problem;
        solve(problem);
    }

    /**
     * returns the selected Rooms, in order
     * @return
     */
    public List<Room> getSelectedRooms() {
        return selectedRooms;
    }

    /**
     * returns the selected Events, in order
     * @return
     */
    public List<Event> getSelectedEvents() {
        return selectedEvents;
    }

    /**
     * solves the problem, using Greedy method
     * @param problem
     */
    public void solve(Problem problem){
        List<Room> availableRooms = problem.getRooms();
        List<Event> events = problem.getEvents();

        //TODO: order rooms by capacity

        for (Event event : events) {
            for (Room room: availableRooms){
                //System.out.println("Trying " + event.getName() + " with " + room.getName());
                if(room.getCapacity() >= event.getSize()
                         && !room.getScheduleAt(event.getStartTime())
                         && !room.getScheduleAt(event.getEndTime())
                )
                {
                    event.setAssignedRoom(room);
                    room.setSchedule(event.getStartTime(), event.getEndTime(), true);
                    selectedRooms.add(room);
                    selectedEvents.add(event);
                    //System.out.println(event.getName() + "  " + event.getAssignedRoom());
                    break;
                }


            }
        }
    }


}
