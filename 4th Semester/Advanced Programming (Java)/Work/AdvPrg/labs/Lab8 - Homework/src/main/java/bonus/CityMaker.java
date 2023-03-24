package bonus;

import com.github.javafaker.Faker;
import connectionDB.Database;

import javax.xml.transform.Result;
import java.sql.*;
import java.util.Random;

import static java.lang.Integer.parseInt;

public class CityMaker implements Runnable {
    private Faker faker;
    private Connection con;

    public CityMaker() {
        faker = new Faker();
    }

    public void create() {
        try {
            con = DBCPDataSource.getConnection();

            String name = faker.address().cityName();
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("select count(*) from fake_cities");
            if (rs == null) return;
            rs.next();
            int id = rs.getInt(1);
            if (id == 0) id = 1;
            else id++;
            PreparedStatement pstmt = con.prepareStatement("insert into fake_cities (id,name) values (?,?)");
            pstmt.setInt(1, id);
            pstmt.setString(2, name);
            pstmt.executeUpdate();
            con.close();

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void sisterhood() {
        try {
            con = DBCPDataSource.getConnection();
            PreparedStatement pstmt1 = con.prepareStatement("insert into sisters (sister1, sister2) values (?,?)");
            Statement stmt1 = con.createStatement();
            ResultSet rs = stmt1.executeQuery("select count(*) from fake_cities");
            rs.next();
            int counter = rs.getInt(1);
            int random1, random2;
            Random rand = new Random();
            if (counter == 0) return;
            random1 = rand.nextInt(counter - 1) + 1;
            random2 = rand.nextInt(counter - 1) + 1;
            while (random1 == random2) {
                random2 = rand.nextInt(counter);
            }
            pstmt1.setInt(1, random1);
            pstmt1.setInt(2, random2);
            pstmt1.executeUpdate();
            con.close();
        }
        catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public String findById(int id) {
        String name = new String();
        try {
            Connection con = DBCPDataSource.getConnection();
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(
                    "select name from fake_cities where id='" + id + "'");
            rs.next();
            name = rs.getString(1);
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            return name;
        }
    }


    public void run() {
        int counter = 0;
        while (counter < 200) {
            create();
            counter++;
        }

    }
}
