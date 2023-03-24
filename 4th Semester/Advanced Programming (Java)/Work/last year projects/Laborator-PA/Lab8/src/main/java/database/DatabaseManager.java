package database;

import database.connections.MyDatabaseConn;
import database.daos.*;
import database.entities.*;

import java.sql.Date;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;

public class DatabaseManager {

    private MovieDao movieDao;
    private GenreDao genreDao;
    private ActorDao actorDao;
    private DirectorDao directorDao;
    private MovieGenreDao movieGenreDao;

    public DatabaseManager() {
        try {
            movieDao = new MovieDao();
            genreDao = new GenreDao();
            actorDao = new ActorDao();
            directorDao = new DirectorDao();
            movieGenreDao = new MovieGenreDao();
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    /**
     * Simple method that makes simple, predefined queries to the database.
     */
    public void testImplementation() {
        try {
            Scanner scanner = new Scanner(System.in);

            System.out.println("Let's add some info to the database!");

            // Setting up the movie

            Movie movie = new Movie();
            System.out.println("Let's start by adding a movie...");

            movie.setId(getMaxId("movies"));

            System.out.print("Movie's title: ");
            movie.setTitle(scanner.nextLine());

            System.out.print("Movie's release date (format: '123L'): ");
            movie.setRelease_date(new Date(scanner.nextLong()));

            System.out.print("Movie's duration (in minutes): ");
            movie.setDuration(scanner.nextInt());

            System.out.print("Movie's score (from 1 to 10): ");
            movie.setScore(scanner.nextInt());

            addMovie(movie);

            // Setting up the genre
            System.out.println("Great! Now let's add its genre: ");

            Genre genre = new Genre();
            genre.setId(getMaxId("genres"));
            genre.setName(scanner.next());

            addGenre(genre);

            // Setting up the movie-genre relation
            movieGenreDao.insert(new MovieGenre(movie.getId(), genre.getId()));

            // Setting up the actors
            System.out.println("Hurray! Only the actors and the director to go. So, how many actors does this movie have?");
            int actorsCount = scanner.nextInt();
            int actorsId = getMaxId("actors");

            for (int i = 1; i <= actorsCount; i++) {
                System.out.println("----- Actor " + i);
                Actor actor = new Actor();
                actor.setId(actorsId);

                System.out.print("Name: ");
                actor.setName(scanner.nextLine());

                System.out.print("Salary: ");
                actor.setSalary(scanner.nextInt());

                actor.setMovie_id(movie.getId());

                addActor(actor);
                actorsCount++;
            }

            // Setting up the director
            Director director = new Director();

            director.setId(getMaxId("directors"));

            System.out.println("Ok, and now the director!");
            System.out.print("Name: ");
            director.setName(scanner.nextLine());

            System.out.print("Salary: ");
            director.setSalary(scanner.nextInt());

            director.setMovie_id(movie.getId());

            addDirector(director);

            System.out.println("Awesome! All the information is now in the database. Thanks!");
        } catch (SQLException throwables) {
            throwables.printStackTrace();
        }
    }

    private int getMaxId(String table) throws SQLException {
        PreparedStatement stmt = MyDatabaseConn.getInstance().getConnection().prepareStatement("select nvl(max(id), 0) + 1 from " + table);
        ResultSet set = stmt.executeQuery();
        set.next();
        return set.getInt(1);
    }

    /**
     * Compulsory method for testing simple queries to the database.
     */
    public void compulsory() {
        try {

            Movie movie1 = new Movie(10, "Return of the Jedi", new Date(102L), 183, 9);
            Movie movie2 = new Movie(11, "Rise of the Empire", new Date(2151231L), 154, 7);

            System.out.println("First, we create a connection to the database.");
            MovieDao movieDao = new MovieDao();

            System.out.println("Then, we delete all entities in the 'movies' table.");
            movieDao.deleteAll();

            System.out.println("After deletion, we insert two movies:");
            System.out.println("Movie 1: " + movie1);
            System.out.println("Movie 2: " + movie2);
            movieDao.insert(movie1);
            movieDao.insert(movie2);

            System.out.println("We then make a query which gets both of them by their ID and compares the results.");
            Movie movie1received = movieDao.getById(10);
            Movie movie2received = movieDao.getById(11);

            if (movie1.equals(movie1received)) {
                System.out.println("Same movie!");
            }
            else {
                System.out.println("Not the same movie!");
            }

            if (movie1.equals(movie2received)) {
                System.out.println("Same movie!");
            }
            else {
                System.out.println("Not the same movie!");
            }
        } catch (SQLException throwable) {
            throwable.printStackTrace();
        }
    }

    public void addMovie(Movie movie) throws SQLException {
        movieDao.insert(movie);
    }

    public Movie getMovieById(int id) throws SQLException {
        return movieDao.getById(id);
    }

    public void deleteAllMovies() throws SQLException {
        movieDao.deleteAll();
    }

    public void addGenre(Genre genre) throws SQLException {
        genreDao.insert(genre);
    }

    public Genre getGenreById(int id) throws SQLException {
        return genreDao.getById(id);
    }

    public void deleteAllGenres() throws SQLException {
        genreDao.deleteAll();
    }

    public void addActor(Actor actor) throws SQLException {
        actorDao.insert(actor);
    }

    public Person getActorById(int id) throws SQLException {
        return actorDao.getById(id);
    }

    public void deleteAllActors() throws SQLException {
        actorDao.deleteAll();
    }

    public void addDirector(Director director) throws SQLException {
        directorDao.insert(director);
    }

    public Person getDirectorById(int id) throws SQLException {
        return directorDao.getById(id);
    }

    public void deleteAllDirectors() throws SQLException {
        directorDao.deleteAll();
    }

}
