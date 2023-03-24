package panel;

import classes.Address;
import com.example.client.CallService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.util.Locale;

import static java.awt.BorderLayout.WEST;

public class ConfigPanel extends JPanel {
    final MainFrame frame;
    JLabel label,correctAddress,entityFalse,addressLabel,labelCity,labelState,labelCountry;
    JTextField cityText, stateText,countryText;
    JButton create;
    String city,state,country;

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
        create = new JButton("Verify Address");
        create.addActionListener(this::createGame);
        entityFalse = new JLabel();
        entityFalse.setVisible(false);
        addressLabel.setVisible(false);
        correctAddress = new JLabel();
        correctAddress.setVisible(true);
        setOpaque(false);
        label.setForeground(Color.white);
        labelCity.setForeground(Color.white);
        labelState.setForeground(Color.white);
        labelCountry.setForeground(Color.white);
        addressLabel.setForeground(Color.white);
        entityFalse.setForeground(Color.white);
        correctAddress.setForeground(Color.white);
        add(label);
        add(labelCountry);
        add(countryText);
        add(labelState);
        add(stateText);
        add(labelCity);
        add(cityText);
        add(create);
        add(entityFalse);
        add(addressLabel);
        add(correctAddress);
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
            entityFalse.setText("There is an empty field!");
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
            Address addressCorrector = new Address(city, state, country);
            CallService callService = new CallService();
            correctAddress.setVisible(true);
            correctAddress.setText(callService.verifyAddress(addressCorrector));
        }
    }

}
