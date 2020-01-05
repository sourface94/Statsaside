/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package footballstats;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;

//import java.text.DecimalFormat;

/**
 *
 * @author natha
 */
public class PosLogToArffFast {

    //each line of the file is stores here and file index is the current line
    ArrayList<String> fileLines;
    int fileIndex = 0;

    //time of pass 1 starts at index 0 and ends at index 1, 
    //time of pass 2 starts at index 2 and ends at index 3 etc
    double actionTimes[];
    
    ArrayList<ArrayList<String>> actions;    
    
    double time = 0.0;
    int timeCount = 0;
    int numPlayers = 0;
    String[] playerIDs;
    String [][] lastKnownPositions;
    double lastTime = 0.000;
    int actionTimeCount = 0;
    int actionCount = 0;
    boolean hasStarted = false;
    boolean makeStop = false;
    int numActions;
    int startRecording = 0;
    String[] tagIds;
    boolean replaceWithUnknown;
    boolean useLastKnownPos;
    String action;
    int indexOfActionStart = 0;

    public PosLogToArffFast(){}

    public PosLogToArffFast(String logDate, String action, String tagIDs[], boolean replaceWithUnknown, boolean useLastKnownPos) throws FileNotFoundException {
        loadFile(logDate);
        if (actionTimes == null || actionTimes.length == 0)
            readCSVFile(logDate, action);
        //read log file
        numActions = actionTimes.length/2;
        actions = new ArrayList<ArrayList<String>>(numActions);
        startRecording = 0;
        String actionStart = action + " start";
        String actionEnd = action + " end";
        //the index currently at from the actionTime array eg pass 0 starts, pass 0 end, pass 1 start
        actionTimeCount = 0;
        //the action instance number eg pass 0, pass 1, pass 2
        actionCount = 0;
        //this indicates whether an instance of an action has started
        hasStarted = false;
        makeStop = false;
        this.replaceWithUnknown = replaceWithUnknown;
        this.useLastKnownPos = useLastKnownPos;
        this.action = action;
        playerIDs = tagIDs;
        numPlayers = tagIDs.length;
        lastKnownPositions = new String[tagIDs.length][3];
        for (int i = 0; i < lastKnownPositions.length; i++){
            for (int j = 0; j < lastKnownPositions[i].length; j++)
                if (replaceWithUnknown){
                    lastKnownPositions[i][j] = "?";
                }
                else {
                    lastKnownPositions[i][j] = "-1";
                }
        }
    }


    public void loadFile(String logDate) throws FileNotFoundException {
        String fileName = "logs/" + logDate + "/" + logDate + ".txt";
        Scanner file = new Scanner(new File(fileName));
        fileLines = new ArrayList<>();
        while (file.hasNextLine()) {
            //System.out.println(time);
            //get the next line and increment current line number
            String lineFromFile = file.nextLine();
            fileLines.add(lineFromFile);
        }
        fileIndex = 0;

    }
    
    public void readFile(String logDate, String action, String tagIDs[], boolean replaceWithUnknown, boolean useLastKnownPos) throws FileNotFoundException, IOException{
        //get start and end time of each instance of an action from csv file
        //and put it in actionTimes array
        if (actionTimes == null || actionTimes.length == 0)
            readCSVFile(logDate, action);
        initialiseLastPositions(tagIDs, replaceWithUnknown);
        
        //read log file
        numActions = actionTimes.length/2;
        actions = new ArrayList<ArrayList<String>>(numActions);
        startRecording = 0;
        String actionStart = action + " start";
        String actionEnd = action + " end";
        //the index currently at from the actionTime array eg pass 0 starts, pass 0 end, pass 1 start
        actionTimeCount = 0;
        //the action instance number eg pass 0, pass 1, pass 2
        actionCount = 0;
        //this indicates whether an instance of an action has started
        hasStarted = false;
        makeStop = false;
        //current line number
        int lineNumber = -1;
        //while the file has a next line and the end of the action hasnt been
        //reached yet
        loadFile(logDate);
        while (fileIndex < fileLines.size() && startRecording != 2 && actionTimeCount != actionTimes.length)
        {
            //System.out.println(time);
            //get the next line and increment current line number
            String lineFromFile = fileLines.get(fileIndex);
            fileIndex++;
            
            //if beginning of action set startRecording to 1
            if(lineFromFile.contains(actionStart))
            {
                startRecording = 1;
                lineFromFile = fileLines.get(fileIndex);
                fileIndex++;
            }
            //if end of action set startRecording to 2
            if (lineFromFile.contains(actionEnd))
            {
                startRecording = 2;
                break;
            }
            
            //if start of action has begun then get positions of each instance 
            //of an action and put it in actions ArrayList
            if (startRecording == 1){              
                //if the time is equal to the time in actionTimes then 
                //it is either the beginnging of an instance of an action
                if (actionTimes[actionTimeCount] == time){
                    System.out.println(time);
                    //if an instance has already started then it is now
                    //the end of the instance and increase actionTimeCount
                    //to go to the next element in actionTimes (which will be
                    //the start of the next instance)
                    if (hasStarted){
                        makeStop = true;
                        //hasStarted = false;
                        actionTimeCount++;
                    }
                    //else if an instance hasnt already started then it is now
                    //the beginning of an instance and increase actionTimeCount
                    //to go to the next element in actionTimes (which will be the
                    //end of this instance). Add new ArrayList to actions
                    //to hold positios for this instance
                    else{
                        hasStarted  = true;
                        //****************************************************************************************************
                        actions.add(new ArrayList<String>());
                        actionTimeCount++;
                        actionCount++;
                    }
                }
                //if an instance has started then add the lines for this 
                //0.1 second to the ArrayList
                if (hasStarted){
                    String line = lineFromFile;
                    //get next lines that are part of this 0.1 second
                    while (fileIndex < fileLines.size()){
                        lineFromFile = fileLines.get(fileIndex);
                        fileIndex++;
                        if (lineFromFile.contains(actionEnd))
                        {
                            //System.out.println("FOUND THE END");
                            startRecording = 2;
                            //System.out.println(lineFromFile);
                            break;
                        }
                        //System.out.println(lineFromFile);
                        if (lineFromFile.length() != 0){
                            line += " & " + lineFromFile;
                        }
                        else{
                            //go back to previous line
                            //goToPreviousLine(file, lineNumber);
                            //exit loop
                            break;
                        }
                        lineNumber++;
                    }
                    //add line to the current instance
                    //updateLastPositions(line);
                    line = addMissingPositions(line);
                    actions.get(actionCount-1).add(line);
                    //System.out.println("actioncount: " + (actionCount-1));
                    lineFromFile = fileLines.get(fileIndex);
                    fileIndex++;
                    if (lineFromFile.contains(actionEnd))
                    {
                        //System.out.println("FOUND THE END");
                        startRecording = 2;
                        //System.out.println(lineFromFile);
                        break;
                    }
                    
                    if (makeStop == true){
                        hasStarted = false;
                        makeStop = false;
                    }
                }
                
                //100 milliseconds has passed so increase time
                if (lineFromFile.length() > 0 && lineFromFile.charAt(0) == '['){
                    time = timeCount/10.0;
                    timeCount++;
                    //lineFromFile = file.nextLine();
                    while(checkTimeGap(lineFromFile)){
                        ;
                    }
                }
            }
        }
        
//        for (int i = 0; i < actions.size(); i++){
//            System.out.println(i + ":");
//            for(int j = 0; j < actions.get(i).size(); j++)
//            System.out.println(actions.get(i).get(j));
//        }
        System.out.println("number of actions in file: " + (actionTimes.length/2));
        System.out.println("number of actions counted: " + actionCount);
        System.out.println("number of times in file: " + actionTimes.length);
        System.out.println("number of times went by: " + actionTimeCount);
        System.out.println("what is startrecording" +startRecording);
        
        createOutput(logDate, action, useLastKnownPos);
    }
    
    private String addMissingPositions(String output){
        String[] outputParts = output.split(" + ");
        if (numPlayers != outputParts.length -1 ){
            int playersInOutput = outputParts.length;
            for (int i = 0; i < numPlayers; i++){
                if (!output.contains(playerIDs[i])){
                    playersInOutput++;
                    output += " & " + (playersInOutput-1) +") " +  playerIDs[i] + "[";
                    for (int j = 0; j < lastKnownPositions[i].length; j++){
                        if (j == 0)
                            output += lastKnownPositions[i][j];
                        else
                            output += "," + lastKnownPositions[i][j];
                    }
                    output += ",0,x00]";
                    //System.out.println("WAS MISSING " + output);                    
                }
            }
        }
        output = putTagsInCorrectOrder(output);
        return output;
    }
    
    private String putTagsInCorrectOrder(String output){
        //get each tag and its co ordinates
        String[] parts = output.split(" & ");
        for (int i = 0; i < parts.length; i++){
            parts[i] = parts[i].trim();
        }
        
        //put tags in correct order
        String newOutput = "";
        for (int i = 0; i < playerIDs.length; i++){
            int indexOfID = -1;
            for (int j = 0; j < parts.length; j++){
                if (parts[j].contains(playerIDs[i])){
                    indexOfID = j;
                    break;
                }
                    
            }
            if (indexOfID == -1)
                System.out.println();
            parts[indexOfID] = 0 + parts[indexOfID].substring(1);
            
            if (i != playerIDs.length-1)
                newOutput += parts[indexOfID] + " & ";
            else
                newOutput += parts[indexOfID];
        }
        return newOutput;
    }
    
    private void updateLastPositions(String output){
        for (int i = 0; i < numPlayers; i++){
            if (output.contains(playerIDs[i])){
                for (int j = 0; j < 3; j++){

                    lastKnownPositions[i][j] = "-1";
                }
            }
        }
    }
    
    private double getTime(String currentTimeInfo){
        int decimalIndex = currentTimeInfo.indexOf('.');
        String currentTimeString = currentTimeInfo.substring(1, decimalIndex + 4);
        double currentTime = Double.parseDouble(currentTimeString);
        return currentTime;
    }
    
    private void storeTime(double currentTime){
        //double currentTime = getTime(currentTimeInfo);
        lastTime = currentTime;
    }
    
    private boolean checkTimeGap(String currentTimeInfo){
        double currentTime = getTime(currentTimeInfo);
        if (lastTime == 0)
            lastTime = currentTime;
        //System.out.println("last time: " + lastTime + ", current time: " + currentTime);
        if (lastTime + 0.110 < currentTime){
            addPositionsForMissingTimes(currentTime);
            //100 milliseconds has passed so increase time
            time = timeCount/10.0;
            timeCount++;
            //System.out.println(time);
            lastTime += 0.10;
            //System.out.println("incremented last time");
            //storeTime(lastTime);
            return true;
        }
        else{
            storeTime(currentTime);
            return false;
        }
    }
    
    private boolean checkTimeGap(double currentTime){
        System.out.println("last time: " + lastTime + ", current time: " + currentTime);
        if (lastTime + 0.110 < currentTime){
            System.out.println("there was a time gap");
            
            //lastTime += 0.1;
            //there has been a time gap so use last values by calling use last values
            //System.out.println("before if");
            if (hasStarted)
                addPositionsForMissingTimes(currentTime);
            //System.out.println("after if");
            //100 milliseconds has passed so increase time
            time = timeCount/10.0;
            timeCount++;
            lastTime += 0.1;
            //System.out.println("incremented last time");
            //storeTime(lastTime);
            return true;
        }
        else{
            storeTime(currentTime);
            return false;
        }
    }
    
    private void addPositionsForMissingTimes(double currentTime){
        //if the time is equal to the time in actionTimes then 
        //it is either the beginnging of an instance of an action
        if (actionTimes[actionTimeCount] == time){
            //System.out.println("match");
            //if an instance has already started then it is now
            //the end of the instance and increase actionTimeCount
            //to go to the next element in actionTimes (which will be
            //the start of the next instance)
            if (hasStarted){
                makeStop = true;
                //hasStarted = false;
                actionTimeCount++;
                //System.out.println("END OF INSTANCE, time = " + time);
            }
            //else if an instance hasnt already started then it is now
            //the beginning of an instance and increase actionTimeCount
            //to go to the next element in actionTimes (which will be the
            //end of this instance). Add new ArrayList to actions
            //to hold positios for this instance
            else{
                hasStarted  = true;
                actions.add(new ArrayList<String>());
                actionTimeCount++;
                actionCount++;
                //System.out.println("START OF INSTANCE, time = " + time);
                //System.out.println(lineFromFile);
            }
            //System.out.println("actiontime count: " + actionTimeCount);
        }
        
        if (hasStarted){
            //make the output for this time
            int playersInOutput = 0;
            String output = "";

            for (int i = 0; i < numPlayers; i++){
                    playersInOutput++;
                    if (i == 0)
                        output += (playersInOutput-1) +") " +  playerIDs[i] + "[";
                    else
                        output += " & " + (playersInOutput-1) +") " +  playerIDs[i] + "[";
                    for (int j = 0; j < lastKnownPositions[i].length; j++){
                        if (j == 0)
                            output += lastKnownPositions[i][j];
                        else
                            output += "," + lastKnownPositions[i][j];
                    }
                    output += ",0,x00]";
            }
            actions.get(actionCount-1).add(output);
            //checkTimeGap(currentTime, actionCount, hasStarted);
            
            if (makeStop == true){
                makeStop = false;
                hasStarted = false;
            }
        }
    }
    
    private void initialiseLastPositions(String[] tagIDs, boolean replaceWithUnknown){
        this.playerIDs = tagIDs;
        numPlayers = tagIDs.length;
        lastKnownPositions = new String[tagIDs.length][3];
        for (int i = 0; i < lastKnownPositions.length; i++){
            for (int j = 0; j < lastKnownPositions[i].length; j++)
                if (replaceWithUnknown){
                    lastKnownPositions[i][j] = "?";
                }
                else {
                    lastKnownPositions[i][j] = "-1";
                }
        } 
    }
    
    public void readCSVFile(String logDate, String action) throws FileNotFoundException{
        //load file with action times
        String fileName = "logs/" + logDate + "/" + action + ".csv";
        Scanner file = new Scanner(new File(fileName));
        //count number of lines
        int lines = 0;
        while (file.hasNextLine()) {
            lines++;
            file.nextLine();
        }

        //total number of times in the file
        actionTimes = new double[(lines-1)*2];

        int count = 0;
        file = new Scanner(new File(fileName));
        String lineFromFile = file.nextLine();
        while (file.hasNextLine())
        {
            lineFromFile = file.nextLine();    
            String parts[] = lineFromFile.split(",");
            double startTime = Double.parseDouble(parts[1]);
            startTime = Math.floor(startTime * 10)/10;
            double endTime = Double.parseDouble(parts[2]);
            endTime = Math.floor(endTime * 10)/10;
            actionTimes[count] = startTime;
            count++;
            actionTimes[count] = endTime;
            //actionTimes[count-1] = lineFromFile;
            count++;
        }
        
        
        
    }
    
    public void createOutput(String logDate, String action, boolean useLastKnownPos) throws IOException{
        String actionNum = action + "_";
        List<String> lines = new ArrayList<>();
        String output;

        //go through each action
        for (int i = 0; i < actions.size(); i++){
            output = actionNum + i;
            lines.add(output);
            output = "[";
            //create hashmap to contain each tags last known position
            Map <String, String> hm = new HashMap<String, String>();
            initialiseHashMapWithRecentPositions(hm, i);
            //initialise HashMap with each tags last known position

            //loop through milisecond for this action
            for(int j = 0; j < actions.get(i).size(); j++){
                String actionLine = actions.get(i).get(j);
                //put each tags location into array
                String[] actionLinesParts = actionLine.split(" & ");


                for (int k = 0; k < actionLinesParts.length; k++){
                    if(!actionLinesParts[k].contains("?") && !actionLinesParts[k].contains("-1")){
                        for(String id : playerIDs){
                            if(actionLinesParts[k].contains(id)){
                                hm.put(id, actionLinesParts[k]);
                            }
                        }
                        output += "," + positionsForLine(actionLinesParts[k]);
                    }
                    else {
                        boolean replaced = false;
                        for(String id : playerIDs) {
                            if (actionLinesParts[k].contains(id) && hm.get(id) != null && useLastKnownPos) {
                                output += "," + positionsForLine(hm.get(id));
                                replaced = true;
                            }
                        }
                        if (!replaced) {
                            output += "," + positionsForLine(actionLinesParts[k]);
                        }
                    }
                }
            }
            output += "]\n";
            lines.add(output);
        }
        
        Path file = Paths.get("logs/" + logDate+ "/" + action + "_output.txt");
        Files.write(file, lines, Charset.forName("UTF-8"));
    }

    public String positionsForLine(String line){
        //find position of opening bracket and third comma
        int openingBracketIndex = -1;
        int thirdCommaIndex = -1;
        int commasFound = 0;
        for (int i = 0; i < line.length(); i ++){
            if (line.charAt(i) == '['){
                openingBracketIndex = i;
            }
            if (line.charAt(i) == ','){
                commasFound++;
                if (commasFound == 3){
                    thirdCommaIndex = i;
                }
            }
        }
       // System.out.print("\n" + line);
        return line.substring(openingBracketIndex+1, thirdCommaIndex);
        
        //get substring from opening bracket to thrid comma as this is the 
        //z, y and z positions      
    }

    public void initialiseHashMapWithRecentPositions(Map map, int actionIndex){
        //look for the first time each tag has a position and add it to map

        //array used to mark when first pos for player is found
        int[] foundPos = new int[numPlayers];
        int foundPosCount = 0;

        //loop through each action to find first position for each tag
        //for (int i = 0; i < actions.size(); i++) {
            //loop
            for (int j = 0; j < actions.get(actionIndex).size(); j++) {
                String actionLine = actions.get(actionIndex).get(j);
                //put each tags location into array
                String[] actionLinesParts = actionLine.split(" & ");
                for (int k = 0; k < actionLinesParts.length; k++) {
                    if (!actionLinesParts[k].contains("?") && !actionLinesParts[k].contains("-1")) {
                        for (int l = 0; l < playerIDs.length; l++){
                            String id = playerIDs[l];
                            if (actionLinesParts[k].contains(id) && foundPos[l] == 0) {
                                map.put(id, actionLinesParts[k]);
                                foundPos[l] = 1;
                                foundPosCount++;
                                if (foundPosCount == numPlayers){
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        //}
        System.out.println();
    }

    Map <String, String> liveHM = new HashMap<String, String>();
    public void createOutput(String action, boolean useLastKnownPos) throws IOException{
        String actionNum = action + "_";
        List<String> lines = new ArrayList<>();
        String output;

        //go through each action
        for (int i = 0; i < actions.size(); i++){
            output = actionNum + i;
            lines.add(output);
            output = "[";
            //create hashmap to contain each tags last known position

            initialiseHashMapWithRecentPositions(liveHM, i);
            //initialise HashMap with each tags last known position

            //loop through milisecond for this action
            for(int j = 0; j < actions.get(i).size(); j++){
                String actionLine = actions.get(i).get(j);
                //put each tags location into array
                String[] actionLinesParts = actionLine.split(" & ");


                for (int k = 0; k < actionLinesParts.length; k++){
                    if(!actionLinesParts[k].contains("?") && !actionLinesParts[k].contains("-1")){
                        for(String id : playerIDs){
                            if(actionLinesParts[k].contains(id)){
                                liveHM.put(id, actionLinesParts[k]);
                            }
                        }
                        output += "," + positionsForLine(actionLinesParts[k]);
                    }
                    else {
                        boolean replaced = false;
                        for(String id : playerIDs) {
                            if (actionLinesParts[k].contains(id) && liveHM.get(id) != null && useLastKnownPos) {
                                output += "," + positionsForLine(liveHM.get(id));
                                replaced = true;
                            }
                        }
                        if (!replaced) {
                            output += "," + positionsForLine(actionLinesParts[k]);
                        }
                    }
                }
            }
            output += "]\n";
            lines.add(output);
        }

        Path file = Paths.get(action + "_output.txt");
        Files.write(file, lines, Charset.forName("UTF-8"));
    }

    public boolean generateActionPositionsForLiveClassification() throws FileNotFoundException, IOException{

        //initialise class atts
        //get start and end time of each instance of an action from csv file
        //and put it in actionTimes array
//        for (int i = 0; i < actionTimes.length; i++){
//            System.out.println(i + ": " + actionTimes[i]);
//        }
        initialiseClassAttributes();
        //initialiseLastPositions(tagIds, replaceWithUnknown);

        //read log file
//        numActions = actionTimes.length/2;
//        actions = new ArrayList<ArrayList<String>>(numActions);
//        startRecording = 0;
        String actionStart = action + " start";
        String actionEnd = action + " end";
         actions = new ArrayList<ArrayList<String>>();
        //the index currently at from the actionTime array eg pass 0 starts, pass 0 end, pass 1 start
//        actionTimeCount = 0;
        //the action instance number eg pass 0, pass 1, pass 2
//        actionCount = 0;
        //this indicates whether an instance of an action has started
//        hasStarted = false;
//        makeStop = false;
        //current line number
        int lineNumber = -1;
        //while the file has a next line and the end of the action hasnt been
        //reached yet

        while (fileIndex < fileLines.size()  && startRecording != 2 && actionTimeCount != actionTimes.length)
        {
            //System.out.println(time);
            //get the next line and increment current line number
            String lineFromFile = fileLines.get(fileIndex);
            fileIndex++;

            //if beginning of action set startRecording to 1
            if(lineFromFile.contains(actionStart))
            {
                startRecording = 1;
                indexOfActionStart = fileIndex;
                lineFromFile = fileLines.get(fileIndex);
                fileIndex++;
            }
            //if end of action set startRecording to 2
            if (lineFromFile.contains(actionEnd))
            {
                startRecording = 2;
                break;
            }

            //if start of action has begun then get positions of each instance
            //of an action and put it in actions ArrayList
            if (startRecording == 1){
                //if the time is equal to the time in actionTimes then
                //it is either the beginnging of an instance of an action
                if (actionTimes[actionTimeCount] == time){
                    //System.out.println(time);
                    //if an instance has already started then it is now
                    //the end of the instance and increase actionTimeCount
                    //to go to the next element in actionTimes (which will be
                    //the start of the next instance)
                    if (hasStarted){
                        makeStop = true;
                        hasStarted = false;
                        actionTimeCount++;
                    }
                    //else if an instance hasnt already started then it is now
                    //the beginning of an instance and increase actionTimeCount
                    //to go to the next element in actionTimes (which will be the
                    //end of this instance). Add new ArrayList to actions
                    //to hold positios for this instance
                    else{
                        hasStarted  = true;
                        //****************************************************************************************************
                        actions.add(new ArrayList<String>());
                        actionTimeCount++;
                        actionCount++;
                    }
                }
                //if an instance has started then add the lines for this
                //0.1 second to the ArrayList
                if (hasStarted){
                    if (lineFromFile.charAt(0) == '['){
                        lineFromFile = fileLines.get(fileIndex);
                        fileIndex++;
                    }
                    String line = lineFromFile;
                    //get next lines that are part of this 0.1 second
                    while (fileIndex < fileLines.size()){
                        lineFromFile = fileLines.get(fileIndex);
                        fileIndex++;
                        if (actionTimes[1] == time || lineFromFile.contains(actionEnd))
                        {
                            //System.out.println("FOUND THE END");
                            startRecording = 2;
                            //System.out.println(lineFromFile);
                            break;
                        }
                        //System.out.println(lineFromFile);
                        if (lineFromFile.length() != 0){
                            line += " & " + lineFromFile;
                        }
                        else{
                            //go back to previous line
                            //goToPreviousLine(file, lineNumber);
                            //exit loop
                            break;
                        }
                        lineNumber++;
                    }
                    //add line to the current instance
                    //updateLastPositions(line);
                    line = addMissingPositions(line);
                    actions.get(actionCount-1).add(line);
                    //System.out.println("actioncount: " + (actionCount-1));
                    lineFromFile = fileLines.get(fileIndex);
                    fileIndex++;
                    if (lineFromFile.contains(actionEnd))
                    {
                        //System.out.println("FOUND THE END");
                        startRecording = 2;
                        //System.out.println(lineFromFile);
                        break;
                    }

                    if (makeStop == true){
                        hasStarted = false;
                        makeStop = false;
                    }
                }

                //100 milliseconds has passed so increase time
                if (lineFromFile.length() > 0 && lineFromFile.charAt(0) == '['){
                    time = timeCount/10.0;
                    timeCount++;
                    //lineFromFile = file.nextLine();
                    while(actionTimeCount < actionTimes.length && checkTimeGap(lineFromFile)){

                        if (actionTimeCount >= actionTimes.length) {
                            System.out.println(time - 0.1);
                            break;
                        }
                    }
//                    if (actionTimeCount >= actionTimes.length) {
//                        System.out.println(time - 0.1);
//                    }
                }
            }
        }

//        for (int i = 0; i < actions.size(); i++){
//            System.out.println(i + ":");
//            for(int j = 0; j < actions.get(i).size(); j++)
//            System.out.println(actions.get(i).get(j));
//        }
//        System.out.println("number of actions in file: " + (actionTimes.length/2));
//        System.out.println("number of actions counted: " + actionCount);
//        System.out.println("number of times in file: " + actionTimes.length);
//        System.out.println("number of times went by: " + actionTimeCount);
//        System.out.println("what is startrecording" +startRecording);

        createOutput(action, useLastKnownPos);
        if (actionCount > 0){
            System.out.println("will return true");
            return true;
        }
        else{
            System.out.println("will return false");
            return false;
        }

    }

    public void initialiseClassAttributes(){
        //time = 0.0;
        //timeCount = 0;
        //lastTime = 0.000;
        actionTimeCount = 0;
        actionCount = 0;
        //hasStarted = false;
        //makeStop = false;
    }

}
