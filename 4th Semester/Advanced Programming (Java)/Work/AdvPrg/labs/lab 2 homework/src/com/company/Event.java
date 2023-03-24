package com.company;

import java.util.Objects;

/**
 * Class for the events
 */
public class Event {

    private String name;
    private int size;
    private int startTime;
    private int endTime;
    private Room assignedRoom;


    /**
     * constructor
     * @param name
     * @param size
     * @param startTime
     * @param endTime
     */
    public Event(String name, int size, int startTime, int endTime) {
        this.name = name;
        this.size = size;
        this.startTime = startTime;
        this.endTime = endTime;
    }

    /**
     * returns the name of the event
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * sets the name of the event
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * returns the size of the event
     * @return
     */
    public int getSize() {
        return size;
    }

    /**
     * sets the size of the event
     * @param size
     */
    public void setSize(int size) {
        this.size = size;
    }

    /**
     * gets the starting hour of the event
     * @return
     */
    public int getStartTime() {
        return startTime;
    }

    /**
     * sets the starting hour of the event
     * @param startTime
     */
    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }

    /**
     * returns the end time of the event
     * @return
     */
    public int getEndTime() {
        return endTime;
    }

    /**
     * sets the end time of the event
     * @param endTime
     */
    public void setEndTime(int endTime) {
        this.endTime = endTime;
    }

    /**
     * return the name of the event followed by its size
     * format: name(size=100, start=8, end=10)
     * @return
     */
    @Override
    public String toString() {
        return name +
                "(size=" + size +
                ", start=" + startTime +
                ", end=" + endTime +
                ")";
    }

    /**
     * compares if the name of the current event is the same with the name of the given event
     * @param o
     * @return
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Event event = (Event) o;
        return Objects.equals(this.getName(), event.getName());
    }

    /**
     * returns the hashCode
     * @return
     */
    @Override
    public int hashCode() {
        return Objects.hash(name);
    }

    /**
     * sets the assigned room
     * @param assignedRoom
     */
    public void setAssignedRoom(Room assignedRoom){
        this.assignedRoom = assignedRoom;
    }

    /**
     * returns the assignedRoom
     * @return
     */
    public Room getAssignedRoom() {
        return assignedRoom;
    }
}
