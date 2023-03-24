package TTPP;

import javax.sound.sampled.Line;
import java.util.*;

public class TravelPlan {
    City city;
    /**
     * A list describing the preferences for each location.
     * The elements are added in order of preferences (the first one is the most preferred).
     */
    LinkedList<String> preferences;

    public TravelPlan(City city) {
        this.city = city;
        preferences = new LinkedList<>();
    }

    public void addPreferenceForLocation(Location location) {
        for (String s : this.preferences) {
            if (s.equals(location.getName())) {
                System.out.println("Cannot add a location twice to the list of preferences!");
                return;
            }
        }

        preferences.add(location.getName());
    }

    public Integer getShortestPathBetween(Location locationStart, Location locationEnd) {
        boolean exists1 = false, exists2 = false;
        for (Location temp : city.locations) {
            if (locationStart == temp) exists1 = true;
            if (locationEnd == temp) exists2 = true;
            if (exists1 && exists2) break;
        }
        if (!exists1 || !exists2) return -1;

        // Constructing the distance matrix
        Integer[][] distanceMatrix = new Integer[city.locations.size()][city.locations.size()];
        for (int i = 0; i < city.locations.size(); i++) {
            for (int j = 0; j < city.locations.size(); j++) {
                if (i == j)
                    distanceMatrix[i][j] = 0;
                else
                    distanceMatrix[i][j] = city.getLocationAtIndex(i).getTravelCostTo(city.getLocationAtIndex(j));
            }
        }

        int currentNode = city.getIndexOfLocation(locationStart);
        int end = city.getIndexOfLocation(locationEnd);

        // List of all visited nodes
        Boolean[] visitedNodes = new Boolean[city.locations.size()];
        // List of all distances from current node to all others
        Integer[] currentDistances = new Integer[city.locations.size()];

        // First, all nodes are unvisited
        Arrays.fill(visitedNodes, false);
        // And all distances are infinite, except the first node.
        Arrays.fill(currentDistances, -1);
        currentDistances[currentNode] = 0;

        while (true) {
            // Are there any unvisited nodes?
            boolean existsUnvisitedNodes = false;
            for (int i = 0; i < visitedNodes.length; i++) {
                if (!visitedNodes[i]) {
                    existsUnvisitedNodes = true;
                    break;
                }
            }
            // If all nodes are visited, then exit the loop.
            if (!existsUnvisitedNodes) {
                break;
            }

            // Mark as visited
            visitedNodes[currentNode] = true;

            // Perform relaxation
            for (int i = 0; i < currentDistances.length; i++) {
                if (i == currentNode) continue;
                if (distanceMatrix[currentNode][i] != -1 && (currentDistances[i] == -1 || (currentDistances[currentNode] + distanceMatrix[currentNode][i] < currentDistances[i] &&  currentDistances[currentNode] != -1))) {
                    currentDistances[i] = currentDistances[currentNode] + distanceMatrix[currentNode][i];
                }
            }

            // Select the next node

            // First, get the minimum value for distance and count how many times that specific value appears
            int minimumValueIndex = -1;
            int minimumValuesCounter = 0;
            for (int i = 0; i < currentDistances.length; i++) {
                if (visitedNodes[i] || currentDistances[i] == -1) continue;

                if (minimumValueIndex == -1 || (currentDistances[minimumValueIndex] > currentDistances[i])) {
                    minimumValueIndex = i;
                    minimumValuesCounter = 1;
                }

                if (minimumValueIndex != i && currentDistances[minimumValueIndex].equals(currentDistances[i])) {
                    minimumValuesCounter++;
                }
            }

            // All nodes have been visited
            if (minimumValueIndex == -1) {
                break;
            }

            // If there are multiple minimum values, select the one with the highest preference
            if (minimumValuesCounter == 1) {
                currentNode = minimumValueIndex;
            }
            else {
                LinkedList<Integer> locations = new LinkedList<>();
                // Map all minimum values
                for (int i = 0; i < currentDistances.length; i++) {
                    if (currentDistances[i].equals(currentDistances[minimumValueIndex])) {
                        locations.add(i);
                    }
                }
                // Find the most preferred location from the selected ones
                int max = preferences.indexOf(city.getLocationAtIndex(minimumValueIndex).getName());
                currentNode = minimumValueIndex;
                for (Integer i : locations) {
                    if (!currentDistances[i].equals(currentDistances[minimumValueIndex])) continue;
                    int temp = preferences.indexOf(city.getLocationAtIndex(i).getName());
                    if (temp < max) {
                        max = temp;
                        currentNode = i;
                    }
                }
            }

        }
        return currentDistances[end];
    }
}
