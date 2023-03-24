package com.company;

import java.util.ArrayList;
import java.util.List;

/**
 * Class for solving the problem
 */
public class Problem {
    private List <Event> events = new ArrayList<Event>();
    private List <Room> rooms = new ArrayList<Room>();

    /**
     * default constructor
     */
    public Problem(){
        this.events = new ArrayList<Event>();
        this.rooms = new ArrayList<Room>();
    }

    /**
     * Problem Constructor awaiting the events list and the rooms list
     * @param events
     * @param rooms
     */
    public Problem(List<Event> events, List<Room> rooms) {
        this.events = events;
        this.rooms = rooms;
    }

    /**
     * returns the event list
     * @return
     */
    public List<Event> getEvents() {
        return events;
    }

    /**
     * sets the events list
     * @param events
     */
    public void setEvents(List<Event> events) {
        this.events = events;
    }

    /**
     * returns the rooms list
     * @return
     */
    public List<Room> getRooms() {
        return rooms;
    }

    /**
     * sets the room list
     * @param rooms
     */
    public void setRooms(List<Room> rooms) {
        this.rooms = rooms;
    }

    /**
     * adds a new room to the rooms list
     * @param newRoom
     */
    public void addRoom(Room newRoom){
        for (Room room: this.rooms){
            if(room.equals(newRoom)){
                System.err.println(newRoom.getName() + " was not added because it already existed");

                return;
            }
        }
        rooms.add(newRoom);
    }

    /**
     * Adds a new event to the event list
     * @param newEvent
     */
    public void addEvent(Event newEvent){
        for (Event event: this.events){
            if(event.equals(newEvent)){
                System.err.println(newEvent.getName() + " was not added because it already existed");
                return;
            }
        }
        events.add(newEvent);
    }

}
