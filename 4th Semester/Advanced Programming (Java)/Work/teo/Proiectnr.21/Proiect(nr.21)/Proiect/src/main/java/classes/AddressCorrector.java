package classes;

import entities.CitiesEntity;
import entities.CountriesEntity;
import entities.StatesEntity;

import javax.persistence.EntityManager;
import javax.persistence.TypedQuery;
import java.util.List;

public class AddressCorrector {
    private String city;
    private String state;
    private String country;
    EntityManager entityManager;
    private int stateId;
    private int countryId;

    public AddressCorrector(String city, String state, String country, EntityManager entityManager) {
        this.city = city;
        this.state = state;
        this.country = country;
        this.entityManager=entityManager;
        this.countryId = 0;
        this.stateId = 0;
    }

    public boolean verifyCity()
    {
        TypedQuery<CitiesEntity> query = this.entityManager.createNamedQuery("CitiesEntity.findByStateId", CitiesEntity.class).setParameter("stateId",this.stateId);
        List<CitiesEntity> results = query.getResultList();
        for(CitiesEntity inst : results){
            if(this.city.equals(inst.getName()))
            {
                this.city = inst.getName();
                return true;
            }
        }
        return false;
    }

    public boolean verifyCityByName()
    {
        TypedQuery<CitiesEntity> query = this.entityManager.createNamedQuery("CitiesEntity.findByName", CitiesEntity.class).setParameter("name",this.city);
        List<CitiesEntity> results = query.getResultList();
        for(CitiesEntity inst : results){
            if(inst.getName().contains(this.city))
            {
                this.city = inst.getName();
                this.stateId= inst.getStateId();
                return true;
            }
        }
        return false;
    }

    public boolean verifyState()
    {
        TypedQuery<StatesEntity> query = this.entityManager
                .createNamedQuery("StatesEntity.findByCountryId", StatesEntity.class)
                .setParameter("countryId", this.countryId)
                .setParameter("stateName",this.state);
        List<StatesEntity> results = query.getResultList();
        for(StatesEntity inst : results){

            if(inst.getStateName().contains(this.state))
            {
                this.stateId = inst.getStateId();
                countryId=inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public boolean verifyStateByName()
    {
        TypedQuery<StatesEntity> query = this.entityManager.createNamedQuery("StatesEntity.findByName", StatesEntity.class).setParameter("stateName",this.state);
        List<StatesEntity> results = query.getResultList();
        for(StatesEntity inst : results){
            if(inst.getStateName().contains(this.city))
            {
                this.countryId = inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public void setStateName()
    {
        TypedQuery<StatesEntity> query = this.entityManager
                .createNamedQuery("StatesEntity.findById", StatesEntity.class)
                .setParameter("stateId", this.stateId);
        List<StatesEntity> results = query.getResultList();
        this.state = results.get(0).getStateName();
        this.countryId = results.get(0).getCountryId();
    }

    public boolean verifyCountry()
    {
        TypedQuery<CountriesEntity> query = this.entityManager.createNamedQuery("CountriesEntity.findByCountryName", CountriesEntity.class).setParameter("countryName", country);
        List<CountriesEntity> results = query.getResultList();
        for(CountriesEntity inst : results){
            if(inst.getCountryName().contains(this.country))
            {
                this.countryId = inst.getCountryId();
                return true;
            }
        }
        return false;
    }

    public void setCountryName() {
        TypedQuery<CountriesEntity> query = this.entityManager
                .createNamedQuery("CountriesEntity.findById", CountriesEntity.class)
                .setParameter("countryId", this.countryId);
        List<CountriesEntity> results = query.getResultList();
        this.country = results.get(0).getCountryName();
    }


    public String getCity() {
        return city;
    }

    public void setCity(String city) {
        this.city = city;
    }

    public String getState() {
        return state;
    }

    public void setState(String state) {
        this.state = state;
    }

    public String getCountry() {
        return country;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public int getStateId() {
        return stateId;
    }

    public int getCountryId() {
        return countryId;
    }
}
