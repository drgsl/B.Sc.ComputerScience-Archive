package com.project.RouteSeeker;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;


@Table(name = "nodes")
@Entity
@Getter
@Setter
@Builder
public class NodeModel {

    @Id
    @JsonProperty("id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @JsonProperty("src")
    @Column(name="src")
    private int src;

    @JsonProperty("dst")
    @Column(name="dst")
    private int dst;

    @JsonProperty("cost")
    @Column(name="cost")
    private int cost;

    @JsonProperty("name")
    @Column(name="name")
    private String name;


    public NodeModel(){};

    public NodeModel(int id, int src, int dst, int cost, String name) {
        this.id = id;
        this.src = src;
        this.dst = dst;
        this.cost = cost;
        this.name = name;
    }
}
