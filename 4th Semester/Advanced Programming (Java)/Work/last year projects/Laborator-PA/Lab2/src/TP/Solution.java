package TP;

/**
 * A class representing a solution to the TP.
 */
public class Solution {
    Integer sourcesNumber;
    Integer destinationsNumber;
    Integer[][] result;
    Problem problem;

    /**
     * Default constructor for an object of type Solution.
     * @param problem the instance of the problem the Solution object should resolve
     * @param sourcesNumber the number of sources
     * @param destinationsNumber the number of destinations
     */
    public Solution(Problem problem, Integer sourcesNumber, Integer destinationsNumber) {
        this.problem = problem;
        this.result = new Integer[sourcesNumber][destinationsNumber];
        this.sourcesNumber = sourcesNumber;
        this.destinationsNumber = destinationsNumber;
    }

    /**
     * A public method implementing a Greedy approach to solve the problem.
     * It stores in the result variable the amount of supplies each source sends to each destination.
     */
    public void solve() {

        for (int i = 0 ; i < sourcesNumber; ++i) {
            for (int j = 0; j < destinationsNumber; ++j) {
                // The demand is greater than the remaining supply
                if (problem.getSourceIndex(i).getRemainingSupply() < problem.getDestinationIndex(j).getDemand()) {
                    result[i][j] = problem.getSourceIndex(i).getRemainingSupply();

                    // Send the supplies to the destination (and decrease its demand)
                    problem.getDestinationIndex(j).setDemand(problem.getDestinationIndex(j).getDemand() - problem.getSourceIndex(i).getRemainingSupply());
                    // Mark the remaining supply as empty
                    problem.getSourceIndex(i).extractSupply(problem.getSourceIndex(i).getRemainingSupply());
                }
                else {
                    result[i][j] = problem.getDestinationIndex(j).getDemand();

                    // Send the supplies
                    problem.getSourceIndex(i).extractSupply(problem.getDestinationIndex(j).getDemand());
                    // Mark the destination demand as zero
                    problem.getDestinationIndex(j).setDemand(0);
                }
            }
        }
    }

    /**
     * A public method for printing the result matrix.
     */
    public void printResult() {
        int overallCost = 0;
        for (int i = 0; i < sourcesNumber; ++i) {
            for (int j = 0; j < destinationsNumber; ++j) {
                System.out.print(result[i][j] + " ");
                overallCost += result[i][j] * problem.getCostFromTo(problem.getSourceIndex(i), problem.getDestinationIndex(j));
            }
            System.out.println();
        }
        System.out.println("Total cost: " + overallCost);
    }


}
