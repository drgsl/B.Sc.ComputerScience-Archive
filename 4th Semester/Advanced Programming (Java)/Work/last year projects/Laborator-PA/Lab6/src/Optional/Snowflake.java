package Optional;

import java.awt.*;

public class Snowflake extends Polygon implements MyShape{
    int dist = 5;

    public Snowflake(int x, int y, int size) {
        dist = dist * size;

        addPoint(x - dist, y - dist);
        addPoint(x - dist, y - dist * 3);
        addPoint(x - 2 * dist, y - 4 * dist);
        addPoint(x - dist, y - 4 * dist);
        addPoint(x, y - 3 * dist);
        addPoint(x + dist, y - 4 * dist);
        addPoint(x + 2 * dist, y - 4 * dist);
        addPoint(x + dist, y - 3 * dist);

        addPoint(x + dist, y - dist);
        addPoint(x + 3 * dist, y - dist);
        addPoint(x + 4 * dist, y - 2 * dist);
        addPoint(x + 4 * dist, y - dist);
        addPoint(x + 3 * dist, y);
        addPoint(x + 4 * dist, y + dist);
        addPoint(x + 4 * dist, y + 2 * dist);
        addPoint(x + 3 * dist, y + dist);

        addPoint(x + dist, y + dist);
        addPoint(x + dist, y + 3 * dist);
        addPoint(x + 2 * dist, y + 4 * dist);
        addPoint(x + dist, y + 4 * dist);
        addPoint(x, y + 3 * dist);
        addPoint(x - dist, y + 4 * dist);
        addPoint(x - 2 * dist, y + 4 * dist);
        addPoint(x - dist, y + 3 * dist);

        addPoint(x - dist, y + dist);
        addPoint(x - 3 * dist, y + dist);
        addPoint(x - 4 * dist, y + 2 * dist);
        addPoint(x - 4 * dist, y + dist);
        addPoint(x - 3 * dist, y);
        addPoint(x - 4 * dist, y - dist);
        addPoint(x - 4 * dist, y - 2 * dist);
        addPoint(x - 3 * dist, y - dist);
    }

    @Override
    public String getName() {
        return "Snowflake";
    }
}
