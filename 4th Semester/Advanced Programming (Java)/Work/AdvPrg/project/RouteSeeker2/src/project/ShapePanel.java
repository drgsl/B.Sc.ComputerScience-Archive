package project;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ShapePanel extends JPanel {
    MainFrame frame;
    JComboBox<String> shapeList;

    public ShapePanel(MainFrame frame) {
        this.frame = frame;
        shapeList = new JComboBox<>();

        shapeList.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                frame.getConfigPanel().init();
            }
        });

        JLabel shapeLabel = new JLabel("Shape: ");

        add(shapeLabel);
        add(shapeList);
    }

    public void addShape(String shape) {
        shapeList.addItem(shape);
    }

    public String getSelectedItem() {
        return (String) shapeList.getSelectedItem();
    }
}
