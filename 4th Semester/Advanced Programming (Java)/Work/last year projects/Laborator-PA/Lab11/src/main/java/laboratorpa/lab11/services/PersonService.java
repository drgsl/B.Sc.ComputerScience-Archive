package laboratorpa.lab11.services;

import laboratorpa.lab11.entities.PersonEntity;
import laboratorpa.lab11.repositories.PersonRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
public class PersonService {

    private final PersonRepository personRepository;

    @Autowired
    public PersonService(PersonRepository personRepository) {
        this.personRepository = personRepository;
    }

    public List<PersonEntity> getAll() {
        return personRepository.findAll();
    }

    public void addPerson(String name) {
        personRepository.save(new PersonEntity(name));
    }

    @Transactional
    public void setName(Integer id, String newName) {
        if (newName == null) {
            return;
        }
        personRepository.update(id, newName);
    }

    public void deletePerson(Integer id) {
        personRepository.deleteById(id);
    }
}
