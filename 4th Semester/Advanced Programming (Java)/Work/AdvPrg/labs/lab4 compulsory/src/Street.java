public class Street {
    private String name;
    private float length;

    private Intersection intersection1;
    private Intersection intersection2;


    public Street(String name, float length) {
        this.name = name;
        this.length = length;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public float getLength() {
        return length;
    }

    public void setLength(float length) {
        this.length = length;
    }
}
