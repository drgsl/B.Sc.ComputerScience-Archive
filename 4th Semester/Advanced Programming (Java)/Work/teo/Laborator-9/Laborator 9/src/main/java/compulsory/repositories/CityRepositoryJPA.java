package compulsory.repositories;

import compulsory.items.City;
import compulsory.management.GlobalManagement;
import compulsory.items.Country;
import homework.repositories.AbstractRepositoryJPA;

import javax.persistence.EntityManager;
import java.util.List;

/**
 * City Repository
 */
public class CityRepositoryJPA extends AbstractRepositoryJPA {
    private EntityManager em;

    public CityRepositoryJPA() {
        setType("City");
        this.em = GlobalManagement.getEntityManagerFactory().createEntityManager();
    }

    public CityRepositoryJPA(EntityManager entityManager) {
    }

    /**
     * this method returns a list of cities based on a specified country
     *
     * @param country country specified
     * @return list of cities from that country
     */
    public List<City> findByCountry(Country country) {
        return em.createNamedQuery("City.findByCountry").setParameter("country", country).getResultList();
    }

    public List<City> findAllCities(){
        return em.createNamedQuery("City.findAll").getResultList();
    }

    public long getCount(){
        return (long) em.createNamedQuery("City.getCount").getSingleResult();
    }
}

