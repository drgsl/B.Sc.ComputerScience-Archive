import database.connections.MyDatabaseConn;
import database.daos.MovieDao;
import database.entities.Movie;
import org.junit.Test;
import org.junit.jupiter.api.Assertions;

import java.sql.Date;
import java.sql.SQLException;

class MovieTest {

    @Test
    public void createAndTest() {
        try
        {
            Movie movie1 = new Movie(10, "Return of the Jedi", new Date(1020313L), 183, 9);
            Movie movie2 = new Movie(11, "Rise of the Empire", new Date(1020313L), 154, 7);

            MovieDao movieDao = new MovieDao();

            movieDao.deleteAll();
            movieDao.insert(movie1);
            movieDao.insert(movie2);

            Movie movie1received = movieDao.getById(10);

            Assertions.assertEquals(movie1, movie1received);
        }
        catch (SQLException throwable) {
            throwable.printStackTrace();
        }

    }
}