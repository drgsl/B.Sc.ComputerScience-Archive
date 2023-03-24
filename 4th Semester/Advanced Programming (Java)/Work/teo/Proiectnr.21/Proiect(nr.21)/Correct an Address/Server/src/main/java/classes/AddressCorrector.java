package classes;

import data.CitiesEntity;
import data.CountriesEntity;
import data.StatesEntity;

import javax.persistence.*;
import java.util.List;

public class AddressCorrector {
    private String city;
    private String state;
    private String country;
    EntityManager entityManager;
    private int stateId;
    private int countryId;

    public AddressCorrector(String country, String state, String city) {
        this.country = country;
        this.state = state;
        this.city = city;
        EntityManagerFactory entityManagerFactory = Persistence.createEntityManagerFactory("default");
        this.entityManager = entityManagerFactory.createEntityManager();
        this.countryId = 0;
        this.stateId = 0;
    }

    public boolean verifyCity() {
        TypedQuery<CitiesEntity> query = this.entityManager.createNamedQuery("CitiesEntity.findByStateId", CitiesEntity.class).setParameter("stateId", this.stateId);
        List<CitiesEntity> results = query.getResultList();
        for (CitiesEntity inst : results) {
            if (this.city.equals(inst.getName())) {
                return true;
            }
        }
        return false;
    }

    public void setCityName() {
        TypedQuery<CitiesEntity> query = this.entityManager.createNamedQuery("CitiesEntity.findByStateId", CitiesEntity.class).setParameter("stateId", this.stateId);
        List<CitiesEntity> results = query.getResultList();
        this.city = results.get(0).getName();
    }

    public boolean verifyCityByName() {
        TypedQuery<CitiesEntity> query = this.entityManager.createNamedQuery("CitiesEntity.findByName", CitiesEntity.class).setParameter("name", this.city);
        List<CitiesEntity> results = query.getResultList();
        for (CitiesEntity inst : results) {
            if (inst.getName().contains(this.city)) {
                this.city = inst.getName();
                this.stateId = inst.getStateId();
                return true;
            }
        }
        return false;
    }

    public boolean verifyState() {
        TypedQuery<StatesEntity> query = this.entityManager.createNamedQuery("StatesEntity.findByCountryId", StatesEntity.class).setParameter("countryId", this.countryId).setParameter("stateName", this.state);
        List<StatesEntity> results = query.getResultList();
        for (StatesEntity inst : results) {

            if (inst.getStateName().contains(this.state)) {
                this.state = inst.getStateName();
                this.stateId = inst.getStateId();
                this.countryId = inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public boolean verifyStateByName() {
        TypedQuery<StatesEntity> query = this.entityManager.createNamedQuery("StatesEntity.findByName", StatesEntity.class).setParameter("stateName", this.state);
        List<StatesEntity> results = query.getResultList();
        for (StatesEntity inst : results) {
            if (inst.getStateName().contains(this.state)) {
                this.state = inst.getStateName();
                this.stateId = inst.getStateId();
                this.countryId = inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public void setStateName() {
        TypedQuery<StatesEntity> query = this.entityManager.createNamedQuery("StatesEntity.findById", StatesEntity.class).setParameter("stateId", this.stateId);
        List<StatesEntity> results = query.getResultList();
        this.state = results.get(0).getStateName();
        this.countryId = results.get(0).getCountryId();
    }

    public boolean verifyCountry() {
        TypedQuery<CountriesEntity> query = this.entityManager.createNamedQuery("CountriesEntity.findByCountryName", CountriesEntity.class).setParameter("countryName", country);
        List<CountriesEntity> results = query.getResultList();
        for (CountriesEntity inst : results) {
            if (inst.getCountryName().contains(this.country)) {
                this.country = inst.getCountryName();
                this.countryId = inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public void setCountryName() {
        TypedQuery<CountriesEntity> query = this.entityManager.createNamedQuery("CountriesEntity.findById", CountriesEntity.class).setParameter("countryId", this.countryId);
        List<CountriesEntity> results = query.getResultList();
        this.country = results.get(0).getCountryName();
    }


    public String getCity() {
        return city;
    }

    public String getState() {
        return state;
    }

    public String getCountry() {
        return country;
    }

    @Override
    public String toString() {
        return "AddressCorrector{" + "city='" + city + '\'' + ", state='" + state + '\'' + ", country='" + country + '\'' + ", stateId=" + stateId + ", countryId=" + countryId + '}';
    }
}
