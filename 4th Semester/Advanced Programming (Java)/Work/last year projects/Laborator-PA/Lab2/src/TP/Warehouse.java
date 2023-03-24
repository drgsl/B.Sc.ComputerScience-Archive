package TP;

import java.util.*;

/**
 * A class extending the abstract class Source. It represents a Warehouse object,
 * along with its constructor.
 */
public final class Warehouse extends Source {

    public Warehouse(String name, int supply) {
        setName(name);
        setInitialSupply(supply);

        System.out.printf("Created the %s Warehouse!\n", this.name);
    }

}
