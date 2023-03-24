package database.daos;

import database.connections.MyDatabaseConn;
import database.entities.Actor;
import database.entities.Person;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ActorDao {

    private final PreparedStatement getByIdStmt;
    private final PreparedStatement insertStmt;
    private final PreparedStatement deleteAllStmt;


    public ActorDao() throws SQLException {
        Connection connection = MyDatabaseConn.getInstance().getConnection();
        getByIdStmt = connection.prepareStatement("select * from actors where id = ?");
        insertStmt = connection.prepareStatement("insert into actors values (?, ?, ?, ?)");
        deleteAllStmt = connection.prepareStatement("delete from actors");
    }

    public Person getById(int id) throws SQLException {
        if (id < 1) {
            System.out.println("Invalid ID (must be over 0!)");
            return null;
        }

        getByIdStmt.setInt(1, id);
        ResultSet result =  getByIdStmt.executeQuery();

        Actor returnActor = null;

        while (result.next()) {
            returnActor =  new Actor();
            returnActor.setId(result.getInt(1));
            returnActor.setName(result.getString(2));
            returnActor.setSalary(result.getInt(3));
            returnActor.setMovie_id(result.getInt(4));
        }
        return returnActor;
    }

    public boolean insert(Actor actor) throws SQLException {
        if (actor == null) {
            System.out.println("Cannot insert a null actor!");
            return false;
        }

        insertStmt.setInt(1, actor.getId());
        insertStmt.setString(2, actor.getName());
        insertStmt.setInt(3, actor.getSalary());
        insertStmt.setInt(4, actor.getMovie_id());

        return insertStmt.execute();
    }

    public boolean deleteAll() throws SQLException {
        return deleteAllStmt.execute();
    }
}
