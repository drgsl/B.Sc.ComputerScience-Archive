package com.company;

public class Tile {
    private final char letter;
    private final int points;

    public Tile(char c) {
        letter = c;
        points = (int) (Math.random()*10);
    }

}
