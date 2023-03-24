package com.company;

public class Room {
    String name;
    int capacity;
    RoomType type;


    public Room(String name, int capacity, RoomType type) {
        this.name = name;
        this.capacity = capacity;
        this.type = type;
    }

    @Override
    public String toString() {
        return name + "(" +
                "cap=" + capacity +
                ", " + type +
                "), ";
    }
}
