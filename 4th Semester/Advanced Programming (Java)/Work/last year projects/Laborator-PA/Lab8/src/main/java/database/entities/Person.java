package database.entities;

public interface Person {
    void setId(int id);
    int getId();

    void setName(String name);
    String getName();

    int getSalary();

    void setSalary(int salary);

    int getMovie_id();

    void setMovie_id(int movie_id);
}
