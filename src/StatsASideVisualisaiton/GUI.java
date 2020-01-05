package StatsASideVisualisaiton;

import StatsASideVisualisaiton.FieldFrame;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.HashMap;

public class GUI {
    public static void main(String[] args) {
        Program program = new Program();
        program.run();
    }
}

class Program {
    private HashMap<String, ArrayList<Float>> positionTable;
    private JFrame mainFrame;
    private DrawPanel drawPanel;
    private java.util.List<Agent> agents;

    private int windowWidth = 640;
    private int windowHeight = 480;
    private String windowLabel = "Stats-a-Side";


    void run() {
        positionTable = new HashMap<String, ArrayList<Float>>();
        createAgents();
        /* Initialize program */
        mainFrame = new JFrame();
        drawPanel = new DrawPanel();
        Field field = new Field(windowWidth, windowHeight);

        drawPanel.add(field, BorderLayout.CENTER);

        mainFrame.getContentPane().add(drawPanel);
        mainFrame.setTitle(windowLabel);
        mainFrame.setSize(windowWidth, windowHeight);
        mainFrame.setVisible(true);
        mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        field.setBackground(new Color(0, 128, 0));










        //contentPane.add(field, BorderLayout.CENTER);
        while (true) {
            int count = 20;
            for (Agent b: agents) {
                b.updatePosition(count,60);
                count+=20;
            }

            /* Give Swing 10 milliseconds to see the update! */
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            mainFrame.repaint();
            field.repaint();
        }
    }

    public void updateAgentPosition(String agent, float posX, float posY){

        for (Agent a : agents){

            if (a.getName().equals(agent)){

            }
        }
    }


    public void createAgents(){

        agents = new ArrayList<>();

        /* Generate agents */

        Agent ball = new Agent(
                "ball",
                /* Random positions from 0 to windowWidth or windowHeight */
                (int) Math.floor(Math.random() * windowWidth),
                (int) Math.floor(Math.random() * windowHeight),
                /* Random size from 10 to 30 */
                10,
                /* Random RGB colors*/
                new Color(100,0,0)
        );

        agents.add(ball);


        Agent alex = new Agent(
                "Alex",
                /* Random positions from 0 to windowWidth or windowHeight */
                (int) Math.floor(Math.random() * windowWidth),
                (int) Math.floor(Math.random() * windowHeight),
                /* Random size from 10 to 30 */
                20,
                /* Random RGB colors*/
                new Color(0,150,0)
        );

        agents.add(alex);




        Agent nathan = new Agent(
                "Nathan",
                /* Random positions from 0 to windowWidth or windowHeight */
                (int) Math.floor(Math.random() * windowWidth),
                (int) Math.floor(Math.random() * windowHeight),
                /* Random size from 10 to 30 */
                20,
                /* Random RGB colors*/
                new Color(0,0,100)
        );

        agents.add(nathan);


    }


    class DrawPanel extends JPanel {
        @Override
        public void paintComponent(Graphics graphics) {
            super.paintComponent(graphics);

            for (Agent b: agents) {
                b.draw(graphics);
            }

        }
    }



    class Agent {
        private int posX, posY, size;
        private Color color;
        String name;

        public Agent(String agentName, int posX, int posY, int size, Color color) {
            this.name = agentName;
            this.posX = posX;
            this.posY = posY;
            this.size = size;
            this.color = color;

        }

        public String getName(){
            return name;
        }

        void updatePosition(int x, int y) {

            posX = x;
            posY = y;
            if (posX > mainFrame.getWidth()) {
                posX = mainFrame.getWidth();
            }

            if (posX < 0) {
                posX = 0;
            }

            if (posY > mainFrame.getHeight()) {
                posY = mainFrame.getHeight();
            }

            if (posY < 0) {
                posY = 0;
            }

        }

        void draw(Graphics g) {
            g.setColor(color);
            g.fillOval(posX, posY, size, size);
        }
    }
}




