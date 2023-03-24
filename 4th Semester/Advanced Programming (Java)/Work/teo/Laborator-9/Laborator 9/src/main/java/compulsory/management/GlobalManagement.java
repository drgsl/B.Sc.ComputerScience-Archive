package compulsory.management;

import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

/**
 * global management for EntityManagerFactory
 */
public class GlobalManagement {
    private static EntityManagerFactory emf = null;
    private static GlobalManagement gm = null;

    private GlobalManagement(){
        GlobalManagement.emf = Persistence.createEntityManagerFactory("appPU");
    }

    /**
     * creating the EntityManagerFactory
     *
     */
    public static void initializeEntityManagerFactory() {
        GlobalManagement.emf = Persistence.createEntityManagerFactory("appPU");
    }

    /**
     * retunrning a reference for an EntityManagerFactory already created
     *
     * @return reference
     */
    public static EntityManagerFactory getEntityManagerFactory() {
        if(gm == null)
            gm = new GlobalManagement();
        return GlobalManagement.emf;
    }

    /**
     * this method closes the connection for the running EntityManagerFactory
     */
    public static void closeEntityManagerFactory() {
        GlobalManagement.emf.close();
    }
}
