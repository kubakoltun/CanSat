import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class size_selector {
    static class MyFrame extends JFrame implements ActionListener {
        JButton addPersonButton;
        JButton exitButton;
        JComboBox sizeBox;
        JTextArea nameTextArea;
        JLabel nameLabel;
        JLabel sizeLabel;

        JTextArea dataTextArea;
        JScrollPane scroll;
        JSlider heightSlider;
        JSlider weightSlider;

        JPanel mainPanel;
        JPanel dataPanel;
        JPanel heightPanel;
        JPanel weightPanel;
        JPanel lowerPanel;

        DefaultListModel<Person> listModel;
        JList<Person> person;

        //Component c;

        public MyFrame() throws HeadlessException {
            JFrame frame = new JFrame(" PERSONS ");
            frame.getContentPane().setLayout(new GridLayout(0,1 ));

            mainPanel = new JPanel();
            dataPanel = new JPanel();
            heightPanel = new JPanel();
            weightPanel = new JPanel();
            lowerPanel = new JPanel();

            listModel = new DefaultListModel<>();
            person = new JList<>(listModel);

            dataPanel.setLayout(new BorderLayout());
            dataPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));
            dataTextArea = new JTextArea();
            dataTextArea.setWrapStyleWord(false);
            dataTextArea.setLineWrap(true);
            dataTextArea.setEditable(false);
            dataPanel.add(dataTextArea);
            scroll = new JScrollPane(person);
            scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
            scroll.setHorizontalScrollBarPolicy(
                    ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
            dataPanel.add(scroll);

            heightPanel.setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createTitledBorder("Height [cm]"),
                    BorderFactory.createEmptyBorder(5,5,5,5)));
            heightPanel.setLayout(new BorderLayout());
            heightSlider = new JSlider(100, 200);
            heightSlider.setMajorTickSpacing(10);
            heightSlider.setMinorTickSpacing(1);
            heightSlider.setPaintTicks(true);
            heightSlider.setPaintLabels(true);
            heightPanel.add(heightSlider);

            weightPanel.setBorder(BorderFactory.createCompoundBorder(
                    BorderFactory.createTitledBorder("Weight [kg]"),
                    BorderFactory.createEmptyBorder(5,5,5,5)));
            weightPanel.setLayout(new BorderLayout());
            weightSlider = new JSlider(40, 120);
            weightSlider.setMajorTickSpacing(10);
            weightSlider.setMinorTickSpacing(2);
            weightSlider.setPaintTicks(true);
            weightSlider.setPaintLabels(true);
            weightPanel.add(weightSlider);

            lowerPanel.setBorder(BorderFactory.createEmptyBorder(5,5,5,5));

            nameLabel = new JLabel("name:");
            lowerPanel.add(nameLabel);
            nameTextArea = new JTextArea(1, 14);
            lowerPanel.add(nameTextArea);

            sizeLabel = new JLabel("size:");
            lowerPanel.add(sizeLabel);

            String[] sizes = {
                    String.valueOf(Size.XS),
                    String.valueOf(Size.S),
                    String.valueOf(Size.M),
                    String.valueOf(Size.L),
                    String.valueOf(Size.XL)};
            sizeBox = new JComboBox(sizes);
            lowerPanel.add(sizeBox);

            addPersonButton = new JButton("Add person");
            addPersonButton.addActionListener(this);
            addPersonButton.setBounds(150, 330, 100, 10);
            lowerPanel.add(addPersonButton);

            exitButton = new JButton("Exit");
            exitButton.addActionListener(this);
            exitButton.setBounds(270, 330, 75, 20);
            lowerPanel.add(exitButton);

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(500, 400);
            frame.setVisible(true);
            frame.setLocationRelativeTo(null);
            frame.add(dataPanel);
            frame.add(heightPanel);
            frame.add(weightPanel);

        }

        @Override
        public void actionPerformed(ActionEvent e) {
            if (e.getSource() == exitButton) {
                System.exit(0);
            }

            if (e.getSource() == addPersonButton) {



                listModel.addElement(new Person(
                        nameTextArea.getText(),
                        heightSlider.getValue(),
                        weightSlider.getValue(),
                        sizeBox.getSelectedItem().toString()));

                class MyCellRenderer extends DefaultListCellRenderer {

                    public Component getListCellRendererComponent(
                            JList list, Object value, int index, boolean isSelected, boolean cellHasFocus) {
                        Component c = super.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
                        String s = sizeBox.getSelectedItem().toString();

                        if (s.equals("XS")) {
                            setBackground(Color.GREEN);
                        } else if (s.equals("XL")) {
                            setBackground(Color.RED);
                        }
                        return c;
                    }
                }


                dataTextArea.setText(listModel.toString());
                if (sizeBox.getSelectedItem().toString().equals("XS")) {
                    person.setBackground(Color.GREEN);
                }
                else if (sizeBox.getSelectedItem().toString().equals("XL")) {
                    person.setBackground(Color.RED);
                }
            }
        }
    }

    public static class Person {
        String name;
        int h;
        int w;
        String size;

        public Person(String name, int h, int w, String size) {
            this.name = name;
            this.h = h;
            this.w =w;
            this.size = size;
        }

        @Override
        public String toString() {
            return name + " (h=" + h + ", w=" + w + ", size=" + size + ")";
        }
    }

    public enum Size {
        XS, S, M, L, XL
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(
                ()-> new MyFrame()
        );
    }
}
