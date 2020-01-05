package StatsASideVisualisaiton;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;

import javax.swing.JComponent;

public class Ball extends JComponent {

	/**
	 * Create the panel.
	 */
	public Ball() {
		
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D) g;
		double width = getWidth();
		double height = getHeight();
		double ballWidth = 9d/36d;
		double scale;
		if(width/height >= 1d) {
			scale = height/ballWidth;
		} else {
			scale = width/ballWidth;
		}
		g2.scale(scale, scale);
		drawBall(g2, ballWidth);
	}

	private void drawBall(Graphics2D g2, double ballWidth) {
		float strokeWidth = 0.2f/36f;
		g2.setColor(Color.WHITE);
		g2.fill(new Ellipse2D.Double(strokeWidth/2, strokeWidth/2, ballWidth-strokeWidth, ballWidth-strokeWidth));
		
		g2.setColor(Color.BLACK);
		Stroke stroke = new BasicStroke(strokeWidth);
		g2.setStroke(stroke);
		g2.draw(new Ellipse2D.Double(strokeWidth/2, strokeWidth/2, ballWidth-strokeWidth, ballWidth-strokeWidth));
		
	}

}
