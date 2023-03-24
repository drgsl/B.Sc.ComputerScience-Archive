package homework.insertionDB;

import compulsory.items.City;
import compulsory.items.Country;
import compulsory.repositories.CityRepositoryJPA;
import compulsory.repositories.CountryRepositoryJPA;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;

public class CitiesInsertion {

    public void insertCities(){
        try{
            File file = new File("src/main/resources/concap.csv");
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            String[] columns;
            CountryRepositoryJPA countryRepository = new CountryRepositoryJPA();
            CityRepositoryJPA cityRepository = new CityRepositoryJPA();
            cityRepository.beginTransaction();
            Random random = new Random();
            while ((line = br.readLine()) != null) {
                columns = line.split(",");
                String countryName = columns[0].replaceAll("'", " ");
                Country country = countryRepository.findByName(countryName);
                String name = columns[1].replaceAll("'", " ");
                City city = new City(name, country);
                city.setPopulation(random.nextInt(18000000));
                cityRepository.create(city);
            }
            cityRepository.commitTransaction();
            cityRepository.closeTransaction();
            fr.close();
        }
        catch (IOException e){
            System.out.println("Exception when handling the file!");
        }
    }

    public void insertCitiesOfCountry(Country country) {
        File file = new File("src/main/resources/citiesUS.txt");
        try {
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            CityRepositoryJPA cityRepository = new CityRepositoryJPA();
            cityRepository.beginTransaction();
            while ((line = br.readLine()) != null) {
                City city = new City(line, country);
                cityRepository.create(city);
            }
            cityRepository.commitTransaction();
            cityRepository.closeTransaction();

        } catch (IOException e) {
            System.out.println("Exception here!");
        }
    }

}
