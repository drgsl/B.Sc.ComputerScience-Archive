package homework.repositories;

import bonus.AbstractRepository;
import bonus.model.City;
import compulsory.management.GlobalManagement;
import lombok.Data;

import javax.persistence.EntityManager;
import java.util.List;

@Data
public abstract class AbstractRepositoryJPA<T> implements AbstractRepository {

    private EntityManager em;
    private String type;

    public AbstractRepositoryJPA() {
        this.em = GlobalManagement.getEntityManagerFactory().createEntityManager();
    }

    public void create(T item){
        em.persist(item);
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

    public T findById(long id){
        StringBuilder sb = new StringBuilder();
        sb.append(type);
        sb.append(".findById");
         //    return (T) em.createNamedQuery(sb.toString()).setParameter("id", id).getSingleResult();
         return null;
    }

    /*
    public List<T> findByMatchingPattern(String pattern){
        StringBuilder sb = new StringBuilder();
        sb.append(type);
        sb.append(".findByNamePattern");
        return em.createNamedQuery(sb.toString()).setParameter("pattern", pattern).getResultList();
    }
     */
}
