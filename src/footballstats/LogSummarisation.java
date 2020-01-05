package footballstats;

import java.io.*;
import java.util.ArrayList;

public class LogSummarisation {
    //velocity
    //possession of ball
    String [] tags;
    double possessionClassifyingValue;

    public LogSummarisation(String [] tags, double classifyingValue) {
        this.tags = tags;
        this.possessionClassifyingValue = classifyingValue;
    }

    public void readOuputFile(String input) throws IOException {
        String line = "";
        String previousLine = "";
        // reads input, output file. e.g pass_output
        BufferedReader br = new BufferedReader(new FileReader(input));
        ArrayList<String> outputList = new ArrayList<String>();
        while ((line = br.readLine()) != null) {
            // process the line.
            if (line.length() > 0) {
                String firstLetter = line.substring(0, 1);
                //look for lines beginning with '[' beacuase they contain position values
                //remove all characters apart from position values
                if (firstLetter.equals("[")) {

                    line = line.replace("]", "");
                    line = line.replace("[", "");
                    line = line.replace("\n", "");
                    // work out number of posiitons to work out highest length
                    line.replaceFirst(" ,", "");

                    outputList.add(whoHasPossession(line.split(","), tags, previousLine));
                }
            }
            previousLine = line;
        }
        writeToFile(outputList, input);
    }

    public ArrayList<String> createPossessionData(String input) throws IOException {
        String line = "";
        String previousLine = "";
        // reads input, output file. e.g pass_output
        BufferedReader br = new BufferedReader(new FileReader(input));
        ArrayList<String> outputList = new ArrayList<String>();
        while ((line = br.readLine()) != null) {
            // process the line.
            if (line.length() > 0) {
                String firstLetter = line.substring(0, 1);
                //look for lines beginning with '[' beacuase they contain position values
                //remove all characters apart from position values
                if (firstLetter.equals("[")) {

                    line = line.replace("]", "");
                    line = line.replace("[", "");
                    line = line.replace("\n", "");
                    // work out number of posiitons to work out highest length
                    line.replaceFirst(" ,", "");

                    outputList.add(whoHasPossession(line.split(","), tags, previousLine));
                }
            }
            previousLine = line;
        }
        return outputList;
    }

    public void workOutVelocity() {

    }

    public Double distance(double x1, double y1, double x2, double y2) {
        return Math.sqrt((x1 - x2) * (x1 - x2) +
                (y1 - y2) * (y1 - y2));
    }

    public void writeToFile (ArrayList<String> output, String input) throws IOException{

        FileWriter fw = new FileWriter(input + "Possesion2.txt", true);
        BufferedWriter bw = new BufferedWriter(fw);
        PrintWriter out = new PrintWriter(bw);
        for (String line : output) {
            out.println(line);
        }

        out.close();

    }

    public String whoHasPossession(String[] positions, String [] tags, String prevLine) {
        int noPositions = (positions.length - 1) / 9; //first element is blank
        int count = 0;
        int lastIndex = 1;
        String output = "";
        double nearestDistance = 3;
        // posList = new ArrayList<String>();
        while (count != noPositions) {

            if ( areThereUnknownValues(positions, lastIndex, lastIndex + 8)){
              output = output + (",no-one");
            }

            else {
                Point first = new Point(Double.parseDouble(positions[lastIndex]), Double.parseDouble(positions[lastIndex + 1]));
                Point second = new Point(Double.parseDouble(positions[lastIndex + 3]), Double.parseDouble(positions[lastIndex + 4]));
                Point third = new Point(Double.parseDouble(positions[lastIndex + 6]), Double.parseDouble(positions[lastIndex + 7]));
               // Double firstAndSecondDist = second.distance(first);
               // Double thirdAndsecondDist = second.distance(third);
                Double firstAndSecondDist = first.distance(second);
                Double thirdAndsecondDist = first.distance(third);
                output = output + "," + whoHasMilisecondPos(firstAndSecondDist, thirdAndsecondDist);
            }
            lastIndex += 9;

            count++;
        }
        return prevLine + "\n" + "[" + output + "]";

    }


    public String whoHasMilisecondPos(double firstDistance, double secondDistance) {

        if (secondDistance > possessionClassifyingValue && firstDistance > possessionClassifyingValue) {
            return "no-one";
        } else if (firstDistance < secondDistance) {
            return tags[1];
        } else {
            return tags[2];
        }
    }

    public Boolean areThereUnknownValues (String [] input, int firstIndex, int lastIndex){
        boolean result = false;
        for (int i = firstIndex; i <= lastIndex; i++){
            if (input[i].contains("?") || input[i].contains("-1")){
                result = true;
                break;
            };
        }

        return result;
    }
}
