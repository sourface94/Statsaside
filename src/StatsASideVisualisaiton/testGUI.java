package StatsASideVisualisaiton;

    import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;

    public class testGUI extends JFrame{

        private JLayeredPane layeredPane;
        private RedPanel redPanel;
        private YellowPanel yellowPanel;

        public testGUI()    {

            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setSize(new Dimension(300, 310));

            //Create and set up the layered pane.
            layeredPane = new Field(300, 310);


            //create a red panel
            redPanel = new RedPanel();
           // redPanel.setBackground(Color.RED);
            //make it the same size as parent
            redPanel.setBounds(getBounds());
            Player al = new Player();
            al.setBounds(getBounds());
            //at it to layered pane with index of 1
            //layeredPane.add(redPanel, 1);
           layeredPane.add(al, 3);

            //similarly make yellow panel
            yellowPanel = new YellowPanel (redPanel); //yellow panel has a reference
            //to red panel
            yellowPanel.setBackground(Color.YELLOW);
            yellowPanel.setBounds(getBounds());
            layeredPane.add(yellowPanel, 2);


            //add a mouse listener to both panels
            redPanel.addMouseListener(getMouseListener(yellowPanel));
            yellowPanel.addMouseListener(getMouseListener(redPanel));

            setContentPane(layeredPane);
            layeredPane.setLayout(new BorderLayout(0, 0));

            setVisible(true);
        }

        //mouse listener: when a panel is clicked, the other panel
        //is moved to front
        private MouseListener getMouseListener(JPanel panel) {

            return new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {

                    layeredPane.moveToFront(panel);
                }
            };
        }

        public class RedPanel extends JPanel {

            RedPanel(){

            }
            //returns a fixed value
            public int getValue() {
                return 16;
            }
        }

        public class YellowPanel extends JPanel {

            YellowPanel(RedPanel redPanel){
                //add a label showing value retrieved from red panel
                add(new JLabel("Value from red panel is :"+ redPanel.getValue()));
            }
        }

        public static void main(String[] args) {

            javax.swing.SwingUtilities.invokeLater(new Runnable() {
                @Override
                public void run() {

                    new testGUI();
                }
            });
        }
    }
