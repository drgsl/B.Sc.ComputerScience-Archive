package entities;

import javax.persistence.*;

@Entity
@NamedQueries({
        @NamedQuery(name = "CitiesEntity.findByStateId", query = "select s from CitiesEntity s where s.stateId = :stateId"),
        @NamedQuery(name = "CitiesEntity.findByName", query = "select s from CitiesEntity s where s.name like concat('%',:name,'%')"),
        @NamedQuery(name = "CitiesEntity.verify", query = "SELECT count(e.id) from CitiesEntity e where e.name=?1"),
        @NamedQuery(name = "CitiesEntity.findAll", query = "SELECT p FROM CitiesEntity p")
})


@Table(name = "cities", schema = "public", catalog = "ProiectPA")
public class CitiesEntity {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Basic
    @Column(name = "id")
    private int id;
    @Basic
    @Column(name = "state_id")
    private Integer stateId;
    @Basic
    @Column(name = "name")
    private String name;

    public int getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Integer getStateId() {
        return stateId;
    }

    public void setStateId(Integer stateId) {
        this.stateId = stateId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        CitiesEntity that = (CitiesEntity) o;

        if (id != that.id) return false;
        if (stateId != null ? !stateId.equals(that.stateId) : that.stateId != null) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = id;
        result = 31 * result + (stateId != null ? stateId.hashCode() : 0);
        result = 31 * result + (name != null ? name.hashCode() : 0);
        return result;
    }
}
