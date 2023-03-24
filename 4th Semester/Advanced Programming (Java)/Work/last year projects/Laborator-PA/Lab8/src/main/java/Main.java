import database.DatabaseManager;
import database.connections.MyDatabaseConn;
import database.daos.MovieDao;
import database.entities.Movie;

import java.sql.Date;
import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
        DatabaseManager databaseManager = new DatabaseManager();

        databaseManager.testImplementation();
    }
}
