package data;

import javax.persistence.*;

@Entity
@Table(name = "countries", schema = "public", catalog = "d4kt7idb1gv9b8")
@NamedQueries({
        @NamedQuery(name = "CountriesEntity.findById", query = "select s from CountriesEntity s where s.countryId=:countryId"),
        @NamedQuery(name = "CountriesEntity.findByCountryName", query = "select c from CountriesEntity c where c.countryName like concat('%',:countryName,'%')")
})
public class CountriesEntity {
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Id
    @Basic
    @Column(name = "country_id")
    private int countryId;
    @Basic
    @Column(name = "country_code")
    private String countryCode;
    @Basic
    @Column(name = "country_name")
    private String countryName;

    public int getCountryId() {
        return countryId;
    }

    public void setCountryId(Integer countryId) {
        this.countryId = countryId;
    }

    public void setCountryId(int countryId) {
        this.countryId = countryId;
    }

    public String getCountryCode() {
        return countryCode;
    }

    public void setCountryCode(String countryCode) {
        this.countryCode = countryCode;
    }

    public String getCountryName() {
        return countryName;
    }

    public void setCountryName(String countryName) {
        this.countryName = countryName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        CountriesEntity that = (CountriesEntity) o;

        if (countryId != that.countryId) return false;
        if (countryCode != null ? !countryCode.equals(that.countryCode) : that.countryCode != null) return false;
        if (countryName != null ? !countryName.equals(that.countryName) : that.countryName != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = countryId;
        result = 31 * result + (countryCode != null ? countryCode.hashCode() : 0);
        result = 31 * result + (countryName != null ? countryName.hashCode() : 0);
        return result;
    }
}
