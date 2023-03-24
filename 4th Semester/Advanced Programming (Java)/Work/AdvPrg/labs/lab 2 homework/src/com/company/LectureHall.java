package com.company;

/**
 * Class for the LectureHall
 */
public class LectureHall extends Room{
    private boolean hasVideoProjector;

    /**
     * constructor
     * @param name
     * @param capacity
     * @param hasVideoProjector
     */
    public LectureHall(String name, int capacity, boolean hasVideoProjector) {
        super(name, capacity);
        this.hasVideoProjector = hasVideoProjector;
    }

    /**
     * returns true if the lectureHall has a video projector
     * @return
     */
    public boolean isHasVideoProjector() {
        return hasVideoProjector;
    }

    /**
     * sets the lectureHall's video projector variable
     * @param hasVideoProjector
     */
    public void setHasVideoProjector(boolean hasVideoProjector) {
        this.hasVideoProjector = hasVideoProjector;
    }
}
