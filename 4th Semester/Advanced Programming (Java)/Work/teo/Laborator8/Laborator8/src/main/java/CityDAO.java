import java.sql.*;

public class CityDAO {

    public void create(int country, String name, int capital, float latitude, float longitude) throws SQLException {
        Connection con = Database.getConnection();
        try (PreparedStatement pstmt = con.prepareStatement(
                "insert into cities (country_id, name, capital, latitude, longitude) values (?, ?, ?, ?, ?)")) {
            pstmt.setInt(1, country);
            pstmt.setString(2, name);
            pstmt.setInt(3, capital);
            pstmt.setFloat(4, latitude);
            pstmt.setFloat(5, longitude);
            pstmt.executeUpdate();
        }
    }
    public Integer findByName(String name) throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select id from continents where name='" + name + "'")) {
            return rs.next() ? rs.getInt(1) : null;
        }
    }
    public String findById(int id) throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select name from continents where id='" + id + "'")) {
            return rs.next() ? rs.getString(1) : null;
        }
    }

}
