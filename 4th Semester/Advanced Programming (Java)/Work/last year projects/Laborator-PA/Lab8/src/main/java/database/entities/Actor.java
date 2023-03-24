package database.entities;

public class Actor implements Person {
    private int id;

    private String name;

    private int salary;

    private int movie_id;

    public Actor() {
    }

    public Actor(int id, String name, int salary, int movie_id) {
        this.id = id;
        this.name = name;
        this.salary = salary;
        this.movie_id = movie_id;
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

    @Override
    public int getSalary() {
        return salary;
    }

    @Override
    public void setSalary(int salary) {
        this.salary = salary;
    }

    @Override
    public int getMovie_id() {
        return movie_id;
    }

    @Override
    public void setMovie_id(int movie_id) {
        this.movie_id = movie_id;
    }
}
