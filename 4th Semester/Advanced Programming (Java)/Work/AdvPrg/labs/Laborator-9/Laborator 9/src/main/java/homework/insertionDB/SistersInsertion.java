package homework.insertionDB;

import compulsory.items.Sister;
import compulsory.repositories.CityRepositoryJPA;
import compulsory.repositories.SisterRepository;
import lombok.NoArgsConstructor;

import java.util.HashSet;
import java.util.Random;
import java.util.Set;

@NoArgsConstructor
public class SistersInsertion {

    public void insertSisterRelationship(){
        CityRepositoryJPA cityRepository = new CityRepositoryJPA();
        long count = cityRepository.getCount();

        Set<Pair> sisters = new HashSet<>();
        while(sisters.size() < 100) {

            Random rand = new Random();
            long id1 = rand.nextLong(count) + 1;
            long id2 = rand.nextLong(count) + 1;
            while (id1 == id2) {
                id2 = rand.nextLong(count) + 1;
            }
            Pair pair = new Pair((int) id1, (int) id2);
            sisters.add(pair);
        }
        SisterRepository sisterRepository = new SisterRepository();
        sisterRepository.beginTransaction();
        for(Pair pair: sisters){
            Sister sister = new Sister();
            sister.setCity1(pair.getFirst());
            sister.setCity2(pair.getSecond());
            sisterRepository.create(sister);
        }
        sisterRepository.commitTransaction();
        sisterRepository.closeTransaction();
    }
}
