package com.example.lab11.controllers;

import com.example.lab11.entity.Person;
import com.example.lab11.services.PersonService;
import org.apache.velocity.exception.ResourceNotFoundException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.ArrayList;
import java.util.List;

@RestController
public class PersonController {
    private final PersonService personService;

    @Autowired
    public PersonController(PersonService personService) {
        this.personService = personService;
    }

    @GetMapping("/test")
    public String test() {
        return "Testing the API";
    }

    @GetMapping("person/list")
    public List<Person> getUsers() {
        return personService.getUsers();
    }

    @PostMapping("person/add")
    public ResponseEntity<Object> addUser(@RequestParam String name) {
        Person person = personService.getPersonByUsername(name);
        System.out.println(person);
        if (person != null) {
            return new ResponseEntity<>("Person already exists", HttpStatus.BAD_REQUEST);
        }
        person = new Person();
        person.setUsername(name);
        personService.addPerson(person);
        return new ResponseEntity<>("Person added successfully", HttpStatus.OK);
    }

    @PutMapping("person/update")
    public ResponseEntity<Object> updateUser(@RequestParam String name) {
        Person person = personService.getPersonByUsername(name);
        if (person != null) {
            person.setUsername(name);
            personService.updatePerson(person);
            return new ResponseEntity<>("Person updated successfully", HttpStatus.OK);
        }
        throw new ResourceNotFoundException("Person does not exist");
    }

    @DeleteMapping("person/delete")
    public ResponseEntity<Object> deleteUser(@RequestParam String name) {
        Person person = personService.getPersonByUsername(name);
        if (person != null) {
            personService.deletePerson(person);
            return new ResponseEntity<>("Person deleted successfully", HttpStatus.OK);
        }
        throw new ResourceNotFoundException("Person does not exist");
    }

    @PutMapping("person/add_friend")
    public ResponseEntity<Object> addFriend(@RequestParam String name, String friend) {
        Person person = personService.getPersonByUsername(name);
        if (person == null) {
            throw new ResourceNotFoundException("Person does not exist");
        }
        Person newFriend = personService.getPersonByUsername(friend);
        if (newFriend == null) {
            throw new ResourceNotFoundException("Person does not exist");
        }
        if (personService.alreadyFriends(person, newFriend)) {
            return new ResponseEntity<>("Persons already friends", HttpStatus.BAD_REQUEST);
        }
        person.addFriend(newFriend);
        newFriend.addFriend(person);
        personService.updatePerson(person);
        personService.updatePerson(newFriend);
        return new ResponseEntity<>("Friend added", HttpStatus.OK);
    }

    @GetMapping("person/friends")
    public List<String> friends(@RequestParam String name) {
        Person person = personService.getPersonByUsername(name);
        if (person == null) {
            throw new ResourceNotFoundException("Person does not exist");
        }
        List<String> friendsNames = new ArrayList<>();
        for (Person myPerson : person.getFriends()) {
            friendsNames.add(myPerson.getUsername());
        }
        return friendsNames;
    }

    @GetMapping("k-most-popular")
    public List<String> getMostPopular(@RequestParam Integer limit) {
        var list = personService.getMostPopular();
        List<String> names = new ArrayList<>();
        for (Person person : list) {
            names.add(person.getUsername());
            if (list.indexOf(person) + 1 == limit) {
                break;
            }
        }
        return names;
    }

    @GetMapping("k-least-popular")
    public List<String> getLeastPopular(@RequestParam Integer limit) {
        var list = personService.getLeastPopular();
        List<String> names = new ArrayList<>();
        for (Person person : list) {
            names.add(person.getUsername());
            if (list.indexOf(person) + 1 == limit) {
                break;
            }
        }
        return names;
    }

    @GetMapping("person/most_important")
    public List<String> getMostImportant() {
        var list = personService.getMostImportant();
        List<String> names = new ArrayList<>();
        for (Person person : list) {
            names.add(person.getUsername());
        }
        return names;
    }
}

