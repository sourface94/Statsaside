package StatsASideVisualisaiton;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.awt.geom.AffineTransform;
import java.awt.geom.Arc2D;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;

import javax.swing.*;

public class Field extends JLayeredPane {

	private static final long serialVersionUID = 1L;

	public Field(int width, int height) {
		setBackground(new Color(0, 128, 0));
		//widht = 550, height = 350
		setPreferredSize(new Dimension(width, height));
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		Graphics2D g2 = (Graphics2D) g;
		super.paintComponent(g2);
		double width = getWidth();
		double height = getHeight();
		double fieldLength = 110d;
		double fieldWidth = 70d;
		double scaleWidth = fieldLength+2;
		double scaleHeight = fieldWidth+2;
		double scale;
		if((width/height) >= (110d/70d)) {
			scale = height/scaleHeight;
		} else {
			scale = width/scaleWidth;
		}
		g2.scale(scale, scale);
		g2.translate(1, 1);
		g2.setColor(Color.WHITE);
		Stroke stroke = new BasicStroke(5f/36f);
		g2.setStroke(stroke);
		drawTouchLines(g2, fieldLength, fieldWidth);
		drawGoalLines(g2, fieldLength, fieldWidth);
		drawCenterLine(g2, fieldLength, fieldWidth);
		drawCenterCircle(g2, fieldLength, fieldWidth);
		drawCenterMark(g2, fieldLength, fieldWidth);
		drawCornerArches(g2, fieldLength, fieldWidth);
		drawGoals(g2, fieldLength, fieldWidth);
		drawGoalAreas(g2, fieldLength, fieldWidth);
		drawPenaltyAreas(g2, fieldLength, fieldWidth);
		drawPenaltyMarks(g2, fieldLength, fieldWidth);
		drawPenaltyArches(g2, fieldLength, fieldWidth);
	}

	private void drawPenaltyArches(Graphics2D g2, double fieldLength,
			double fieldWidth) {
//		double extent = 2*Math.toDegrees(Math.acos(6d/10d));
		double extent = 106.26020470831196d;
		g2.draw(new Arc2D.Double(fieldLength-12-10, (fieldWidth/2)-10, 20, 20, 180-(extent/2), extent, Arc2D.OPEN));
		g2.draw(new Arc2D.Double(12-10, (fieldWidth/2)-10, 20, 20, -extent/2, extent, Arc2D.OPEN));
	}

	private void drawPenaltyMarks(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.fill(new Ellipse2D.Double(fieldLength-12-(10d/36), (fieldWidth/2)-(10d/36), (20d/36), (20d/36)));
		g2.fill(new Ellipse2D.Double(12-(10d/36), (fieldWidth/2)-(10d/36), (20d/36), (20d/36)));
	}

	private void drawPenaltyAreas(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Rectangle2D.Double(0, (fieldWidth/2)-22, 18, 42));
		g2.draw(new Rectangle2D.Double(fieldLength-18, (fieldWidth/2)-22, 18, 42));
	}

	private void drawGoalAreas(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Rectangle2D.Double(0, (fieldWidth/2)-10, 6, 20));
		g2.draw(new Rectangle2D.Double(fieldLength-6, (fieldWidth/2)-10, 6, 20));
	}

	private void drawGoals(Graphics2D g2, double fieldLength, double fieldWidth) {
		g2.draw(new Rectangle2D.Double(-1, (fieldWidth/2)-4, 1, 8));
		g2.draw(new Rectangle2D.Double(fieldLength, (fieldWidth/2)-4, 1, 8));
	}

	private void drawCornerArches(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Arc2D.Double(-1, -1, 2, 2, 270, 90, Arc2D.OPEN));
		g2.draw(new Arc2D.Double(fieldLength-1, -1, 2, 2, 180, 90, Arc2D.OPEN));
		g2.draw(new Arc2D.Double(fieldLength-1, fieldWidth-1, 2, 2, 90, 90, Arc2D.OPEN));
		g2.draw(new Arc2D.Double(-1, fieldWidth-1, 2, 2, 0, 90, Arc2D.OPEN));
	}

	private void drawCenterMark(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.fill(new Ellipse2D.Double((fieldLength/2)-(10d/36), (fieldWidth/2)-(10d/36), (20d/36), (20d/36)));
	}

	private void drawCenterCircle(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Ellipse2D.Double((fieldLength/2)-10, (fieldWidth/2)-10, 20, 20));
	}

	private void drawCenterLine(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Line2D.Double(fieldLength/2, 0, fieldLength/2, fieldWidth));
	}

	private void drawGoalLines(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Line2D.Double(0, 0, 0, fieldWidth));
		g2.draw(new Line2D.Double(fieldLength, 0, fieldLength, fieldWidth));
	}

	private void drawTouchLines(Graphics2D g2, double fieldLength,
			double fieldWidth) {
		g2.draw(new Line2D.Double(0, 0, fieldLength, 0));
		g2.draw(new Line2D.Double(0, fieldWidth, fieldLength, fieldWidth));
	}
	
}
