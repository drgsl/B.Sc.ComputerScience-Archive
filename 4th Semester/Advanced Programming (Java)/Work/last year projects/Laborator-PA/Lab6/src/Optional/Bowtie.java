package Optional;

import java.awt.*;

public class Bowtie extends Polygon implements MyShape {
    int dist = 5;
    public Bowtie(int x, int y, int size) {
        dist = dist * size;

        addPoint(x - 2 * dist, y - dist);
        addPoint(x - 2 * dist, y + dist);
        addPoint(x + 2 * dist, y - dist);
        addPoint(x + 2 * dist, y + dist);
    }

    @Override
    public String getName() {
        return "Bowtie";
    }
}
