package footballstats;

public class  Point {
    // the coordinates of the point
    private double x;
    private double y;

    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }

    public double getX() {
        return this.x;
    }

    public double getY() {
        return this.y;
    }

    // distance returns the distance between this point and a given point
    public double distance(Point p) {
        return Math.sqrt((p.x - this.x) * (p.x - this.x) +
                (p.y - this.y) * (p.y - this.y));
    }

    public String toString() {
        String s = "";
        //for (int i = 0; i < s.length(); i++) {
        s = "(" + this.getX() + "," + this.getY() + ")";

        return s;
    }

    public Point nearestPoint(Point[] points, Point point) {
        Point p = points[0];
        for (int i = 0; i < points.length; i++) {
            if (points[i].distance(point) < p.distance(point)) {
                p = points[i];
            }
        }
        return p;
    }

    public static Point[] internalPoints(Point[] points, double radius) {

        int countPoints = 0;
        for (int i = 0; i < points.length; i++) {
            double xp = points[i].getX();
            double yp = points[i].getY();
            // points are inside the circle if d^2 <= r^2
            // d^2 = (Xp-Xc)^2 + (Yp-Yc)^2
            // Xp and Yp is the point that should be checked
            // Xc and Xc is the point center (orgin)
            // Xc and Yc are 0 you end up with d^2 = (Xp-Xc)^2 + (Yp-Yc)^2
            if (xp * xp + yp * yp <= radius * radius) {
                countPoints++;
            }
        }
        int companionVar = 0;
        Point[] pointsInside = new Point[countPoints];
        for (int j = 0; j < countPoints; j++) {
            pointsInside[companionVar] = points[j];
            companionVar++;
        }
        return pointsInside;
    }
}