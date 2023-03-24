package smartCity.service;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import smartCity.model.Loc;
import smartCity.model.Locatie;
import smartCity.model.Parcare;
import smartCity.repository.LocRepository;
import smartCity.repository.ParcareRepository;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

@Service
public class Distanta {

    private ParcareRepository parcareRepository;
    private LocRepository locRepository;

    @Autowired
    public Distanta(ParcareRepository parcareRepository, LocRepository locRepository){
        this.parcareRepository = parcareRepository;
        this.locRepository = locRepository;
    };

    public HashMap getParcareLibera(Locatie locatie){
        List<Parcare> parcari = parcareRepository.findAll();
        List<Parcare> libere = new ArrayList<>();
        HashMap <Integer, Double> distante = new HashMap<>();
        HashMap <Integer, Double> rezultat = new HashMap<>();
        for(Parcare p: parcari){
            List<Loc> locuri = locRepository.findLocByIdParcareAndDisponibil(p.getId(),true);
            if(locuri.size()>0) libere.add(p);
        }
        if(libere.size()!=0){
            double min = computeDistance(locatie.getLatitudine(),locatie.getLongitudine(),
                    libere.get(0).getLatitudine(),libere.get(0).getLongitudine());
            for(Parcare p: libere){
                double dist = computeDistance(locatie.getLatitudine(),locatie.getLongitudine(),p.getLatitudine(),p.getLongitudine());
                if(min >= dist) min = dist;
                distante.put(p.getId(),dist);
            }
            for(Integer i : distante.keySet()){
                if(distante.get(i) <= min + 0.5) rezultat.put(i, distante.get(i));
            }
        }
        return rezultat;
    }

    public double computeDistance(double lat1, double long1, double lat2, double long2) {
        long1 = Math.toRadians(long1);
        long2 = Math.toRadians(long2);
        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        double lon = long2 - long1;
        double lat = lat2 - lat1;
        double a = Math.pow(Math.sin(lat / 2), 2)
                + Math.cos(lat1) * Math.cos(lat2)
                * Math.pow(Math.sin(lon / 2), 2);

        double c = 2 * Math.asin(Math.sqrt(a));
        double radius = 6371;
        return (c * radius * 1.609344 );
    }
}
