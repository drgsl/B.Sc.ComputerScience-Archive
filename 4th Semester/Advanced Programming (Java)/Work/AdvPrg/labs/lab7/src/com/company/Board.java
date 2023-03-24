package com.company;

import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    private ArrayList<String> words;
    public static void addWord(Player player, String word) {
        //add the word to the collection;
        player.addWord(word);
        System.out.println(player.getName() + ": " + word);
    }
    @Override
    public String toString() {
        return words.toString();
    }

}
