package compulsory.repositories;

import compulsory.items.Country;
import compulsory.items.Sister;
import compulsory.management.GlobalManagement;

import javax.persistence.EntityManager;

public class SisterRepository {

    private EntityManager em;

    public SisterRepository() {
        this.em = GlobalManagement.getEntityManagerFactory().createEntityManager();
    }

    public void create(Sister sister){
        em.persist(sister);
    }

    public void beginTransaction(){
        em.getTransaction().begin();
    }

    public void commitTransaction(){
        em.getTransaction().commit();
    }

    public void closeTransaction(){
        em.close();
    }
}
