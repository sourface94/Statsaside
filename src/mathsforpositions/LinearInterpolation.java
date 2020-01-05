/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mathsforpositions;

/**
 *
 * @author natha
 */
public class LinearInterpolation {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        double[] source = {5,8,4,2,1};
        double[] destination = interpolateArray(source, 5);
        for (int i = 0; i < destination.length; i++){
            if ( i != destination.length){
                System.out.print(destination[i] + ", ");
            }
            else{
                System.out.print(destination[i]);
        }
    }
        
        
    }
    
    public static double[] interpolateArray(double[] source, int destinationLength){
        double[] destination = new double[destinationLength];

        destination[0] = source[0];
        int jPrevious = 0;
        for (int i = 1; i < source.length; i++)
        {
            int j = i * (destination.length - 1)/(source.length - 1);
            interpolate(destination, jPrevious, j, source[i - 1], source[i]);

            jPrevious = j;
        }     
        return destination;
    }
    
    private static void interpolate(double[] destination, int destFrom, int destTo, double valueFrom, double valueTo)
    {
        int destLength = destTo - destFrom;
        double valueLength = valueTo - valueFrom;
        for (int i = 0; i <= destLength; i++)
            destination[destFrom + i] = valueFrom + (valueLength * i)/destLength;
    }
}
