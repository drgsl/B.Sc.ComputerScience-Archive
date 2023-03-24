package laboratorpa.lab11.repositories;

import laboratorpa.lab11.entities.PersonEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;

public interface PersonRepository extends JpaRepository<PersonEntity, Integer> {

    @Modifying
    @Query("UPDATE PersonEntity p SET p.name = ?2 where p.id = ?1")
    void update(Integer id, String name);
}
