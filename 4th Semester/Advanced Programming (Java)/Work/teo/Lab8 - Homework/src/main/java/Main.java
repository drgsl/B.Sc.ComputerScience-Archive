import connectionDB.Database;
import daos.CityDAO;
import daos.ContinentDAO;
import daos.CountryDAO;
import graphics.MainFrame;

import java.io.IOException;
import java.sql.Connection;
import java.sql.SQLException;

public class Main {

    public static void main(String[] args) throws SQLException {

        try{
            Database.createConnection();

            var continent = new ContinentDAO();
            continent.loadContinents();
            var country = new CountryDAO();
            var city = new CityDAO();

            country.loadFromFile();
            city.loadFromFile();


            System.out.println("The distance between Paris and Moscow is: " +
                    city.getDistanceBetweenCities("Bucharest", "Budapest") + " km");

            System.out.println(city.findByName("Hargeisa"));

            MainFrame frame= new MainFrame();
            frame.setVisible(true);



        }
        catch (SQLException e){
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}

