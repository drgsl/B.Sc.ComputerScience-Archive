package connectionDB;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

/**
 * global management for EntityManagerFactory
 */
public class Database {
    private static EntityManagerFactory emf = null;

    /**
     * creating the EntityManagerFactory
     *
     */
    public static void initializeEntityManagerFactory() {
       Database.emf = Persistence.createEntityManagerFactory("appPU");
    }

    /**
     * retunrning a reference for an EntityManagerFactory already created
     *
     * @return reference
     */
    public static EntityManagerFactory getEntityManagerFactory() {
        return Database.emf;
    }

    /**
     * this method closes the connection for the running EntityManagerFactory
     */
    public static void closeEntityManagerFactory() {
        Database.emf.close();
    }
}
