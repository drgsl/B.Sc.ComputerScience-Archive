package bonus.daos;

import bonus.AbstractRepositoryJDBC;
import bonus.DatabaseJDBC;
import bonus.model.Country;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class CountryRepositoryJDBC extends AbstractRepositoryJDBC<Country> {
    public CountryRepositoryJDBC(DatabaseJDBC singletonJDBC) {
    }

    public CountryRepositoryJDBC() {

    }

    public Country findById(int id) throws SQLException {
        Connection con = DatabaseJDBC.getInstance("jdbc:postgresql://localhost:8081/postgres","postgres","STUDENT").getConnection();
        Country country = new Country();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select name from countries where id='" + id + "'")) {
            rs.next();
            country.setId(id);
            country.setName(rs.getString(1));
        }
        catch(SQLException e){
            e.printStackTrace();
        }
        finally {
            return country;
        }
    }
}
