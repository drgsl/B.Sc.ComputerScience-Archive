package bonus;

import bonus.daos.CityRepositoryJDBC;
import bonus.daos.ContinentRepositoryJDBC;
import bonus.daos.CountryRepositoryJDBC;
import compulsory.repositories.CityRepositoryJPA;
import compulsory.repositories.ContinentRepositoryJPA;
import compulsory.repositories.CountryRepositoryJPA;
import lombok.NoArgsConstructor;

import javax.persistence.EntityManager;

@NoArgsConstructor
public class RepoFactory extends AbstractFactory {

    DatabaseJDBC singletonJDBC;
    EntityManager entityManager;

    public RepoFactory(DatabaseJDBC singletonJDBC) {
        this.singletonJDBC = singletonJDBC;
    }

    public RepoFactory(EntityManager entityManager) {
        this.entityManager = entityManager;
    }

    public RepoFactory(DatabaseJDBC singletonJDBC, EntityManager entityManager) {
        this.singletonJDBC = singletonJDBC;
        this.entityManager = entityManager;
    }
    public AbstractRepository getRepository(String type, String repoType)
    {
        AbstractRepository repository = null;
        switch (repoType) {
            case "JDBC":
                switch (type) {
                    case "City":
                        repository = new CityRepositoryJDBC(singletonJDBC);
                        break;
                    case "Country":
                        repository = new CountryRepositoryJDBC(singletonJDBC);
                        break;
                    case "Continent":
                        repository = new ContinentRepositoryJDBC(singletonJDBC);
                        break;
                    default:
                        System.out.println("ERROR: NO KNOWN TYPE");
                        break;
                }
                break;
            case "JPA":
                switch (type) {
                    case "City":
                        repository = new CityRepositoryJPA(entityManager);
                        break;
                    case "Country":
                        repository = new CountryRepositoryJPA(entityManager);
                        break;
                    case "Continent":
                        repository = new ContinentRepositoryJPA(entityManager);
                        break;
                    default:
                        System.out.println("ERROR: NO KNOWN TYPE");
                        break;
                }
                break;
            default:
                System.out.println("ERROR NO KNOWN REPOSITORY TYPE");
                break;
        }
        return repository;
    }

    @Override
    public AbstractRepository getCityRepository() {
        return null;
    }

    @Override
    public AbstractRepository getCountryRepository() {
        return null;
    }

    @Override
    public AbstractRepository getContinentRepository() {
        return null;
    }
}

