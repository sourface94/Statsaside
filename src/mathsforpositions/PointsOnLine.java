package mathsforpositions;

import footballstats.Point;

public class PointsOnLine {

    double[] unitVector;
    double[] firstPos;
    double[] secondPos;


    PointsOnLine(double[] firstPos, double[] secondPos){
        unitVector = new double[2];
        this.firstPos = firstPos;
        this.secondPos = secondPos;
        calculateEquationOfLine();
    }

    public void calculateEquationOfLine(){
        double D = euclideanDistance(firstPos, secondPos);
        double xVector = (secondPos[0] - firstPos[0]) / D;
        double yVector = (secondPos[1] - firstPos[1]) / D;
        unitVector[0] = xVector;
        unitVector[1] = yVector;
    }

    public double[] getCoordinatesForPointAtDistance(double d){
        double x = d* unitVector[0];
        double y = d* unitVector[1];
        double[] coordinates = {x, y};
        return coordinates;
    }


    public double euclideanDistance(double[] firstPos, double[] secondPos){
        double distance = Math.pow(secondPos[0] - firstPos[0], 2) + Math.pow(secondPos[1] - firstPos[1], 2);
        return Math.sqrt(distance);
    }

}
