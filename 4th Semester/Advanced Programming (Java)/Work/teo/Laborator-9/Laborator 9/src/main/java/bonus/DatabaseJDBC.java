package bonus;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseJDBC {
    // static variable single_instance of type Singleton
    private static DatabaseJDBC single_instance = null;

    String url;
    Connection con;

    // private constructor restricted to this class itself
    private DatabaseJDBC(String url, String user, String password) throws SQLException {
        this.url = url;
        con = null;
        try {
            con = DriverManager.getConnection(url, user, password);
            System.out.println("Successfully connected to the database");
        } catch(SQLException e) {
            System.err.println("Cannot connect to DB: " + e);
        }
    }

    // static method to create instance of Singleton class
    public static DatabaseJDBC getInstance(String url, String user, String password) throws SQLException {
        if (single_instance == null)
            single_instance = new DatabaseJDBC(url, user, password);
        return single_instance;
    }

    public Connection getConnection(){
        return this.con;
    }
    public void close() throws SQLException {
        if (con != null) con.close();
    }
}
