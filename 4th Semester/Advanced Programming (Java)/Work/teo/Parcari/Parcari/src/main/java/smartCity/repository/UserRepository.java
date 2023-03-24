package smartCity.repository;

import smartCity.model.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.query.Param;

public interface UserRepository extends JpaRepository<User, Integer> {
    User findUserById(@Param("id") Integer id);
    User findUserByUsername(@Param("username") String username);
}
