package compulsory.items;

import lombok.Data;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Set;

@Getter
@Setter
@NoArgsConstructor

@Entity
@Table(name = "continents")
@NamedQueries({
        @NamedQuery(name = "Continent.findAll",
                query = "select e from Continent e order by e.name"),
        @NamedQuery(name = "Continent.findById", query = "select e from Continent e where e.id = :id"),

        @NamedQuery(name = "Continent.findByName", query = "select e from Continent e where e.name = :name"),

        @NamedQuery(name = "Continent.findByNamePattern", query = "select e from Continent e where e.name like :pattern")
})

public class Continent implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY, generator = "id")
    @Column(name = "id")
    private Integer id;

    @Column(name = "name")
    private String name;

    @OneToMany(mappedBy="continent", cascade=CascadeType.MERGE)
    private Set<Country> countries;

    public Continent(String name){
        this.name = name;
    }

}
