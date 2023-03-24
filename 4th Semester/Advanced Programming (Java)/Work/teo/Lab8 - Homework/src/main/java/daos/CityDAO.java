package daos;

import connectionDB.Database;
import lombok.NoArgsConstructor;
import model.City;
import model.Country;

import java.io.*;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

@NoArgsConstructor
public class CityDAO {

    public void create(int countryId, String name, boolean capital, double latitude, double longitude) throws SQLException {
        Connection con = Database.getConnection();
        try (PreparedStatement pstmt = con.prepareStatement(
                "insert into cities(country_id, name, capital, latitude, longitude) values (?,?,?,?,?)")) {
            pstmt.setInt(1, countryId);
            pstmt.setString(2, name);
            pstmt.setInt(3, capital ? 1 : 0);
            pstmt.setDouble(4, latitude);
            pstmt.setDouble(5, longitude);
            pstmt.executeUpdate();
        }
    }

    public City findByName(String name) throws SQLException {
        name = name.replaceAll("'", " ");
        Connection con = Database.getConnection();
        City returnCity = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from cities where name='" + name + "'")) {
            while (rs.next()) {
                returnCity = new City();
                returnCity.setId(rs.getInt(1));
                returnCity.setCountryId(rs.getInt(2));
                returnCity.setName(rs.getString(3));
                returnCity.setCapital(rs.getInt(4));
                returnCity.setLatitude(rs.getDouble(5));
                returnCity.setLongitude(rs.getDouble(6));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCity;
    }

    public City findById(int id) throws SQLException {
        Connection con = Database.getConnection();
        City returnCity = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from cities where id='" + id + "'")) {
            while (rs.next()) {
                returnCity = new City();
                returnCity.setId(rs.getInt(1));
                returnCity.setCountryId(rs.getInt(2));
                returnCity.setName(rs.getString(3));
                returnCity.setCapital(rs.getInt(4));
                returnCity.setLatitude(rs.getDouble(5));
                returnCity.setLongitude(rs.getDouble(6));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCity;
    }

    public double getDistanceBetweenCities(String c1, String c2) {
        Connection con = Database.getConnection();
        double distance = -1;
        c1 = c1.replaceAll("'"," ");
        c2 = c2.replaceAll("'"," ");
        try {
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery(
                    "select latitude, longitude from cities where name='" + c1 + "'" + " or name='" + c2 + "'");
            if (rs == null) {
                System.out.println("This city doesn't exist!");
                return -1;
            }

            rs.next();
            double lat1 = rs.getDouble(1);
            double long1 = rs.getDouble(2);
            rs.next();
            double lat2 = rs.getDouble(1);
            double long2 = rs.getDouble(2);
            distance = computeDistance(lat1, long1, lat2, long2);
        } catch (SQLException e) {
            e.printStackTrace();
        }
        finally {
            return distance;
        }
    }

    public double computeDistance(double lat1, double long1, double lat2, double long2) {
        long1 = Math.toRadians(long1);
        long2 = Math.toRadians(long2);
        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        double lon = long2 - long1;
        double lat = lat2 - lat1;
        double a = Math.pow(Math.sin(lat / 2), 2)
                + Math.cos(lat1) * Math.cos(lat2)
                * Math.pow(Math.sin(lon / 2), 2);

        double c = 2 * Math.asin(Math.sqrt(a));
        double radius = 6371;
        return (c * radius * 1.609344 );
    }

    public void loadFromFile() throws SQLException {
        try {
            Connection con = Database.getConnection();
            PreparedStatement pstmt = con.prepareStatement(
                    "insert into cities(country_id, name, capital, latitude, longitude) values (?,?,?,?,?)");
            CountryDAO country = new CountryDAO();

            File file = new File("src/main/resources/concap.csv");
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            String[] columns;
            while ((line = br.readLine()) != null) {
                columns = line.split(",");
                int id;
                if ((id = country.findByName(columns[0]).getId()) != -1)
                    pstmt.setInt(1, id);
                else
                    pstmt.setInt(1, 1);

                String name = columns[1].replaceAll("'", " ");
                pstmt.setString(2, name);
                pstmt.setInt(3, 1);
                pstmt.setDouble(4, Double.parseDouble(columns[2]));
                pstmt.setDouble(5, Double.parseDouble(columns[3]));

                CityDAO city = new CityDAO();
                if (city.findByName(columns[1]) ==null)
                    pstmt.executeUpdate();
            }
            fr.close();
        } catch (IOException | SQLException e) {
            e.printStackTrace();
        }
    }

    /**
     * Function to find all the cities in the database that belong
     * to a country.
     *
     * @param continentName
     * @return
     * @throws SQLException
     */
    public City findByCountry(String continentName) throws SQLException {
        Connection con = Database.getConnection();
        City returnCity = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery("select * from countries cou join continents con on cou.continent_id=con.id " +
                     "where con.name='" + continentName + "'")) {
            while (rs.next()) {
                returnCity = new City();
                returnCity.setId(rs.getInt(1));
                returnCity.setCountryId(rs.getInt(2));
                returnCity.setName(rs.getString(3));
                returnCity.setCapital(rs.getInt(4));
                returnCity.setLatitude(rs.getDouble(5));
                returnCity.setLongitude(rs.getDouble(6));
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
        return returnCity;
    }

    public List<City> findAll() throws SQLException {

        Connection con = Database.getConnection();

        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select * from cities")) {

            List<City> cities = new ArrayList<>();

            while (rs.next()) {
                cities.add(new City(rs.getInt(1), rs.getInt(2),
                        rs.getString(3), rs.getInt(4), rs.getDouble(5), rs.getDouble(6)));
            }
            return cities;
        }
    }
}


