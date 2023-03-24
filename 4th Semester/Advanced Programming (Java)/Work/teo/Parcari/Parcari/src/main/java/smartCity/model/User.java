package smartCity.model;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.*;

import javax.persistence.*;

@Table(name = "users")
@Entity
@AllArgsConstructor
@Getter
@Setter
@Builder
@Data
public class User {

    @Id
    @JsonProperty("id")
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;

    @JsonProperty("username")
    @Column(name="username")
    private String username;

    @JsonProperty("parola")
    @Column(name="parola")
    private String parola;

    @JsonProperty("email")
    @Column(name="email")
    private String email;

    public User(){};
}
