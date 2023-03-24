package laboratorpa.lab11.controllers;

import laboratorpa.lab11.entities.PersonEntity;
import laboratorpa.lab11.services.PersonService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("person")
public class PersonController {

    private final PersonService personService;

    @Autowired
    public PersonController(PersonService personService) {
        this.personService = personService;
    }

    @GetMapping(path = "/")
    public List<PersonEntity> getAll() {
        return personService.getAll();
    }

    @PostMapping(path = "/")
    public void addPerson(@RequestParam(name = "name", required = true) String name) {
        personService.addPerson(name);
    }

    @PutMapping(path = "/")
    public void changePersonName(@RequestParam(name = "id", required = true) Integer id,
                                 @RequestParam(name = "newName", required = true) String newName) {
        personService.setName(id, newName);
    }

    @DeleteMapping(path = "/")
    public void deletePerson(@RequestParam(name = "id", required = true) Integer id) {
        personService.deletePerson(id);
    }
}
