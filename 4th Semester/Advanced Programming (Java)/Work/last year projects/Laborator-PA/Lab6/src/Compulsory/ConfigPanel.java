package Compulsory;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseWheelEvent;

public class ConfigPanel extends JPanel {
    final MainFrame frame;
    JSpinner sidesField;
    JSpinner sizeField;
    JComboBox<String> colorCombo; // the color of the shape

    JButton undo;

    public ConfigPanel(MainFrame frame) {
        this.frame = frame;
        setForRegularPolygon();
    }

    public void init() {
        removeAll();
        if ("Regular Polygon".equals(frame.canvas.getTypeOfDrawing())) {
            setForRegularPolygon();
        } else {
            setForPredefined();
        }
        repaint();
        validate();
    }

    private void setForRegularPolygon() {
        JLabel sidesLabel = new JLabel("Number of sides: ");
        sidesField = new JSpinner(new SpinnerNumberModel(3, 3, 100, 1));
        sidesField.setValue(3);

        JLabel colorLabel = new JLabel("Color type: ");
        JLabel sizeLabel = new JLabel("Size: ");

        colorCombo = new JComboBox<>();
        colorCombo.addItem("Random");
        colorCombo.addItem("Black");

        sizeField = new JSpinner(new SpinnerNumberModel(10, 10, 300, 10));

        undo = new JButton("Undo");
        undo.addActionListener(this::undoImage);

        add(sidesLabel); //JPanel uses FlowLayout by default
        add(sidesField);
        add(sizeLabel);
        add(sizeField);
        add(colorLabel);
        add(colorCombo);
        add(undo);
    }

    private void setForPredefined() {
        JLabel colorLabel = new JLabel("Color type: ");

        colorCombo = new JComboBox<>();
        colorCombo.addItem("Random");
        colorCombo.addItem("Black");

        JLabel sizeLabel = new JLabel("Size: ");
        sizeField = new JSpinner(new SpinnerNumberModel(10, 10, 300, 10));

        add(sizeLabel);
        add(sizeField);
        add(colorLabel);
        add(colorCombo);

    }

    private void undoImage(ActionEvent actionEvent) {
        if (frame.getStackOfImages().isEmpty()) {
            return;
        }

        // Delete the last drawn image
        if (frame.getStackOfImages().size() > 1) {
            frame.getStackOfImages().pop();

            // Reload the "before" image
            frame.getCanvas().graphics.drawImage(frame.getStackOfImages().peek(), 0, 0, frame.getCanvas());
            frame.getCanvas().repaint();
            System.out.println("Drawn img");
        }

    }
}
