package homework.insertionDB;

import compulsory.items.Continent;
import compulsory.repositories.ContinentRepositoryJPA;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class ContinentsInsertion {

    public void insertContinents(){
        ContinentRepositoryJPA continentRepository = new ContinentRepositoryJPA();
        continentRepository.beginTransaction();
        continentRepository.create(new Continent("North America"));
        continentRepository.create(new Continent("South America"));
        continentRepository.create(new Continent("Central America"));
        continentRepository.create(new Continent("Europe"));
        continentRepository.create(new Continent("Antarctica"));
        continentRepository.create(new Continent("Asia"));
        continentRepository.create(new Continent("Africa"));
        continentRepository.create(new Continent("Australia"));
        continentRepository.commitTransaction();
        continentRepository.closeTransaction();
    }
}
