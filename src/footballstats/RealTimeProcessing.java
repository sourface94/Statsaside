package footballstats;

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.TimeUnit;

public class RealTimeProcessing {
    PosLogToArff pos;
    String logfile;
    double lastEndTime;
    ArrayList<Integer> classifications;
    Boolean classifyActions;
    double timeSinceLastPosition;
    long positionWindow;
    String [] tagids;

    public RealTimeProcessing (PosLogToArff pos, String[] tagids, String logfile, long positionWindow) throws IOException {
        this.logfile = logfile;
        this.pos = pos;
        this.lastEndTime = 0.0;
        this.classifications = new ArrayList<Integer>();
        this.classifyActions = true;
        this.timeSinceLastPosition = 0.0;
        this.positionWindow = positionWindow;
        this.tagids = new String[] {"41AA", "88B4", "CC03"};//tagids;
        //liveClassification();
    }

    public RealTimeProcessing (String[] tagids, String logfile, long positionWindow) throws IOException {
        this.logfile = logfile;
        this.lastEndTime = 0.0;
        this.classifications = new ArrayList<Integer>();
        this.classifyActions = true;
        this.timeSinceLastPosition = 0.0;
        this.positionWindow = positionWindow;
        this.tagids = new String[] {"41AA", "88B4", "CC03"};//tagids;
        //liveClassification();
    }


    public void beginProcessing() throws InterruptedException {
        while (classifyActions = true) {

            int classification = getClassificationOfPosition(getNextSetOfPositions(0.0, "file"));
            classifications.add(classification);
            System.out.println(classification);
            lastEndTime = lastEndTime + positionWindow;
            timeSinceLastPosition = 0.0;

            TimeUnit.SECONDS.sleep(positionWindow);

        }
    }

    public double[][] createPositionImage(double [] positions){
        double [][] image = {{0.0},{0.0}};
        return image;
    }

    public double [] getNextSetOfPositions(double positionWindow, String logfile){
        double [] positions = {0.0, 0.1, 0.2, 0.3} ;
        return positions;
    }

    public void changeLastEndTime(double time){
        this.lastEndTime = time;
    }

    public void resetEndTime(){
        this.lastEndTime = 0.0;
    }

    public int getClassificationOfPosition(double [] positions){
        double [][] image = createPositionImage(positions);
        int classification = 0;
        return classification;
    }

    public void liveClassificationAnalysis() throws IOException {
        //tackles
        double[][] timeTuples =  {{3360,3420},
                {3425,3495},
                {3544,3597},
                {3607,3895},
                {3672,3722},
                {3730,3784},
                {3791,3847},
                {3850,3903},
                {3910,3965},
                {3970,4038},
                {4045,4103},
                {4111,4185},
                {4270,4259},
                {4317,4384},
                {4390,4445},
                {4456,4523},};

        //dribbles
//        double[][] timeTuples =  {{5812,59043},
//                {5908,5987}};

        //tackles
//        double[][] timeTuples =  {{10992,11083},
//                {1109,1159},
//                {11161,1125},
//                {11253,11315}
//        };

        ArrayList<String> allResults = new ArrayList<>();
        allResults.add("start,end,prob,class");
        for (int i = 0; i < timeTuples.length; i++){
            System.out.println("Classifying combinations from: " + timeTuples[i][0] + " to: " + timeTuples[i][1]);
            allResults.add("Classifying combinations from: " + timeTuples[i][0] + " to: " + timeTuples[i][1] + "\n");
            ArrayList<String> results = classificationBetweenSetTimesWithSkips(timeTuples[i]);
            allResults.addAll(results);
            allResults.add("\n");
            System.out.println("");
        }
        //write results to file
        FileWriter writer = new FileWriter("liveresultstest/live_classification_analysis_results.txt");
        for(String str: allResults) {
            writer.write(str);
        }
        writer.close();

    }

    public ArrayList<String> classificationBetweenSetTimes(double[] timeLimits) throws IOException {
        ArrayList<String> results = new ArrayList<>();
        //String[] classNames = {"Tackle", "Dribble", "Pass"};
        String[] classNames = {"Dribble" , "Pass", "Tackle"}; // redone class names after conversion to three training classes
        //10 = 1 seconds and 1 = 1 milisecond i.e. 23 = 2.3 seconds, 103 = 10.3 seconds, 123 = 12.3 seconds 1352 = 135.2 secondds
        //maximum time an action can take is 50 which is 5 seconds
        int maxTimeWindow = 80;
        //loop from 0 miliseconds to max duration of log file
        PosLogToArffFast posFast = new PosLogToArffFast("100219", "actions_100219" ,tagids, false, true);
        for (double currentTime = timeLimits[0]; currentTime < timeLimits[1]; currentTime++){
            double[] probabilities = new double[maxTimeWindow*10];
            int[] classes = new int[maxTimeWindow*10];

            //loop from current time to the maximum time an action can take
            int count = 0;
            for (double j = currentTime + 1; j < currentTime+maxTimeWindow && j <= timeLimits[1]; j+= 1){
                if (j == 30)
                    System.out.println();
                //classify this time window as an action
                double[] times = {currentTime / 10, j / 10};

                posFast.actionTimes = times;
                posFast.time = 0;
                posFast.timeCount = 0;
                posFast.hasStarted = false;
                posFast.makeStop = false;

                //create image
                boolean result = posFast.generateActionPositionsForLiveClassification();
                posFast.fileIndex = posFast.indexOfActionStart;
                //if it didnt find any positions then go to the next times
                if (!result)
                    return results;
                //classify image and get result

                Process p = Runtime.getRuntime().exec("py -3.6 kera_cnn_transferlearning.py " + (currentTime/10) + " " + ((j)/10));
                BufferedReader stdInput = new BufferedReader(new
                        InputStreamReader(p.getInputStream()));
                //0 = tackle, 1 = pass 2 = dribble
                String output = stdInput.readLine();
                output = stdInput.readLine();
                //String output = "2,[0.111 0.99 0.12]";

                //get class classifier thinks it most likely is
                //this way
                int windowMaxIndex = Integer.parseInt(output.substring(0, output.indexOf(",")));
                String[] classificationValuesTemp = output.substring(3,output.length()-1).split(" ");
                String[] classificationValues = new String[4];
                count = 0;
                for (int i = 0; i < classificationValuesTemp.length; i++){
                    if (!classificationValuesTemp[i].trim().isEmpty()){
                        classificationValues[count] = classificationValuesTemp[i];
                        count++;
                    }
                }
                double windowMaxProb = Double.parseDouble(classificationValues[windowMaxIndex].trim());
                double[] probAndClass = {windowMaxIndex, windowMaxProb};
                classes[count] = (int)probAndClass[0];
                probabilities[count] = probAndClass[1];
                System.out.println("Time: " + (currentTime/10) + " to " + ((j)/10) + ", Probability: " + windowMaxProb + ", Class: " + classNames[windowMaxIndex]);
                //results.add("Time: " + (currentTime/10) + " to " + ((j)/10) + ", Probability: " + windowMaxProb + "\n");
                results.add((currentTime/10) + "," + ((j)/10) + "," + windowMaxProb + "," + classNames[windowMaxIndex] + "\n");
                count++;
            }

            //get highest classification probability
//            double maxProb = probabilities[0];
//            int maxIndex = 0;
//            for (int j = 1; j < probabilities.length; j++){
//                //System.out.print("prediction:  " + classes[j] + "  " + classNames[classes[j]] + " probability: " + probabilities[j] + " \n");
//                if (probabilities[j] > maxProb){
//                    maxProb = probabilities[j];
//                    maxIndex = j;
//
//                }
//            }

            //set currentTime to end  of image with the highest probability score
            //double newTime = currentTime + 1;
//            for(int i  : classes){
//                System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[classes[i]] );
//            }
            //System.out.println("Time (secs): " + (currentTime /10) + " to " + ((currentTime + maxIndex)/10) + ". Classified as: " + classNames[classes[maxIndex]] + " Max Prob: " + maxProb);
            //System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[0] + " Max Prob: " + maxProb);
            //currentTime = newTime;

        }
        return results;
    }

    public ArrayList<String> classificationBetweenSetTimesWithSkips(double[] timeLimits) throws IOException {
        ArrayList<String> results = new ArrayList<>();
        //String[] classNames = {"Tackle", "Dribble", "Pass"};
        String[] classNames = {"Dribble" , "Pass", "Tackle"}; // redone class names after conversion to three training classes
        //10 = 1 seconds and 1 = 1 milisecond i.e. 23 = 2.3 seconds, 103 = 10.3 seconds, 123 = 12.3 seconds 1352 = 135.2 secondds
        //maximum time an action can take is 50 which is 5 seconds
        int maxTimeWindow = 80;
        //loop from 0 miliseconds to max duration of log file
        PosLogToArffFast posFast = new PosLogToArffFast("100219", "actions_100219" ,tagids, false, true);
        double timeDifference = timeLimits[1] - timeLimits[0];
        int increment = (int) timeDifference / 3;
        System.out.println("increment: " +increment);
        for (double currentTime = timeLimits[0]; currentTime < timeLimits[1]; currentTime+= increment){
            double[] probabilities = new double[maxTimeWindow*10];
            int[] classes = new int[maxTimeWindow*10];

            //loop from current time to the maximum time an action can take
            int count = 0;
            for (double j = currentTime + 1; j < currentTime+maxTimeWindow && j <= timeLimits[1]; j+= increment){
                if (j == 30)
                    System.out.println();
                //classify this time window as an action
                double[] times = {currentTime / 10, j / 10};

                posFast.actionTimes = times;
                posFast.time = 0;
                posFast.timeCount = 0;
                posFast.hasStarted = false;
                posFast.makeStop = false;

                //create image
                boolean result = posFast.generateActionPositionsForLiveClassification();
                posFast.fileIndex = posFast.indexOfActionStart;
                //if it didnt find any positions then go to the next times
                if (!result)
                    return results;
                //classify image and get result

                Process p = Runtime.getRuntime().exec("py -3.6 kera_cnn_transferlearning.py " + (currentTime/10) + " " + ((j)/10));
                BufferedReader stdInput = new BufferedReader(new
                        InputStreamReader(p.getInputStream()));
                //0 = tackle, 1 = pass 2 = dribble
                String output = stdInput.readLine();
                output = stdInput.readLine();
                //String output = "2,[0.111 0.99 0.12]";

                //get class classifier thinks it most likely is
                //this way
                int windowMaxIndex = Integer.parseInt(output.substring(0, output.indexOf(",")));
                String[] classificationValuesTemp = output.substring(3,output.length()-1).split(" ");
                String[] classificationValues = new String[4];
                count = 0;
                for (int i = 0; i < classificationValuesTemp.length; i++){
                    if (!classificationValuesTemp[i].trim().isEmpty()){
                        classificationValues[count] = classificationValuesTemp[i];
                        count++;
                    }
                }
                double windowMaxProb = Double.parseDouble(classificationValues[windowMaxIndex].trim());
                double[] probAndClass = {windowMaxIndex, windowMaxProb};
                classes[count] = (int)probAndClass[0];
                probabilities[count] = probAndClass[1];
                System.out.println("Time: " + (currentTime/10) + " to " + ((j)/10) + ", Probability: " + windowMaxProb + ", Class: " + classNames[windowMaxIndex]);
                //results.add("Time: " + (currentTime/10) + " to " + ((j)/10) + ", Probability: " + windowMaxProb + "\n");
                results.add((currentTime/10) + "," + ((j)/10) + "," + windowMaxProb + "," + classNames[windowMaxIndex] + "\n");
                count++;
                if (j < timeLimits[1] && j + increment > timeLimits[1]) {
                    System.out.println("will get bigger");
                    j = timeLimits[1] - increment;
                }
            }
            //currentTime += increment;

            //get highest classification probability
//            double maxProb = probabilities[0];
//            int maxIndex = 0;
//            for (int j = 1; j < probabilities.length; j++){
//                //System.out.print("prediction:  " + classes[j] + "  " + classNames[classes[j]] + " probability: " + probabilities[j] + " \n");
//                if (probabilities[j] > maxProb){
//                    maxProb = probabilities[j];
//                    maxIndex = j;
//
//                }
//            }

            //set currentTime to end  of image with the highest probability score
            //double newTime = currentTime + 1;
//            for(int i  : classes){
//                System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[classes[i]] );
//            }
            //System.out.println("Time (secs): " + (currentTime /10) + " to " + ((currentTime + maxIndex)/10) + ". Classified as: " + classNames[classes[maxIndex]] + " Max Prob: " + maxProb);
            //System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[0] + " Max Prob: " + maxProb);
            //currentTime = newTime;

        }
        return results;
    }

    public void liveClassification() throws IOException {
        //String[] classNames = {"Tackle", "Dribble", "Pass"};
        String[] classNames = {"Dribble" , "Pass", "Tackle"}; // redone class names after conversion to three training classes
        //10 = 1 seconds and 1 = 1 milisecond i.e. 23 = 2.3 seconds, 103 = 10.3 seconds, 123 = 12.3 seconds 1352 = 135.2 secondds
        //max time in log file is 10000 which is 1000 seconds which is 16.67 minutes
        int maxTimeInLogFile = 12805;
        //maximum time an action can take is 50 which is 5 seconds
        int maxTimeWindow = 80;
        //loop from 0 miliseconds to max duration of log file
        pos = new PosLogToArff();
        for (double currentTime = 3290; currentTime < maxTimeInLogFile; currentTime++){
            double[] probabilities = new double[maxTimeWindow*10];
            int[] classes = new int[maxTimeWindow*10];

            //loop from current time to the maximum time an action can take
            int count = 0;
            for (double j = currentTime + 1; j < currentTime+maxTimeWindow; j+= 1){
                if (j == 30)
                    System.out.println();
                //classify this time window as an action
                double[] times = {currentTime / 10, j / 10};

                pos.actionTimes = times;

                //create image
                boolean result = pos.generateActionPositionsForLiveClassification("logs/100219/100219.txt", "actions_100219" ,tagids, false, true);
                //if it didnt find any positions then go to the next times
                if (!result)
                    return;
                //classify image and get result

                Process p = Runtime.getRuntime().exec("py -3.6 kera_cnn_transferlearning.py");
                BufferedReader stdInput = new BufferedReader(new
                        InputStreamReader(p.getInputStream()));
                //0 = tackle, 1 = pass 2 = dribble
                String output = stdInput.readLine();
                output = stdInput.readLine();
                //String output = "2,[0.111 0.99 0.12]";

                //get class classifier thinks it most likely is
                //this way
                int windowMaxIndex = Integer.parseInt(output.substring(0, output.indexOf(",")));
                String[] classificationValuesTemp = output.substring(3,output.length()-1).split(" ");
                String[] classificationValues = new String[4];
                count = 0;
                for (int i = 0; i < classificationValuesTemp.length; i++){
                    if (!classificationValuesTemp[i].trim().isEmpty()){
                        classificationValues[count] = classificationValuesTemp[i];
                        count++;
                    }
                }
                double windowMaxProb = Double.parseDouble(classificationValues[windowMaxIndex].trim());

//                Random rand = new Random();
//                windowMaxIndex = rand.nextInt(3) + 0;
//                windowMaxProb = (rand.nextInt(100) + 0) / (double)100;

                //or alternatively this way
//                output = output.substring(3,output.length());
//                String[] classificationValues = output.split(" ");
//                int windowMaxIndex = 0;
//                double windowMaxProb = Double.parseDouble(classificationValues[0]);
//
//                for (int k = 1; k < classificationValues.length; k++){
//                    if (Double.parseDouble(classificationValues[k]) > windowMaxProb){
//                        windowMaxProb = Double.parseDouble(classificationValues[k]);
//                        windowMaxIndex = k;
//                    }
//                }
                //System.out.println("Times enetered loop:" + count + "max prob: " + windowMaxProb);
                double[] probAndClass = {windowMaxIndex, windowMaxProb};
                classes[count] = (int)probAndClass[0];
                probabilities[count] = probAndClass[1];
                System.out.println("Time: " + (currentTime/10) + " to " + ((currentTime + j)/10) + ", Probability: " + windowMaxProb + ", Probability: " + windowMaxProb);
                count++;
            }

            //get highest classification probability
            double maxProb = probabilities[0];
            int maxIndex = 0;
            for (int j = 1; j < probabilities.length; j++){
                //System.out.print("prediction:  " + classes[j] + "  " + classNames[classes[j]] + " probability: " + probabilities[j] + " \n");
                if (probabilities[j] > maxProb){
                    maxProb = probabilities[j];
                    maxIndex = j;

                }
            }

            //set currentTime to end  of image with the highest probability score
            double newTime = currentTime + (maxIndex) + 1;
//            for(int i  : classes){
//                System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[classes[i]] );
//            }
            System.out.println("Time (secs): " + (currentTime /10) + " to " + ((currentTime + maxIndex)/10) + ". Classified as: " + classNames[classes[maxIndex]] + " Max Prob: " + maxProb);
            //System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[0] + " Max Prob: " + maxProb);
            currentTime = newTime;

        }
    }

    public void postMatchClassification() throws IOException {
//        PosLogToArff allData = new PosLogToArff();
        String logDate = "100219";
//        allData.actionTimes = new double[] {0, 2202};
//        allData.readFile("100219", "actions_100219" ,tagids, false, true);
        String fileName = "logs/" + logDate + "/" + "actions_100219_output.txt";
        ArrayList<ArrayList<Double>> possessionChanges = TimeWindow.changeInPossession(fileName);

        //thist 'times' list will store start and end time pairs
        ArrayList<List<Double>> times = new ArrayList<List<Double>>();
        int index = 0;
        // create lists with one start and one end value and add them to the 'times' list
        while(index + 1 < possessionChanges.get(0).size()){// should be 'possessionChanges.get(0)' here, but for testing purposes i get the second array of positions
            List<Double> timeSet = possessionChanges.get(0).subList(index, index + 2);
            times.add(timeSet);
            index++;

        }
        //create dummy time data
//        ArrayList<Double> pass = new ArrayList<Double>(Arrays.asList(20.00,25.80));
//        ArrayList<Double> dribble = new ArrayList<Double>(Arrays.asList(895.8, 905.0));
//        ArrayList<Double> ptackle = new ArrayList<Double>(Arrays.asList(2190.0, 2202.0));
//        // just for testing
        //ArrayList<ArrayList<Double>> times = new ArrayList<ArrayList<Double>>(Arrays.asList(pass, ptackle, dribble)) ;
        //allData.actionTimes = times;
        //String[] classNames = {"Tackle", "Dribble", "Pass"};
        String[] classNames = {"Dribble" , "Pass", "Tackle"}; // redone class names after conversion to three training classes
        //10 = 1 seconds and 1 = 1 milisecond i.e. 23 = 2.3 seconds, 103 = 10.3 seconds, 123 = 12.3 seconds 1352 = 135.2 secondds
        //max time in log file is 10000 which is 1000 seconds which is 16.67 minutes
        int maxTimeInLogFile = 12805;
        //maximum time an action can take is 50 which is 5 seconds
        int maxTimeWindow = 40;
        //loop from 0 miliseconds to max duration of log file
        pos = new PosLogToArff();
        // loop through array list of tuples containing start and end times
        for (List<Double> timeSet : times){
            double[] timeTuple;

            //classify this start and end time window as an action

            for (double currentTime = timeSet.get(0); currentTime < timeSet.get(1); ){

                ArrayList<Double> probabilities = new ArrayList<Double>();
                ArrayList<Integer> classes = new ArrayList<Integer>();

                for (double j = currentTime + 1; j <= timeSet.get(1); j++){
                    double[]  thisTimeTuple = {currentTime /10, j / 10};// + 26 is there for testing purposes, needs to be removed

                    timeTuple = thisTimeTuple;
                    pos.actionTimes = timeTuple;

                    boolean result = pos.generateActionPositionsForLiveClassification("logs/100219/100219.txt", "actions_100219" ,tagids, false, true);
                    //if it didnt find any positions then go to the next times
                    if (!result)
                        return;
                    //classify image and get result

                    Process p = Runtime.getRuntime().exec("py -3.6 kera_cnn_transferlearning.py");
                    BufferedReader stdInput = new BufferedReader(new
                            InputStreamReader(p.getInputStream()));
                    //0 = tackle, 1 = pass 2 = dribble
                    String output = stdInput.readLine();
                    if(output == "null")
                        return;
                    output = stdInput.readLine();
                    //String output = "2,[0.111 0.99 0.12]";

                    //get class classifier thinks it most likely is
                    //this way
                    int windowMaxIndex = Integer.parseInt(output.substring(0, output.indexOf(",")));
                    String[] classificationValuesTemp = output.substring(3,output.length()-1).split(" ");
                    String[] classificationValues = new String[4];
                    int count = 0;
                    for (int i = 0; i < classificationValuesTemp.length; i++){
                        if (!classificationValuesTemp[i].trim().isEmpty()){
                            classificationValues[count] = classificationValuesTemp[i];
                            count++;
                        }
                    }
                    double windowMaxProb = Double.parseDouble(classificationValues[windowMaxIndex].trim());

//                Random rand = new Random();
//                windowMaxIndex = rand.nextInt(3) + 0;
//                windowMaxProb = (rand.nextInt(100) + 0) / (double)100;

                    //or alternatively this way
//                output = output.substring(3,output.length());
//                String[] classificationValues = output.split(" ");
//                int windowMaxIndex = 0;
//                double windowMaxProb = Double.parseDouble(classificationValues[0]);
//
//                for (int k = 1; k < classificationValues.length; k++){
//                    if (Double.parseDouble(classificationValues[k]) > windowMaxProb){
//                        windowMaxProb = Double.parseDouble(classificationValues[k]);
//                        windowMaxIndex = k;
//                    }
//                }
                    //System.out.println("Times enetered loop:" + count + "max prob: " + windowMaxProb);
                    double[] probAndClass = {windowMaxIndex, windowMaxProb};
                    classes.add( (int)probAndClass[0]);
                    probabilities.add(probAndClass[1]);
                    count++;

                }

                //get highest classification probability
                if (probabilities.size() == 0)
                    continue;
                double maxProb = probabilities.get(0);
                int maxIndex = 0;
                for (int j = 1; j < probabilities.size(); j++){
                    System.out.print("prediction:  " + classes.get(j) + "  " + classNames[classes.get(j)] + " \n");
                    if (probabilities.get(j) >= maxProb){
                        maxProb = probabilities.get(j);
                        maxIndex = j;

                    }
                }
                System.out.println("Time (secs): " + (currentTime/10) + " to " + ((currentTime+maxIndex)/10) + ". Classified as: " + classNames[classes.get(maxIndex)] + " Max Prob: " + maxProb);

                //set currentTime to end  of image with the highest probability score
                double newTime = currentTime + (maxIndex) + 1;
                currentTime = newTime;
            }


            // said poslogto arff action times
            //pos.actionTimes = timeTuple;
            //pos.actionTimes = new double[] {timeTuple[0], endTime};
            //create image





            //set currentTime to end  of image with the highest probability score
//            for(int i  : classes){
//                System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[classes[i]] );
//            }

            //System.out.println("Time (secs): " + (currentTime /10) + " to " + (newTime/10) + ". Classified as: " + classNames[0] + " Max Prob: " + maxProb);


        }
    }

    public String classify(double startTime, double endTime) throws IOException {
        String[] classNames = {"Dribble" , "Pass", "Tackle"}; // redone class names after conversion to three training classes
        //10 = 1 seconds and 1 = 1 milisecond i.e. 23 = 2.3 seconds, 103 = 10.3 seconds, 123 = 12.3 seconds 1352 = 135.2 secondds
        //maximum time an action can take is 50 which is 5 seconds
        //loop from 0 miliseconds to max duration of log file
        PosLogToArffFast posFast = new PosLogToArffFast("100219", "actions_100219" ,tagids, false, true);
        posFast.actionTimes = new double [] {startTime, endTime};
        posFast.time = 0;
        posFast.timeCount = 0;
        posFast.hasStarted = false;
        posFast.makeStop = false;

        //create image
        boolean result = posFast.generateActionPositionsForLiveClassification();
        posFast.fileIndex = posFast.indexOfActionStart;
        //if it didnt find any positions then go to the next times
        if (!result)
            return "";
        //classify image and get result

        Process p = Runtime.getRuntime().exec("py -3.6 kera_cnn_transferlearning.py " + (startTime/10) + " " + ((endTime)/10));
        BufferedReader stdInput = new BufferedReader(new
                InputStreamReader(p.getInputStream()));
        //0 = tackle, 1 = pass 2 = dribble
        String output = stdInput.readLine();
        output = stdInput.readLine();
        //String output = "2,[0.111 0.99 0.12]";

        //get class classifier thinks it most likely is
        //this way
        int windowMaxIndex = Integer.parseInt(output.substring(0, output.indexOf(",")));
        String[] classificationValuesTemp = output.substring(3,output.length()-1).split(" ");
        String[] classificationValues = new String[4];
        int count = 0;
        for (int i = 0; i < classificationValuesTemp.length; i++){
            if (!classificationValuesTemp[i].trim().isEmpty()){
                classificationValues[count] = classificationValuesTemp[i];
                count++;
            }
        }
        double windowMaxProb = Double.parseDouble(classificationValues[windowMaxIndex].trim());
            System.out.println("Time: " + (startTime/10) + " to " + ((endTime)/10) + ", Probability: " + windowMaxProb + ", Class: " + classNames[windowMaxIndex]);

        return classNames[windowMaxIndex];
    }




}
