package com.company;

import java.util.List;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class Player implements Runnable {
    private String name;
    private Game game;
    private boolean running;
    public Player(String name) { this.name = name; }
    private boolean submitWord() {
        List<Tile> extracted = game.getBag().extractTiles(7);
        if (extracted.isEmpty()) {
            return false;
        }
        //create a word with all the extracted tiles;
        Scanner s = new Scanner(System.in);
        String word = s.nextLine();
        game.getBoard().addWord(this, word);
        //make the player sleep 50ms;
        try {
            sleep(50);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return true;
    }

    @Override
    public void run() {
        while(running){

        }
    }

    public void setGame(Game game) {
    }

    public void addWord(String word) {
    }

    public String getName() {
        return name;
    }
}
