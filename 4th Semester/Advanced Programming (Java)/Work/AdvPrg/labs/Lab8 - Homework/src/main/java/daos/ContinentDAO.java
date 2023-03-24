package daos;

import connectionDB.Database;
import lombok.NoArgsConstructor;
import model.Continent;
import model.Country;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
public class ContinentDAO {

    public void create(String name) throws SQLException {
        Connection con = Database.getConnection();
        try (PreparedStatement pstmt = con.prepareStatement(
                "insert into continents (name) values (?)")) {
            pstmt.setString(1, name);
            pstmt.executeUpdate();
        }
    }
    public Continent findByName(String name) throws SQLException {
        Connection con = Database.getConnection();
        Continent returnContinent = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from continents where name='" + name + "'")) {
            while (rs.next()) {
                returnContinent = new Continent();
                returnContinent.setId(rs.getInt(1));
                returnContinent.setName(rs.getString(2));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnContinent;
    }
    public Continent findById(int id) throws SQLException {
        Connection con = Database.getConnection();
        Continent returnContinent = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from continents where id='" + id + "'")) {
            while (rs.next()) {
                returnContinent = new Continent();
                returnContinent.setId(rs.getInt(1));
                returnContinent.setName(rs.getString(2));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnContinent;
    }

    public void loadContinents(){
        Connection con = Database.getConnection();
        List<String> continents = new ArrayList<>();
        continents.add("Australia");
        continents.add("Europe");
        continents.add("Asia");
        continents.add("Africa");
        continents.add("North America");
        continents.add("South America");
        continents.add("Antarctica");
        continents.add("Central America");
        try{
            for(String continent:continents) {
                PreparedStatement pstmt = con.prepareStatement("insert into continents (name) values (?)");
                pstmt.setString(1, continent);
                pstmt.executeUpdate();
            }
        }
        catch(SQLException e){
            e.printStackTrace();
        }
    }

    public List<Continent> findAll() throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select * from continents")) {
            List<Continent> continents = new ArrayList<>();

            while (rs.next()) {
                continents.add(new Continent(rs.getInt(0), rs.getString(1)));
            }
            return continents;
        }
    }
}
