package compulsory;

import compulsory.items.Continent;
import compulsory.management.GlobalManagement;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;

public class Main {
    public static void main(String[] args) {

        EntityManagerFactory emf = GlobalManagement.getEntityManagerFactory();

        EntityManager em = emf.createEntityManager();

        em.getTransaction().begin();
        //Continent continent = new Continent("Europe");
        //em.persist(continent);

        //Continent c = (Continent) em.createQuery("select e from Continent e where e.name = 'Europe'").getSingleResult();

        //c.setName("Africa");

        //em.getTransaction().commit();

        em.close();
        GlobalManagement.closeEntityManagerFactory();
    }
}

