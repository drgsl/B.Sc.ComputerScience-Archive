package homework;

import ch.qos.logback.classic.turbo.TurboFilter;
import compulsory.items.City;
import compulsory.repositories.CityRepositoryJPA;
import homework.insertionDB.CitiesInsertion;
import homework.insertionDB.ContinentsInsertion;
import homework.insertionDB.CountriesInsertion;
import homework.insertionDB.SistersInsertion;

public class Main {
    public static void insertIntoDB(){
        ContinentsInsertion continentsInsertion = new ContinentsInsertion();
        continentsInsertion.insertContinents();

        CountriesInsertion countriesInsertion = new CountriesInsertion();
        countriesInsertion.insertCountries();

        CitiesInsertion citiesInsertion = new CitiesInsertion();
        citiesInsertion.insertCities();

        SistersInsertion sistersInsertion = new SistersInsertion();
        sistersInsertion.insertSisterRelationship();

    }

    public static void main(String[] args){
        //insertIntoDB();
        City city = new City();
        city.setName("Iasi");
        CityRepositoryJPA c = new CityRepositoryJPA();
        City citty = (City) c.findById(1);
        System.out.println(city.getName());

    }
}
