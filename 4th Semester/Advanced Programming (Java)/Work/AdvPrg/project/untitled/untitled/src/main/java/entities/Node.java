package entities;

import javax.persistence.*;

@Entity
@Table(name = "nodes")
@NamedQueries({
        @NamedQuery(name = "Node.findAll", query = "select e from Node e order by e.id")
})

public class Node {
    @Id
    @Column(name = "id", nullable = false)
    private int id;

    @Column(name = "x")
    private int x;

    @Column(name = "y")
    private int y;

    public Node(){}

    public Node(int id, int x, int y) {
        this.id = id;
        this.x = x;
        this.y = y;
    }

    public Node(int id, int weight) {
        this.id = id;
        this.x = 5;
        this.y = 5;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    @Override
    public String toString() {
        return "Node{" +
                "id=" + id +
                ", x=" + x +
                ", y=" + y +
                '}';
    }


}
