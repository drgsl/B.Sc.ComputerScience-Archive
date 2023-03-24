package model;

public class Continent extends Land{
    private int id;
    private String name;

    public Continent(int id, String name) {
        super(id, name);
    }

    public Continent() {
    }

    @Override
    public int getId() {
        return id;
    }

    @Override
    public void setId(int id) {
        this.id = id;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void setName(String name) {
        this.name = name;
    }
}
