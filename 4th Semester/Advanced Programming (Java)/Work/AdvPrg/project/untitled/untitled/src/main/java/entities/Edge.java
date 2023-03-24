package entities;

import lombok.Data;

import javax.persistence.*;


@Entity
@Table(name = "edges")
@NamedQueries({
        @NamedQuery(name = "Edge.findAll", query = "select e from Edge e order by e.id")
})

public class Edge {

    @Id
    @Column(name = "id", nullable = false)
    private int id;

    @ManyToOne
    @JoinColumn(name = "src")
    private Node src;

    @ManyToOne
    @JoinColumn(name = "dst")
    private Node dest;

    @Column(name = "cost")
    private int weight;

    @Column(name = "name")
    private String name;

    public Edge(Node src, Node dest, int weight) {
        this.src = src;
        this.dest = dest;
        this.weight = weight;
    }

    public Edge() {

    }

    public Node getSrc() {
        return src;
    }

    public void setSrc(Node src) {
        this.src = src;
    }

    public Node getDest() {
        return dest;
    }

    public void setDest(Node dest) {
        this.dest = dest;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    @Override
    public String toString() {
        return "Edge{" +
                "src=" + src +
                ", dest=" + dest +
                ", weight=" + weight +
                '}';
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
