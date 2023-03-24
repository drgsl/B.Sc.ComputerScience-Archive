package project;

import javax.swing.*;
import java.awt.event.ActionEvent;

public class ConfigPanel extends JPanel {
    final MainFrame frame;
    JLabel label;
    JSpinner spinner1, spinner2;
    JButton create;

    public int getRows() {
        return rows;
    }

    public void setRows(int rows) {
        this.rows = rows;
    }

    public int getCols() {
        return cols;
    }

    public void setCols(int cols) {
        this.cols = cols;
    }

    int rows, cols;

    public ConfigPanel(MainFrame frame) {
        this.frame = frame;
        init();
    }
    public void init() {
        //create the label and the spinner
        label = new JLabel("Grid size:");
        spinner1 = new JSpinner(new SpinnerNumberModel(5, 2, 100, 1));
        spinner2 = new JSpinner(new SpinnerNumberModel(5, 2, 100, 1));

        create = new JButton("Create");
        create.addActionListener(this::createGame);

        add(label); //JPanel uses FlowLayout by default
        add(spinner1);
        add(spinner2);
        add(create);
    }

    private void createGame(ActionEvent e) {
        frame.repaint();
    }
}
