package com.company;

import java.util.ArrayList;
import java.util.List;

public class Bag {
    private ArrayList<Tile> tiles;
    public Bag() {
        for (char c = 'a'; c < 'z'; c++) {
            tiles.add(new Tile(c));
        }
    }
    public synchronized List<Tile> extractTiles(int howMany) {
        List<Tile> extracted = new ArrayList<>();
        for (int i = 0; i < howMany; i++) {
            if (tiles.isEmpty()) {
                break;
            }
            extracted.add(tiles.get(tiles.size()));
            tiles.remove(tiles.size());
        }
        return extracted;
    }
}
