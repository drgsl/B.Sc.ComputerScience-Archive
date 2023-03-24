import lombok.Data;

import java.sql.*;

@Data
public class CountryDAO {
    public void create(String name, int id) throws SQLException {
        Connection con = Database.getConnection();
        try (PreparedStatement pstmt = con.prepareStatement(
                "insert into countries (name, continent_id) values (?, ?)")) {
            pstmt.setString(1, name);
            pstmt.setInt(2, id);
            pstmt.executeUpdate();
        }
    }
    public Integer findByName(String name) throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select id from countries where name='" + name + "'")) {
            return rs.next() ? rs.getInt(1) : null;
        }
    }
    public String findById(int id) throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select name from countries where id='" + id + "'")) {
            return rs.next() ? rs.getString(1) : null;
        }
    }
    public String findByContinent(String continentName) throws SQLException {
        Connection con = Database.getConnection();
        try (Statement stmt = con.createStatement();
             ResultSet rs = stmt.executeQuery(
                     "select cou.name from countries cou join continents con on cou.continent_id=con.id " +
                             "where con.name='" + continentName + "'")) {
            StringBuilder str = new StringBuilder();
            while(rs.next()) {
                str.append(rs.getString(1));
                str.append(" ");
            }
            return str.toString();
        }
    }



}
