package com.company;

/**
 * Class for the ComputerLabs
 */
public class ComputerLab extends Room {
    private String operatingSystem;

    /**
     * constructor
     * @param name
     * @param capacity
     * @param operatingSystem
     */
    public ComputerLab(String name, int capacity, String operatingSystem) {
        super(name, capacity);
        this.operatingSystem = operatingSystem;
    }

    /**
     * returns the operatingSystem of the lab, in string format
     * @return
     */
    public String getOperatingSystem() {
        return operatingSystem;
    }

    /**
     * sets the operatingSystem of the lab, in string format
     * @param operatingSystem
     */
    public void setOperatingSystem(String operatingSystem) {
        this.operatingSystem = operatingSystem;
    }
}
