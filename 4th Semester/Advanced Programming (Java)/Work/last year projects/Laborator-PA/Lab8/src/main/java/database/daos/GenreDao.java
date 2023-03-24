package database.daos;

import database.connections.MyDatabaseConn;
import database.entities.Genre;

import java.sql.*;

public class GenreDao {

    private final PreparedStatement getByIdStmt;
    private final PreparedStatement insertStmt;
    private final PreparedStatement deleteAllStmt;

    public GenreDao() throws SQLException {
        Connection connection = MyDatabaseConn.getInstance().getConnection();
        getByIdStmt = connection.prepareStatement("select * from genres where id = ?");
        insertStmt = connection.prepareStatement("insert into genres values (?, ?)");
        deleteAllStmt = connection.prepareStatement("delete from genres");
    }

    public Genre getById(int id) throws SQLException {
        getByIdStmt.setInt(1, id);

        ResultSet result = getByIdStmt.executeQuery();

        Genre returnGenre = null;
        while (result.next()) {
            returnGenre = new Genre();
            returnGenre.setId(result.getInt(1));
            returnGenre.setName(result.getString(2));
        }
        return returnGenre;
    }

    public boolean insert(Genre genre) throws SQLException {
        if (genre == null) {
            System.out.println("Cannot insert a null genre!");
            return false;
        }

        insertStmt.setInt(1, genre.getId());
        insertStmt.setString(2, genre.getName());

        return insertStmt.execute();
    }

    public boolean deleteAll() throws SQLException {
        return deleteAllStmt.execute();
    }
}
