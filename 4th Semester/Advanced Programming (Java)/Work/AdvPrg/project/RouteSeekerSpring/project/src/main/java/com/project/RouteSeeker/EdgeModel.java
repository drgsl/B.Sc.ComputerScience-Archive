package com.project.RouteSeeker;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.ColumnDefault;

import javax.persistence.*;


@Table(name = "edges")
@Entity
@Getter
@Setter
@Builder
public class EdgeModel {

    @Id
    @JsonProperty("id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @JsonProperty("y")
    @Column(name="y")
    private int y;

    @JsonProperty("x")
    @Column(name="x")
    private int x;

    public EdgeModel(){};

    public EdgeModel(int id, int x, int y){
        this.id=id;
        this.x = x;
        this.y = y;
    }
}
