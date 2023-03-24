package TP;

import java.util.*;

/**
 * A class extending the abstract class Source. It represents a Factory object,
 * along with its constructor.
 */
public final class Factory extends Source {

    public Factory(String name, int supply) {
        setName(name);
        setInitialSupply(supply);

        System.out.printf("Created the %s Factory!\n", this.name);
    }
}
