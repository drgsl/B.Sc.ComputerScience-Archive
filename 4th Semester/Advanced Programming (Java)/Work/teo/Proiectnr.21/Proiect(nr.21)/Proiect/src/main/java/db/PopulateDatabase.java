package db;

import entities.AlldataEntity;
import entities.CitiesEntity;
import entities.CountriesEntity;
import entities.StatesEntity;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.TypedQuery;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.List;

public class PopulateDatabase {

    public void populateTheDatabaseFromCsv(EntityManager entityManager, EntityTransaction transaction){
        String file = "./target/data/cities.csv";
        BufferedReader reader = null;
        String line = "";

        try{
          reader = new BufferedReader(new FileReader(file));
          int a=0;
          transaction.begin();
          AlldataEntity newEntity = new AlldataEntity();
          line = reader.readLine();//citesc headeru-ul
          int cont;
          while((line = reader.readLine()) != null){
              String[] row = line.split(",");
              cont=0;
              newEntity.setId(Integer.parseInt(row[cont]));
              cont++;
              if(row[cont].startsWith("\"") && !row[cont].endsWith("\"")){
                  newEntity.setName(row[cont] + row[cont+1]);
                  cont+=2;
              }else{
                  newEntity.setName(row[cont]);
                  cont++;
              }
              newEntity.setStateId(Integer.parseInt(row[cont]));
              cont++;
              newEntity.setStateCode(row[cont]);
              cont++;
              if(row[cont].startsWith("\"") && !row[cont].endsWith("\"")){
                  newEntity.setStateName(row[cont] + row[cont+1]);
                  cont+=2;
              }else{
                  newEntity.setStateName(row[cont]);
                  cont++;
              }
              newEntity.setCountryId(Integer.parseInt(row[cont]));
              cont++;
              newEntity.setCountryCode(row[cont]);
              cont++;
              if(row[cont].startsWith("\"") && !row[cont].endsWith("\"")){
                  newEntity.setCountryName(row[cont] + row[cont+1]);
                  cont+=2;
              }else{
                  newEntity.setCountryName(row[cont]);
                  cont++;
              }
              newEntity.setLatitude(row[cont]);
              cont++;
              newEntity.setLongitude(row[cont]);
              cont++;
              if(row.length>cont)
              newEntity.setWikidataid(row[cont]);
              else newEntity.setWikidataid("none");
              entityManager.merge(newEntity);
              System.out.println(a);
              a++;
          }
          transaction.commit();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void populateTables(EntityManager entityManager, EntityTransaction transaction){
        TypedQuery<AlldataEntity> query = entityManager.createNamedQuery("AlldataEntity.findAll", AlldataEntity.class);
        List<AlldataEntity> results = query.getResultList();
        StatesEntity newState = new StatesEntity();
        CountriesEntity newCountry = new CountriesEntity();
        CitiesEntity newCity = new CitiesEntity();
        //Object exists;
        transaction.begin();
        int a=0;
        for(AlldataEntity inst : results){
            newState.setStateId(inst.getStateId());
            newState.setCountryId(inst.getCountryId());
            newState.setStateCode(inst.getStateCode());
            newState.setStateName(inst.getStateName());
            entityManager.merge(newState);

            newCountry.setCountryId(inst.getCountryId());
            newCountry.setCountryCode(inst.getCountryCode());
            newCountry.setCountryName(inst.getCountryName());
            entityManager.merge(newCountry);

            newCity.setId(inst.getId());
            newCity.setName(inst.getName());
            newCity.setStateId(inst.getStateId());
            entityManager.merge(newCity);

            System.out.println(a);
            a++;
        }
        transaction.commit();
    }

    /*
    //exists = entityManager.createNamedQuery("CitiesEntity.verify").setParameter(1,inst.getName()).getSingleResult();
            if(!(Integer.parseInt(String.valueOf(exists)) >0)){
                newCity.setId(inst.getId());
                newCity.setName(inst.getName());
                newCity.setStateId(inst.getStateId());
                entityManager.merge(newCity);
            }
    */
}
