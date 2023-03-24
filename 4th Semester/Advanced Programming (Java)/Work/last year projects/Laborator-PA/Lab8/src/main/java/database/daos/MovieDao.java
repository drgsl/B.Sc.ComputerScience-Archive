package database.daos;

import database.connections.MyDatabaseConn;
import database.entities.Movie;

import java.sql.*;

public class MovieDao {

    private final PreparedStatement getByIdStmt;
    private final PreparedStatement insertStmt;
    private final PreparedStatement deleteAllStmt;


    public MovieDao() throws SQLException {
        Connection connection = MyDatabaseConn.getInstance().getConnection();
        getByIdStmt = connection.prepareStatement("select * from movies where id = ?");
        insertStmt = connection.prepareStatement("insert into movies values (?, ?, ?, ?, ?)");
        deleteAllStmt = connection.prepareStatement("delete from movies");
    }

    public Movie getById(int id) throws SQLException {
        if (id < 1) {
            System.out.println("Invalid ID (must be over 0!)");
            return null;
        }

        getByIdStmt.setInt(1, id);
        ResultSet result =  getByIdStmt.executeQuery();

        Movie returnMovie = null;

        while (result.next()) {
            returnMovie =  new Movie();
            returnMovie.setId(result.getInt(1));
            returnMovie.setTitle(result.getString(2));
            returnMovie.setRelease_date(result.getDate(3));
            returnMovie.setDuration(result.getInt(4));
            returnMovie.setScore(result.getInt(5));
        }
        return returnMovie;
    }

    public boolean insert(Movie movie) throws SQLException {
        if (movie == null) {
            System.out.println("Cannot insert a null movie!");
            return false;
        }

        insertStmt.setInt(1, movie.getId());
        insertStmt.setString(2, movie.getTitle());
        insertStmt.setDate(3, movie.getRelease_date());
        insertStmt.setInt(4, movie.getDuration());
        insertStmt.setInt(5, movie.getScore());

        return insertStmt.execute();
    }

    public boolean deleteAll() throws SQLException {
        return deleteAllStmt.execute();
    }
}
