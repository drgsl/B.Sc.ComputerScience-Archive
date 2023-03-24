package database.daos;

import database.connections.MyDatabaseConn;
import database.entities.Actor;
import database.entities.Director;
import database.entities.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class DirectorDao {

    private final PreparedStatement getByIdStmt;
    private final PreparedStatement insertStmt;
    private final PreparedStatement deleteAllStmt;


    public DirectorDao() throws SQLException {
        Connection connection = MyDatabaseConn.getInstance().getConnection();
        getByIdStmt = connection.prepareStatement("select * from directors where id = ?");
        insertStmt = connection.prepareStatement("insert into directors values (?, ?, ?, ?)");
        deleteAllStmt = connection.prepareStatement("delete from directors");
    }

    public Person getById(int id) throws SQLException {
        if (id < 1) {
            System.out.println("Invalid ID (must be over 0!)");
            return null;
        }

        getByIdStmt.setInt(1, id);
        ResultSet result =  getByIdStmt.executeQuery();

        Director returnDirector = null;

        while (result.next()) {
            returnDirector =  new Director();
            returnDirector.setId(result.getInt(1));
            returnDirector.setName(result.getString(2));
            returnDirector.setSalary(result.getInt(3));
            returnDirector.setMovie_id(result.getInt(4));
        }
        return returnDirector;
    }

    public boolean insert(Director director) throws SQLException {
        if (director == null) {
            System.out.println("Cannot insert a null director!");
            return false;
        }

        insertStmt.setInt(1, director.getId());
        insertStmt.setString(2, director.getName());
        insertStmt.setInt(3, director.getSalary());
        insertStmt.setInt(4, director.getMovie_id());

        return insertStmt.execute();
    }

    public boolean deleteAll() throws SQLException {
        return deleteAllStmt.execute();
    }
}
