package bonus.daos;

import bonus.AbstractRepositoryJDBC;
import bonus.DatabaseJDBC;
import bonus.model.City;
import org.hibernate.boot.model.relational.Database;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class CityRepositoryJDBC extends AbstractRepositoryJDBC<City>{
    public CityRepositoryJDBC(DatabaseJDBC s) {
    }

    public CityRepositoryJDBC() {

    }

    public City findById(int id) throws SQLException {
        Connection con = DatabaseJDBC.getInstance("jdbc:postgresql://localhost:5432/postgres", "postgres", "student").getConnection();
        City city = null;
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select name from cities where id='" + id + "'")) {
            city = new City();
            if (rs.next() == true) {
                city.setName(rs.getString(1));
            } else return null;
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            return city;
        }
    }

}
