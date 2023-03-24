package com.company;

public class Event {

    String name;
    int size;
    int startTime;
    int endTime;


    public Event(String name, int size, int startTime, int endTime) {
        this.name = name;
        this.size = size;
        this.startTime = startTime;
        this.endTime = endTime;
    }


    public String getName() {
        return name;
    }


    public void setName(String name) {
        this.name = name;
    }


    public int getSize() {
        return size;
    }


    public void setSize(int size) {
        this.size = size;
    }


    public int getStartTime() {
        return startTime;
    }


    public void setStartTime(int startTime) {
        this.startTime = startTime;
    }


    public int getEndTime() {
        return endTime;
    }


    public void setEndTime(int endTime) {
        this.endTime = endTime;
    }


    @Override
    public String toString() {
        return name +
                "(size=" + size +
                ", start=" + startTime +
                ", end=" + endTime +
                "), ";
    }
}
