import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class Main {

    public static void main(String[] args) {
        try{
            Database.createConnection();
            Connection con = Database.getConnection();
            System.out.println(con);
            var continents = new ContinentDAO();
            continents.create("Europe");
            System.out.println(continents.findByName("Europe"));


            var countries = new CountryDAO();

            int europeId = continents.findByName("Europe");

            countries.create("Romania", europeId);
            countries.create("Ukraine", europeId);

            System.out.println(countries.findByContinent("Europe"));

            var cities = new CityDAO();
            cities.create(countries.findByName("Romania"),"Iasi",0, (float)  47.17, (float) 27.57);
            cities.create(countries.findByName("Romania"),"Vaslui",0, (float)  46.65, (float) 27.73);


        }
        catch (SQLException e){
            e.printStackTrace();
        }
    }

}
