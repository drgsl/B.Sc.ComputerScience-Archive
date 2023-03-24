package smartCity.repository;

import smartCity.model.Loc;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.repository.query.Param;
import java.util.List;

public interface LocRepository extends JpaRepository<Loc, Integer>{
    Loc findLocById(@Param("id") Integer id);
    List<Loc> findLocByIdParcare(@Param("id_parcare")Integer id_parcare);
    List<Loc> findLocByIdParcareAndDisponibil(@Param("id_parcare")Integer id_parcare, @Param("disponibil")Boolean disponibil);
    Loc findByIdParcareAndIdLoc(@Param("id_parcare")Integer id_parcare, @Param("id_loc")Integer id_loc);
}
