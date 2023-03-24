package smartCity.controller;

import smartCity.model.Loc;
import smartCity.model.Locatie;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import smartCity.model.Rezervare;
import smartCity.model.RezervareBody;
import smartCity.repository.LocRepository;
import smartCity.repository.ParcareRepository;
import smartCity.repository.UserRepository;
import smartCity.service.Distanta;
import smartCity.service.Mail;

import javax.mail.MessagingException;
import java.io.IOException;
import java.util.*;

@RestController
@RequestMapping("/parkingLots")
public class ParcareController {

    private ParcareRepository parcareRepository;
    private LocRepository locRepository;
    private UserRepository userRepository;
    private Distanta distanta;
    List<Rezervare> rezervari = new ArrayList<>();

    @Autowired
    public ParcareController(ParcareRepository parcareRepository, LocRepository locRepository, UserRepository userRepository, Distanta distanta) {
        this.parcareRepository = parcareRepository;
        this.locRepository = locRepository;
        this.userRepository = userRepository;
        this.distanta = distanta;
    }


    @PostMapping(consumes = "application/json")
    public ResponseEntity<String> findLoc(@RequestBody Locatie locatie) {
        HashMap<Integer,Double> locuri = distanta.genodetParcareLibera(locatie);
        if(locuri.size()==0)
        {
            return new ResponseEntity<>("Nu sunt locuri libere de parcare", HttpStatus.OK);
        }
        String raspuns = "Cele mai apropiate parcari sunt: ";
        for(Integer i: locuri.keySet()){
            raspuns += parcareRepository.findParcareById(i).getStrada();
            raspuns += " cu id-ul ";
            raspuns += i;
            raspuns += " la distanta de ";
            raspuns += locuri.get(i);
            raspuns += " km cu locurile libere: ";
            List<Loc> locuriParcare = locRepository.findLocByIdParcareAndDisponibil(i,true);
            for(Loc l: locuriParcare){
                raspuns += l.getIdLoc();
                raspuns += " ";
            }
            raspuns += "\n";
        }
        return new ResponseEntity<>(raspuns, HttpStatus.OK);
    }

    @PostMapping(value = "/rezerva", consumes = "application/json")
    public ResponseEntity<String> occupySpot(@RequestBody RezervareBody body){
        Rezervare rezervare = new Rezervare(locRepository.findByIdParcareAndIdLoc(body.getIdParcare(),body.getIdLoc()).getId(),
                userRepository.findUserByUsername(body.getUsername()).getId(), body.getDurata());
        rezervari.add(rezervare);
        Loc ocupat = new Loc(rezervare.getIdLoc(), body.getIdLoc(), body.getIdParcare());
        if(locRepository.findLocById(ocupat.getId()).isDisponibil()==false)
            return new ResponseEntity<>("Locul nu mai este disponibil", HttpStatus.OK);
        else{
            ocupat.setDisponibil(false);
            locRepository.save(ocupat);
            TimerTask task = new TimerTask() {
                public void run() {
                    if(locRepository.findLocById(ocupat.getId()).isDisponibil()==false)
                    {
                        Mail mail = new Mail();
                        try {
                            mail.sendmail(userRepository.findUserByUsername(body.getUsername()).getEmail());
                        }
                        catch(MessagingException | IOException e){
                            e.printStackTrace();
                        }
                    }
                }
            };
            Timer timer = new Timer("Timer");
            long delay = body.getDurata()*30000L;
            timer.schedule(task, delay);
            return new ResponseEntity<>("Locul de parcare a fost rezervat", HttpStatus.OK);
        }
    }

    @PostMapping(value = "/elibereaza", consumes = "application/json")
    public ResponseEntity<String> freeSpot(@RequestBody RezervareBody body){
        Loc eliberat = new Loc(locRepository.findByIdParcareAndIdLoc(body.getIdParcare(),body.getIdLoc()).getId(), body.getIdLoc(), body.getIdParcare());
        if(locRepository.findLocById(eliberat.getId()).isDisponibil()==true)
            return new ResponseEntity<>("Acest loc este deja liber", HttpStatus.OK);
        else{
            eliberat.setDisponibil(true);
            locRepository.save(eliberat);
            return new ResponseEntity<>("Locul de parcare a fost eliberat", HttpStatus.OK);
        }
    }
}
