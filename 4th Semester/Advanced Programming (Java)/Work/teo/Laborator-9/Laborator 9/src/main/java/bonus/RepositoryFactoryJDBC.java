package bonus;

import bonus.daos.CityRepositoryJDBC;
import bonus.daos.ContinentRepositoryJDBC;
import bonus.daos.CountryRepositoryJDBC;

public class RepositoryFactoryJDBC extends AbstractFactory{
    @Override
    public AbstractRepository getCityRepository() {
        return new CityRepositoryJDBC();
    }

    @Override
    public AbstractRepository getCountryRepository() {
        return new CountryRepositoryJDBC();
    }

    @Override
    public AbstractRepository getContinentRepository() {
        return new ContinentRepositoryJDBC();
    }
}
