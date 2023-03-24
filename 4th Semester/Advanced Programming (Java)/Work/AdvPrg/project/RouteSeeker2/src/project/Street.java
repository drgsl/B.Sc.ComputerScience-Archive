package project;

public class Street {
    private String name;
    private int length;
    private int src;
    private int dest;

    public Street(String name, int src, int dest , int length) {
        this.name = name;
        this.src = src;
        this.dest = dest;
        this.length = length;
    }

    public int getSrc() {
        return src;
    }

    public void setSrc(int src) {
        this.src = src;
    }

    public int getDest() {
        return dest;
    }

    public void setDest(int dest) {
        this.dest = dest;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int length) {
        this.length = length;
    }
}
