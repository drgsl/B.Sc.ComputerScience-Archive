package daos;

import connectionDB.Database;
import lombok.NoArgsConstructor;
import model.Country;

import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
public class CountryDAO {

    public void create(String name, int code, int continent_id) throws SQLException {
        Connection con = Database.getConnection();
        try (PreparedStatement pstmt = con.prepareStatement(
                "insert into countries(name, continent_id) values (?,?)")) {
            pstmt.setString(1, name);
            pstmt.setInt(2, continent_id);
            pstmt.executeUpdate();
        }
    }

    public Country findByName(String name) throws SQLException {
        name = name.replaceAll("'", " ");
        Connection con = Database.getConnection();
        Country returnCountry = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from countries where name='" + name + "'")) {
            while (rs.next()) {
                returnCountry = new Country();
                returnCountry.setId(rs.getInt(1));
                returnCountry.setName(rs.getString(2));
                returnCountry.setContinentId(rs.getInt(3));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCountry;
    }

    public Country findById(int id) throws SQLException {
        Connection con = Database.getConnection();
        Country returnCountry = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from countries where id='" + id + "'")) {
            while (rs.next()) {
                returnCountry = new Country(rs.getInt(0), rs.getString(1), rs.getInt(2));
                returnCountry.setId(rs.getInt(1));
                returnCountry.setName(rs.getString(2));
                returnCountry.setContinentId(rs.getInt(3));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCountry;
    }

    public Country findByContinent(String continentName) throws SQLException {
        Connection con = Database.getConnection();
        Country returnCountry = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from countries cou join continents con on cou.continent_id=con.id " +
                     "where con.name='" + continentName + "'")) {
            while (rs.next()) {
                returnCountry = new Country(rs.getInt(0), rs.getString(1), rs.getInt(2));
                returnCountry.setId(rs.getInt(1));
                returnCountry.setName(rs.getString(2));
                returnCountry.setContinentId(rs.getInt(3));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCountry;
    }

    public List<Country> findAll() throws SQLException {

        Connection con = Database.getConnection();

        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select * from countries")) {

            List<Country> countries = new ArrayList<>();

            while (rs.next()) {

                countries.add(new Country(rs.getInt(0), rs.getString(1),
                        rs.getInt(2)));
            }
            return countries;
        }
    }

    public void loadFromFile(){
        try {
            Connection con = Database.getConnection();
            PreparedStatement pstmt = con.prepareStatement(
                    "insert into countries(name, continent_id) values (?,?)");
            ContinentDAO continent = new ContinentDAO();

            File file=new File("src/main/resources/concap.csv");
            FileReader fr=new FileReader(file);
            BufferedReader br=new BufferedReader(fr);
            String line;
            String[] columns;
            while((line=br.readLine())!=null)
            {
                columns = line.split(",");
                String name = columns[0].replaceAll("'", " ");
                pstmt.setString(1,name);
                int id;
                if((id = continent.findByName(columns[5]).getId()) != -1)
                    pstmt.setInt(2,id);
                else
                    pstmt.setInt(2, 1);
                CountryDAO country = new CountryDAO();
                //if(country.findByName(columns[0]).getId() == 0)
                    pstmt.executeUpdate();
            }
            fr.close();
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }
}

