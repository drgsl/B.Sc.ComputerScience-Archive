package smartCity.repository;

import smartCity.model.Parcare;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.query.Param;

public interface ParcareRepository extends JpaRepository<Parcare, Integer> {
    Parcare findParcareById(@Param("id")Integer id);
    Parcare findParcareByStrada(@Param("strada")String strada);
    Parcare findParcareByLatitudine(@Param("latitudine") Double latitudine);
    Parcare findParcareByLongitudine(@Param("longitudine") Double longitudine);
}
