package compulsory.items;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

/**
 * Queries and database mapping
 */

@Getter
@Setter
@Entity
@Table(name = "cities")
@NamedQueries({
        @NamedQuery(name = "City.findAll", query = "select e from City e order by e.name"),

        @NamedQuery(name = "City.findByCountry", query = "select e from City e where e.country = :country"),

        @NamedQuery(name = "City.findByName", query = "select e from City e where e.name = :name"),

        @NamedQuery(name = "City.findByNamePattern", query = "select e from City e where e.name like :pattern"),

        @NamedQuery(name = "City.findById", query = "select e from City e where e.id = :id"),

        @NamedQuery(name = "City.getCount", query = "select count(*) from City")
})

/**
 * this class describes the city and its relations
 */
public class City implements Serializable {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    @Column(name = "id", nullable = false)
    private Long id;

    private String name;
    private int population;


    @ManyToOne(cascade=CascadeType.MERGE)
    @JoinColumn(name = "country_id")
    private Country country;


    @ManyToMany(cascade=CascadeType.MERGE, fetch = FetchType.EAGER)
    @JoinTable(name="sisters",
            joinColumns={@JoinColumn(name="id_city1")},
            inverseJoinColumns={@JoinColumn(name="id_city2")})
    private Set<City> cities1 = new HashSet<City>();

    @ManyToMany(cascade = CascadeType.MERGE)
    @JoinTable(name="sisters",
            joinColumns={@JoinColumn(name="id_city2")},
            inverseJoinColumns={@JoinColumn(name="id_city1")})
    private Set<City> cities2 = new HashSet<City>();

    public City() {
    }

    public City(String name, Country country) {
        this.name = name;
        this.country = country;
    }

    @Override
    public String toString() {
        return "City{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", country=" + country +
                '}';
    }
}

