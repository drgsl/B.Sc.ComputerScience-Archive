package database.connections;

import java.sql.*;

public class MyDatabaseConn {
    private static MyDatabaseConn instance = null;
    private static Connection connection;
    private MyDatabaseConn() throws SQLException {
            // System.out.println("Connecting to database...");
            connection = DriverManager.getConnection("jdbc:oracle:thin:@DESKTOP-ADRIAN:1521:XE", "STUDENT", "STUDENT");
            // System.out.println("Connected!");
    }

    public static MyDatabaseConn getInstance() throws SQLException {
        if (instance == null) {
            instance = new MyDatabaseConn();
        }
        return instance;
    }

    public Connection getConnection() {
        return connection;
    }
}
