package StatsASideVisualisaiton;

import java.awt.EventQueue;

import javax.swing.*;

public class  Application {

	private JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Application window = new Application();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Application() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new FieldFrame();
		JLayeredPane pane = new JLayeredPane();
		frame.add(pane);

		Field pitch = new Field(450, 300);
		Ball ball = new Ball();
		ball.setVisible(true);
		pitch.add(ball);
		Player aaj = new Player();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(pitch);
		//frame.add(ball);
		//frame.add(aaj);
	}

}
