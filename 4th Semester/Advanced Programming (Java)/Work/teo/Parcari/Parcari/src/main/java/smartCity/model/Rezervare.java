package smartCity.model;

import lombok.Data;

@Data
public class Rezervare {
    private int idLoc;
    private int idUser;
    private int durata;

    public Rezervare(){}

    public Rezervare(int idLoc, int idUser, int durata){
        this.idLoc = idLoc;
        this.idUser = idUser;
        this.durata = durata;
    }
}
