package entities;

import javax.persistence.*;
import java.math.BigInteger;

@Entity
@Table(name = "states", schema = "public", catalog = "ProiectPA")
@NamedQueries({
        @NamedQuery(name = "StatesEntity.findById", query = "select s from StatesEntity s where s.stateId=:stateId"),
        @NamedQuery(name = "StatesEntity.findByCountryId", query = "select s from StatesEntity s where s.countryId = :countryId and s.stateName  like concat('%',:stateName,'%')") ,
        @NamedQuery(name = "StatesEntity.findByName", query = "select c from StatesEntity c where c.stateName like concat('%',:stateName,'%')")
})
public class StatesEntity {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Basic
    @Column(name = "state_id")
    private Integer stateId;
    @Basic
    @Column(name = "country_id")
    private Integer countryId;
    @Basic
    @Column(name = "state_code")
    private String stateCode;
    @Basic
    @Column(name = "state_name")
    private String stateName;

    public int getStateId() {
        return stateId;
    }

    public void setStateId(Integer stateId) {
        this.stateId = stateId;
    }

    public void setStateId(int stateId) {
        this.stateId = stateId;
    }

    public Integer getCountryId() {
        return countryId;
    }

    public void setCountryId(Integer countryId) {
        this.countryId = countryId;
    }

    public String getStateCode() {
        return stateCode;
    }

    public void setStateCode(String stateCode) {
        this.stateCode = stateCode;
    }

    public String getStateName() {
        return stateName;
    }

    public void setStateName(String stateName) {
        this.stateName = stateName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        StatesEntity that = (StatesEntity) o;

        if (stateId != that.stateId) return false;
        if (countryId != null ? !countryId.equals(that.countryId) : that.countryId != null) return false;
        if (stateCode != null ? !stateCode.equals(that.stateCode) : that.stateCode != null) return false;
        if (stateName != null ? !stateName.equals(that.stateName) : that.stateName != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = stateId;
        result = 31 * result + (countryId != null ? countryId.hashCode() : 0);
        result = 31 * result + (stateCode != null ? stateCode.hashCode() : 0);
        result = 31 * result + (stateName != null ? stateName.hashCode() : 0);
        return result;
    }
}
