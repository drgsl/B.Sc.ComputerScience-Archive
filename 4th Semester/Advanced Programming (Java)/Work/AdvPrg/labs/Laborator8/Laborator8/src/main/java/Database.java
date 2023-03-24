import java.sql.*;

public class Database{
    private static Database instance = null;
    private static Connection connection;

    private Database()  {
        //connection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:XE", "STUDENT", "STUDENT");
    }

    public static Database getInstance() throws SQLException {
        if (instance == null) {
            instance = new Database();
        }
        return instance;
    }

    public static Connection getConnection() {
        return connection;
    }

    public static void createConnection() throws SQLException{
        connection = DriverManager.getConnection("jdbc:postgresql://localhost:8081/postgres", "postgres", "STUDENT");
    }


}