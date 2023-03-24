package bonus;

public abstract class AbstractFactory {
    public abstract AbstractRepository getCityRepository();
    public abstract AbstractRepository getCountryRepository();
    public abstract AbstractRepository getContinentRepository();
}