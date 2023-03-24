package smartCity.model;

import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;

import javax.persistence.*;

@Table(name = "parcari")
@Entity
@AllArgsConstructor
@Getter
@Setter
@Builder
public class Parcare {

    @Id
    @JsonProperty("id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @JsonProperty("latitudine")
    @Column(name="latitudine")
    private double latitudine;

    @JsonProperty("longitudine")
    @Column(name="longitudine")
    private double longitudine;

    @JsonProperty("strada")
    @Column(name="strada")
    private String strada;

    public Parcare(){}
}
