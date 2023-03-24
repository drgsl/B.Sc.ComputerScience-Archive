package smartCity.model;

import lombok.Data;

@Data
public class RezervareBody {
    private String username;
    private int idParcare;
    private int idLoc;
    private int durata;

    public RezervareBody(String username, int idParcare, int idLoc, int durata){
        this.username = username;
        this.idLoc = idLoc;
        this.idParcare = idParcare;
        this.durata = durata;
    }

    public RezervareBody(String username, int idParcare, int idLoc){
        this.username = username;
        this.idLoc = idLoc;
        this.idParcare = idParcare;
    }

    public RezervareBody(){}
}
