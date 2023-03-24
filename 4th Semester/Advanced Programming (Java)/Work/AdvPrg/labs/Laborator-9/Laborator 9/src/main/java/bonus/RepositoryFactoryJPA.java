package bonus;

import compulsory.repositories.CityRepositoryJPA;
import compulsory.repositories.ContinentRepositoryJPA;
import compulsory.repositories.CountryRepositoryJPA;

public class RepositoryFactoryJPA extends AbstractFactory{
    @Override
    public AbstractRepository getCityRepository() {
        return new CityRepositoryJPA();
    }

    @Override
    public AbstractRepository getCountryRepository() {
        return new CountryRepositoryJPA();
    }

    @Override
    public AbstractRepository getContinentRepository() {
        return new ContinentRepositoryJPA();
    }
}
