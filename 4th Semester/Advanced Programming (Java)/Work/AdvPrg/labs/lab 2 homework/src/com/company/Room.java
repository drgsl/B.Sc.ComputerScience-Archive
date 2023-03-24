package com.company;

import java.util.Objects;

/**
 * Class for the rooms
 */
public abstract class Room {
    private String name;
    private int capacity;

    boolean[] schedule = new boolean[24];

    /**
     * constructor
     * @param name
     * @param capacity
     */
    public Room(String name, int capacity) {
        this.name = name;
        this.capacity = capacity;
    }

    /**
     * returns the name of the room
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * sets the name of the room
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * return the capacity of the room
     * @return
     */
    public int getCapacity() {
        return capacity;
    }

    /**
     * sets the room capacity
     * @param capacity
     */
    public void setCapacity(int capacity) {
        this.capacity = capacity;
    }

    /**
     * returns the schedule at a given hour
     * @param hour
     * @return
     */
    public boolean getScheduleAt(int hour) {
        return schedule[hour];
    }

    /**
     * changes the schedule for a given time period
     * @param startTime
     * @param endTime
     * @param reserved
     */
    public void setSchedule(int startTime, int endTime, boolean reserved ) {
        for (int i = startTime; i < endTime; i++){
            schedule[i] = reserved;
        }
    }

    /**
     * checks if the room is occupied at a given hour
     * @param hour
     * @return
     */
    public boolean isOccupiedAt(int hour){
        return this.schedule[hour];
    }

    /**
     * changes the schedule for a given hour
     * @param hour
     * @param isReserved
     */
    public void changeScheduleFor(int hour, boolean isReserved){
        this.schedule[hour] = isReserved;
    }

    /**
     * return the name of the room followed by the capacity
     * format: name(cap=100)
     * @return
     */
    @Override
    public String toString() {
        return name + "(" +
                "cap=" + capacity +
                ")";
    }

    /**
     * compares if the name of the current room is the same with the name of the given room
     * @param o
     * @return
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Room room = (Room) o;
        return Objects.equals(this.getName(), room.getName());
    }

    /**
     * returns the hashCode
     * @return
     */
    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}
