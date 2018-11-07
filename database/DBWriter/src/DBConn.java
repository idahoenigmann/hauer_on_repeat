import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;
import java.sql.Date;
import java.sql.Blob;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import java.time.LocalDate;
import javafx.stage.Stage;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.lang.StringBuilder;


class DBConn {
    DBConn() {
        try {
            Class.forName("org.sqlite.JDBC");
            connection = DriverManager.getConnection("jdbc:sqlite:" + pathToDB);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    DBConn(String path) {
        try {
            Class.forName("org.sqlite.JDBC");
            connection = DriverManager.getConnection("jdbc:sqlite:" + path);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    boolean addEntry(String value) {
        String sql = new String("insert into saves (inputDate, input) values (datetime(), ?)");

        try {
            statement = connection.prepareStatement(sql);
            statement.setQueryTimeout(5);
            statement.setString(1, value);
            statement.executeUpdate();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    private String pathToDB = new String("../database.db");
    private Connection connection;
    private PreparedStatement statement;
}
