package compulsory.repositories;

import compulsory.items.Continent;
import compulsory.management.GlobalManagement;
import homework.repositories.AbstractRepositoryJPA;

import javax.persistence.EntityManager;

public class ContinentRepositoryJPA extends AbstractRepositoryJPA {
    private EntityManager em;

    public ContinentRepositoryJPA() {
        this.em = GlobalManagement.getEntityManagerFactory().createEntityManager();
        setType("Continent");
    }

    public ContinentRepositoryJPA(EntityManager entityManager) {
    }

    public Continent findByName(String name){
        return (Continent) em.createNamedQuery("Continent.findByName").setParameter("name", name).getSingleResult();
    }
}
