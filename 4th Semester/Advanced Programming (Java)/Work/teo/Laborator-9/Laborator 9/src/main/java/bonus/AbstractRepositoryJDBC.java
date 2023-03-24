package bonus;

import java.sql.SQLException;

public abstract class AbstractRepositoryJDBC<T> implements AbstractRepository{
    public abstract T findById(int id) throws SQLException;
}
