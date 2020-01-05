package StatsASideVisualisaiton;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;

import javax.swing.JComponent;

public class Player extends JComponent {

	private boolean isActive;
	
	public Player() {
	}
	
	public void setActive(boolean isActive) {
		this.isActive = isActive;
	}
	
	public boolean isActive() {
		return isActive;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D) g;
		double width = getWidth();
		double height = getHeight();
		double playerWidth = 1d;
		double scale;
		if(width/height >= 1d) {
			scale = height;
		} else {
			scale = width;
		}
		g2.scale(scale, scale);
		if(isActive()) {
			drawRing(g2, playerWidth);
		}
		drawBody(g2, playerWidth);
		drawHead(g2, playerWidth);
	}

	private void drawHead(Graphics2D g2, double playerWidth) {
		g2.setColor(new Color(140,104,74));
		double headWidth = playerWidth*6d/36d;
		double headHeight = playerWidth*8d/36d;
		g2.fill(new Ellipse2D.Double((playerWidth/2)-(headWidth/2), (playerWidth/2)-(headHeight/2), headWidth, headHeight));		
	}

	private void drawBody(Graphics2D g2, double playerWidth) {
		g2.setColor(Color.YELLOW);
		double bodyWidth = playerWidth*20d/36d;
		double bodyHeight = playerWidth*8d/36d;
		g2.fill(new Ellipse2D.Double((playerWidth/2)-(bodyWidth/2), (playerWidth/2)-(bodyHeight/2), bodyWidth, bodyHeight));
	}

	private void drawRing(Graphics2D g2, double playerWidth) {
		g2.setColor(Color.BLUE);
		float strokeWidth = 3f/36f;
		Stroke stroke = new BasicStroke(strokeWidth);
		g2.setStroke(stroke);
		g2.draw(new Ellipse2D.Double(strokeWidth/2, strokeWidth/2, playerWidth-strokeWidth, playerWidth-strokeWidth));
	}
}
