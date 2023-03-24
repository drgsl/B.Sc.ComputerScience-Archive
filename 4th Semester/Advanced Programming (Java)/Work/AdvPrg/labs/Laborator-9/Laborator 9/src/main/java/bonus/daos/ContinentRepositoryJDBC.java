package bonus.daos;

import bonus.AbstractRepositoryJDBC;
import bonus.DatabaseJDBC;
import bonus.model.Continent;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ContinentRepositoryJDBC extends AbstractRepositoryJDBC<Continent> {
    public ContinentRepositoryJDBC(DatabaseJDBC databaseJDBC) {
    }

    public ContinentRepositoryJDBC() {

    }

    public Continent findById(int id) throws SQLException {
        Connection con = DatabaseJDBC.getInstance("jdbc:postgresql://localhost:8081/postgres", "postgres", "STUDENT").getConnection();
        Continent continent = new Continent();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select name from continents where id='" + id + "'")) {
            rs.next();
            continent.setName(rs.getString(1));
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            return continent;
        }
    }
}
