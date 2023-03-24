package smartCity.model;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;
import org.hibernate.annotations.ColumnDefault;

import javax.persistence.*;

@Table(name = "locuri")
@Entity
@AllArgsConstructor
@Getter
@Setter
@Builder
public class Loc {

    @Id
    @JsonProperty("id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @JsonProperty("id_loc")
    @Column(name="id_loc")
    private int idLoc;

    @JsonProperty("id_parcare")
    @Column(name="id_parcare")
    private int idParcare;

    @JsonProperty("disponibil")
    @Column(name="disponibil")
    @ColumnDefault("true")
    private boolean disponibil;

    public Loc(){};

    public Loc(int id, int idLoc, int idParcare){
        this.id=id;
        this.idLoc = idLoc;
        this.idParcare = idParcare;
    }
}
