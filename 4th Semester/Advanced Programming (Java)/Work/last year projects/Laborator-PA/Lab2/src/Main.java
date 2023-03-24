import TP.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        Destination D1 = new Destination("D1", 20);
        Destination D2 = new Destination("D2", 25);
        Destination D3 = new Destination("D3", 25);

        Source S1 = new Factory("S1", 10);
        Source S2 = new Factory("S2", 35);
        Source S3 = new Factory("S3", 25);


        Source[] sources = new Source[3];
        Destination[] destinations = new Destination[3];

        sources[0] = S1;
        sources[1] = S2;
        sources[2] = S3;
        destinations[0] = D1;
        destinations[1] = D2;
        destinations[2] = D3;

        Problem problemTP = new Problem(sources, destinations);
        problemTP.addCost(S1, D1, 2);
        problemTP.addCost(S1, D2, 3);
        problemTP.addCost(S1, D3, 1);
        problemTP.addCost(S2, D1, 5);
        problemTP.addCost(S2, D2, 4);
        problemTP.addCost(S2, D3, 8);
        problemTP.addCost(S3, D1, 5);
        problemTP.addCost(S3, D2, 6);
        problemTP.addCost(S3, D3, 8);

        problemTP.printMatrix();

        Solution solution = new Solution(problemTP, 3, 3);
        solution.solve();
        solution.printResult();
    }
}
