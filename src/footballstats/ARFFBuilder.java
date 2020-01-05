package footballstats;

import mathsforpositions.LinearInterpolation;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class ARFFBuilder {
    
    public Map<String, ArrayList<String>> instanceMap;
    public int highestLength;
    public String input;
    boolean inputUnknownValues;
    int noTags;

    public ARFFBuilder (String inputFile, boolean inputUnknownValues, int noTags) {
        this.instanceMap = new HashMap<String, ArrayList<String>>();
        this.highestLength = 0;
        this.input = inputFile;
        this.inputUnknownValues = inputUnknownValues;
        this.noTags = noTags;
    }
        
    /*public static void main(String[] args) {
        String action = "action";
        String logDate = "06052018";
        String filePath = "../../action_times/" + logDate + "/" + action + "_output.txt";
        filePath = action + "_output.txt";
        try {
            ARFFBuilder b = new ARFFBuilder(filePath, false);
            b.createArffFile();
        }
        catch (IOException e){}
    }*/

    public int getHighestLength() {
        return highestLength;
    }

    public void setHighestLength(int highestLength) {
        this.highestLength = highestLength;
    }

    public Map<String, ArrayList<String>> getInstanceMap() {
        return instanceMap;
    }

    public void setInstanceMap(Map<String, ArrayList<String>> instanceMap) {
        this.instanceMap = instanceMap;
    }

    public String actionFromString(String text) {
        if(text.toLowerCase().contains("pass")) {
                return "pass";
        }
        if(text.toLowerCase().contains("tackle")) {
                return "tackle";
        }
        if(text.toLowerCase().contains("dribble")) {
                return "dribble";
        }
        if(text.toLowerCase().contains("inaccuratep")) {
                return "inaccuratePass";
        }
        else return "";
    }

    public void createArffFile(boolean addExtraPosToBeginning) throws IOException{
        readInputFile();
        writeToFile(getInstanceMap(), arffBeginning(getHighestLength()), addExtraPosToBeginning);
    }

    public String arffBeginning(int noAttributes){
        String beginning = "% 1. Title: Football Action Database\n%\n";
        beginning =  beginning +"% 2. Sources: \n%      (a) Creator: A.Joseph & N. Francis\n%\n";
        beginning =  beginning +"@RELATION Action";

        for (int i = 0; i < noAttributes - 1; i++){
            beginning =  beginning + "\n@ATTRIBUTE position" + i + " NUMERIC";
           // beginning =  beginning + "\n@ATTRIBUTE possession" + i + "{no-one,88B4,CC03}";
        }

        beginning =  beginning +"\n@ATTRIBUTE class        {pass,tackle,dribble,inaccuratePass}\n@data\n";
        return beginning;
    }

    public void readInputFile() throws IOException {
        String line = "";
        String previousLine = "";
        // reads input, output file. e.g pass_output
        BufferedReader br = new BufferedReader(new FileReader(input));
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
                    int length = line.split(",").length;
                    if (length > getHighestLength()) {
                        setHighestLength(length);
                    }
                    //work out what action is being processed, e.g pass, or tackle
                    previousLine = actionFromString(previousLine);

                    //add position values to hashmap
                    if (getInstanceMap().get(previousLine) != null) {
                        getInstanceMap().get(previousLine).add(line);
                    } else {
                        ArrayList<String> aList = new ArrayList<String>();
                        getInstanceMap().put(previousLine, aList);
                        getInstanceMap().get(previousLine).add(line);
                    }
                }
                previousLine = line;
            } else {
                previousLine = line;
            }
        }
    }

	public void  writeToFile( Map<String, ArrayList<String>> map, String beginning, boolean addExtraPosToBeginning) throws IOException{
        //create new interpolation object
        LinearInterpolation linearInter = new LinearInterpolation();
        // create new arff file
		FileWriter fw = new FileWriter(input + "_rtlsTrain.arff", true);
		BufferedWriter bw = new BufferedWriter(fw);
		PrintWriter out = new PrintWriter(bw);
		// writes the beginning of arff to arff file
		out.println(beginning);
		Iterator it = map.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry pair = (Map.Entry)it.next();
			@SuppressWarnings("unchecked")
			ArrayList<String> actionList = (ArrayList<String>) pair.getValue();
			//get action
			String action = (String) pair.getKey();
			for (String positions : actionList) {
               String [] posArray = positions.split(",");
               double [] floatPosArray = new double [posArray.length]; // = posArray.length;
                for (int i = 1; i < posArray.length; i++){

                    floatPosArray[i] = Double.parseDouble(posArray[i]);

                }

            double [] interpolatedPositions = LinearInterpolation.interpolateArray(floatPosArray, (getHighestLength()-1));

            out.println(createOutputLineFromArray(interpolatedPositions, action));


//				if(positions.split(",").length < getHighestLength() && addExtraPosToBeginning) {
//                    out.println(constructInstanceFillBeginning(positions, action));
//                }
//				else{
//				    out.println(constructInstanceFillEnd(positions, action));
//				}

			}
		}


		out.close();
            System.out.println("done");
	}

	public String createOutputLineFromArray(double [] array, String action){
	    String output = "";
        for (double a: array) {
             output += String.valueOf(a);
             output += ",";
        }
        output += action;

        return output;
    }

    public String constructInstanceFillEnd(String positions, String action){
        String output = "";
        String [] lineArray = positions.split(",");
        int count = 0;
        //output = output + "\n";
        //output = output +"<";
        boolean beginAddingLastKnownPos = false;
        for (int i = 0; i < getHighestLength(); i++) {

            if(count >= lineArray.length) {
                if (!inputUnknownValues) {
                    /*for(int t = noTags*3; t > 0; t--){

                        output = output + lineArray[lineArray.length - t];

                        if (t > 1){
                            output+=",";
                        }

                    }
                    count += noTags*3;
                    i = count;*/
                    output = output + lineArray[lineArray.length - 1];
                    count++;
                }
                else {
                    output = output + "?";
                    count++;
                }
            }
            else {
                //add line position value to output string
                output = output + lineArray[i];
                count++;
            }
            output = output +",";

        }
        output = output + action;
        //out.println(action + "\n");
        //erase first comma.
        return output.replaceFirst(",", "");
    }

    public String constructInstanceFillBeginning(String positions, String action){
        String output = "";
        String replacedCommas = positions.replaceAll(",", "#");
        String reversedPositions = new StringBuilder(replacedCommas).reverse().toString();
        String [] lineArray = reversedPositions.split("#");
        int count = 0;

        for (int i = 0; i < getHighestLength(); i++) {

            if (count >= lineArray.length) {
                if (!inputUnknownValues) {
                    for (int t = noTags * 3; t > 0; t--) {

                        output = output + lineArray[lineArray.length - t];
                        String x = lineArray[lineArray.length - t];
                        if (t > 1) {
                            output += ",";
                        }

                    }
                    count += noTags * 3;
                    i = count;

                } else {
                    output = output + "?";
                    count++;
                }
            } else {
                //add line position value to output string
                output = output + lineArray[i];
                count++;
            }
            output = output + ",";

        }
        output = new StringBuilder(output).reverse().toString();
        output = output + "," + action;
        //out.println(action + "\n");
        //erase first comma.
        return output.replaceFirst(",", "");
    }
}
