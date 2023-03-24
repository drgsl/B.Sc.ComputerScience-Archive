package homework.insertionDB;

import compulsory.items.Continent;
import compulsory.items.Country;
import compulsory.repositories.ContinentRepositoryJPA;
import compulsory.repositories.CountryRepositoryJPA;
import lombok.NoArgsConstructor;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

@NoArgsConstructor
public class CountriesInsertion {

    public void insertCountries(){
        try {
            File file = new File("src/main/resources/concap.csv");
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            String[] columns;
            CountryRepositoryJPA countryRepository = new CountryRepositoryJPA();
            countryRepository.beginTransaction();

            while ((line = br.readLine()) != null) {
                columns = line.split(",");
                String name = columns[0].replaceAll("'", " ");
                ContinentRepositoryJPA continentRepository = new ContinentRepositoryJPA();
                Continent continent = continentRepository.findByName(columns[5]);
                Country country = new Country(name, continent);
                countryRepository.create(country);
            }
            countryRepository.commitTransaction();
            countryRepository.closeTransaction();
            fr.close();
        }
        catch (IOException e){
            System.out.println("Error when handling file!");
        }
    }
}
