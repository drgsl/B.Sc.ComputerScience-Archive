package laborator11.clientapplication.model;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@NoArgsConstructor
@Setter
@Getter
@AllArgsConstructor
public class User {

    private int id;
    private String name;

    public User(String name){
        this.name = name;
    }
}