package panel;

import classes.AddressCorrector;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.Locale;

public class ConfigPanel extends JPanel {
    final MainFrame frame;
    JLabel label,correctAddress,entityFalse,incorrectAddress,addressLabel,labelCity,labelState,labelCountry;
    JTextField cityText, stateText,countryText;
    JButton create;
    String city,state,country;
    EntityManagerFactory entityManagerFactory = Persistence.createEntityManagerFactory("default");
    EntityManager entityManager = entityManagerFactory.createEntityManager();

    public ConfigPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }

    private void init() {
        label = new JLabel("Address Input:");
        labelCity = new JLabel("City: ");
        labelState = new JLabel("State: ");
        labelCountry = new JLabel("Country: ");
        cityText = new JTextField();
        stateText = new JTextField();
        countryText = new JTextField();
        addressLabel = new JLabel();
       /* cityText.setPreferredSize( new Dimension( 200, 24 ) );
        stateText.setPreferredSize( new Dimension( 200, 24 ) );
        countryText.setPreferredSize( new Dimension( 200, 24 ) );*/
        create = new JButton("Verify Address");
        create.addActionListener(this::createGame);
        //create spinners for rows and cols, and the button
        entityFalse = new JLabel();
        entityFalse.setVisible(false);
        incorrectAddress = new JLabel("Incorrect Address!");
        incorrectAddress.setVisible(false);
        addressLabel.setVisible(false);
        correctAddress = new JLabel();
        correctAddress.setVisible(false);
        add(label);
        add(labelCountry);
        add(countryText);
        add(labelState);
        add(stateText);
        add(labelCity);
        add(cityText);
        add(create);
        add(entityFalse);
        add(incorrectAddress);
        add(addressLabel);
    }

    private void createGame(ActionEvent e) {
        String output;
        boolean next = true;
        addressLabel.setVisible(false);
        correctAddress.setVisible(false);
        entityFalse.setVisible(false);
        city = cityText.getText();
        state = stateText.getText();
        country = countryText.getText();
        if (city.length()==0 || state.length()==0 || country.length()==0) {
            entityFalse.setText("This is an empty field!");
            entityFalse.setVisible(true);
            next = false;
        }
        if (next) {
            output = city.substring(0, 1).toUpperCase() + city.substring(1).toLowerCase(Locale.ROOT);
            city = output;
            output = state.substring(0, 1).toUpperCase() + state.substring(1).toLowerCase(Locale.ROOT);
            state = output;
            output = country.substring(0, 1).toUpperCase() + country.substring(1).toLowerCase(Locale.ROOT);
            country = output;
            AddressCorrector addressCorrector = new AddressCorrector(city, state, country, entityManager);
            if (!addressCorrector.verifyCountry()) {
                if(!addressCorrector.verifyStateByName()){
                    if(!addressCorrector.verifyCityByName()){
                        entityFalse.setText("Nothing from this address can be found in the database!");
                        entityFalse.setVisible(true);
                    }else{
                        addressCorrector.setStateName();
                        addressCorrector.setCountryName();
                        addressLabel = new JLabel("The correct address is:");
                        add(addressLabel);
                        addressLabel.setVisible(true);
                        correctAddress.setText("City: " + addressCorrector.getCity() + " State: " + addressCorrector.getState() + " Country: " + addressCorrector.getCountry());
                        correctAddress.setVisible(true);
                        add(correctAddress);
                    }
                }else{
                    addressCorrector.setCountryName();
                    addressLabel = new JLabel("The correct address is:");
                    add(addressLabel);
                    addressLabel.setVisible(true);
                    correctAddress.setText("City: " + addressCorrector.getCity() + " State: " + addressCorrector.getState() + " Country: " + addressCorrector.getCountry());
                    correctAddress.setVisible(true);
                    add(correctAddress);
                }
            } else if (!addressCorrector.verifyState()) {
                if (!addressCorrector.verifyCityByName()) {
                    entityFalse.setText("The city and the state doesn't exist!");
                    entityFalse.setVisible(true);
                } else {
                    addressCorrector.setStateName();
                    addressLabel = new JLabel("The correct address is:");
                    add(addressLabel);
                    addressLabel.setVisible(true);
                    correctAddress.setText("City: " + addressCorrector.getCity() + " State: " + addressCorrector.getState() + " Country: " + addressCorrector.getCountry());
                    correctAddress.setVisible(true);
                    add(correctAddress);
                }

            } else if (addressCorrector.verifyCity() == false) {
                entityFalse.setText("City doesn't exist!");
                entityFalse.setVisible(true);
            } else {
                correctAddress.setText("Address is correct!");
                correctAddress.setVisible(true);
                add(correctAddress);
            }
        }
    }

}
