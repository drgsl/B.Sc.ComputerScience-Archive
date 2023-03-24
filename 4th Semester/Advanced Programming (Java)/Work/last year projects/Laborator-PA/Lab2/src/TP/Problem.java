package TP;

import java.util.ArrayList;

/**
 * A class describing the Transportation Problem, alongside its sources, destinations and costs of transportation.
 * @author Adrian Peterca
 * @version 1.0
 */
public class Problem {

    ArrayList<Cost> costs;
    Source[] sources;
    Destination[] destinations;

    /**
     * The constructor for an instance of the TP.
     * @param sourceArray represents an array of fixed size of different sources.
     * @param destinationArray represents an array of fixed size of different destinations.
     */
    public Problem(Source[] sourceArray, Destination[] destinationArray) {
        for (int i = 0; i < sourceArray.length; ++i)
            for (int j = i + 1; j < sourceArray.length; ++j)
                if (sourceArray[i].equals(sourceArray[j])) {
                    System.out.println("In the TP there cannot be two instances of the same source!");
                    return;
                }

        for (int i = 0; i < destinationArray.length; ++i)
            for (int j = i + 1; j < destinationArray.length; ++j)
                if (destinationArray[i].equals(destinationArray[j])) {
                    System.out.println("In the TP there cannot be two instances of the same destination!");
                    return;
                }

        System.out.println("An instance of the TP was created!");
        costs = new ArrayList<Cost>();
        sources = sourceArray;
        destinations = destinationArray;
    }

    /**
     * Public method for adding the transportation cost between a given Source and a given Destination.
     * The given Source and Destination must exist in the problem.
     * @param s the given Source object
     * @param d the given Destination object
     * @param cost the cost between them
     */
    public void addCost(Source s, Destination d, Integer cost) {
        boolean exists = false;
        for (Source temp : this.sources) {
            if (temp.equals(s)) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            System.out.printf("Error! No sources with name %s were found!\n", s.getName());
            return;
        }

        exists = false;
        for (Destination temp : this.destinations) {
            if (temp.equals(d)) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            System.out.printf("Error! No destinations with name %s were found!\n", d.getName());
            return;
        }

        Cost temp = new Cost(s, d, cost);
        this.costs.add(temp);
    }

    /**
     * A simple function that prints the matrix representing the Sources, Destinations, the demands and supplies,
     * along with the cost for each transportation.
     */
    public void printMatrix() {
        System.out.println("--------------------------------");

        int lines = sources.length + 2;
        int columns = destinations.length + 2;
        String[][] matrix = new String[lines][columns];

        matrix[0][0] = " ";
        matrix[0][columns - 1] = "Supply";
        matrix[lines - 1][0] = "Demand";
        matrix[lines - 1][columns - 1] = " ";

        // Map the sources names
        for (int i = 1; i < lines - 1; ++i) {
            matrix[i][0] = sources[i - 1].toString();
        }

        // Map the destinations names
        for (int i = 1; i < columns - 1; ++i) {
            matrix[0][i] = destinations[i - 1].toString();
        }

        // Map the supply
        for (int i = 1; i < lines - 1; ++i) {
            matrix[i][columns - 1] = sources[i - 1].getInitialSupply().toString();
        }

        // Map the demand
        for (int i = 1; i < columns - 1; ++i) {
            matrix[lines - 1][i] = destinations[i - 1].getDemand().toString();
        }

        // Map all the costs
        for (int i = 1; i < lines - 1; ++i) {
            for (int j = 1; j < columns - 1; ++j) {
                matrix[i][j] = getCostFromTo(sources[i - 1], destinations[j - 1]).toString();
            }
        }

        // Printing out the matrix
        for (int i = 0; i < lines; ++i) {
            for (int j = 0; j < columns; ++j) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    /**
     * Public method for getting the cost of transportation between a Source and a Destination.
     * @param from the Source from where to start
     * @param to the Destination object
     * @return the cost between them
     */
    public Integer getCostFromTo(Source from, Destination to) {
        for (int i = 0; i < costs.size(); ++i) {
            if (costs.get(i).getFrom().equals(from) && costs.get(i).getTo().equals(to)) {
                return costs.get(i).getCost();
            }
        }
        return -1;
    }

    public Source getSourceIndex(int index) {
        if (index > sources.length) return null;
        return sources[index];
    }

    public Destination getDestinationIndex(int index) {
        if (index > destinations.length) return null;
        return destinations[index];
    }


}
