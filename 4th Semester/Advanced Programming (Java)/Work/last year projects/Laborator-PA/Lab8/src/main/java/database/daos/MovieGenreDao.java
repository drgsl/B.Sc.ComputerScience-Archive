package database.daos;

import database.connections.MyDatabaseConn;
import database.entities.Actor;
import database.entities.MovieGenre;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MovieGenreDao {
    private final PreparedStatement getByIdStmt;
    private final PreparedStatement insertStmt;
    private final PreparedStatement deleteAllStmt;


    public MovieGenreDao() throws SQLException {
        Connection connection = MyDatabaseConn.getInstance().getConnection();
        getByIdStmt = connection.prepareStatement("select * from movies_genres where id = ?");
        insertStmt = connection.prepareStatement("insert into movies_genres values (?, ?)");
        deleteAllStmt = connection.prepareStatement("delete from movies_genres");
    }

    public MovieGenre getById(int id) throws SQLException {
        if (id < 1) {
            System.out.println("Invalid ID (must be over 0!)");
            return null;
        }

        getByIdStmt.setInt(1, id);
        ResultSet result =  getByIdStmt.executeQuery();

        MovieGenre returnMovieGenre = null;

        while (result.next()) {
            returnMovieGenre =  new MovieGenre();
            returnMovieGenre.setMovie_id(result.getInt(1));
            returnMovieGenre.setGenre_id(result.getInt(2));
        }
        return returnMovieGenre;
    }

    public boolean insert(MovieGenre movieGenre) throws SQLException {
        if (movieGenre == null) {
            System.out.println("Cannot insert a null movie genre!");
            return false;
        }

        insertStmt.setInt(1, movieGenre.getMovie_id());
        insertStmt.setInt(2, movieGenre.getGenre_id());

        return insertStmt.execute();
    }

    public boolean deleteAll() throws SQLException {
        return deleteAllStmt.execute();
    }

}
