package footballstats;

import java.io.IOException;
import java.util.ArrayList;

public class TimeWindow {

    public static String[] tagIDs = {"41AA", "88B4", "CC03"};  //41aa = ball

    public static ArrayList<ArrayList<Double>> changeInPossession(String fileName) throws IOException {
        ArrayList<ArrayList<String>> possessionChanges = new ArrayList<ArrayList<String>>();
        ArrayList<ArrayList<Double>> times = new ArrayList<ArrayList<Double>>();
        //find if there has been a change in possesion

        //for each millisecond check who the ball is closest to
        LogSummarisation summarisation = new LogSummarisation(tagIDs, 2.5);

        ArrayList<String> possessionData = summarisation.createPossessionData(fileName);

        for (int i = 0; i < possessionData.size(); i++){
            possessionChanges.add(new ArrayList<>());
            times.add(new ArrayList<>());
            String tagWithPossesion = "";
            String[] parts = possessionData.get(i).split(",");
            parts[parts.length-1] = parts[parts.length-1].replace("]", "");
            //find who has possession, we know someone has possession if they are near the ball for at least 0.3 seconds
            for (int j = 1; j < parts.length - 2; j++){
                //if a player has possession and it is a different player to who previously had possession
                //this wont recognise if a player is making a dribble and has knocked the ball far ahead of themself.
                //this can be improved to know if possession has changed to someone on same team or different team
                //and this can be used to limit the number of classifications considered as possible
//                if (parts[j].equals(parts[j+1]) && parts[j].equals(parts[j+2]) && !parts[j].equals(tagWithPossesion)){
//                    tagWithPossesion = parts[j];
//                    possessionChanges.get(i).add(parts[j]);
//                    double currentTime = j - 1;
//                    times.get(i).add(currentTime);
//                }
                if (!parts[j].equals(tagWithPossesion)){
                    tagWithPossesion = parts[j];
                    possessionChanges.get(i).add(parts[j]);
                    double currentTime = j - 1;
                    times.get(i).add(currentTime);
                }
            }
        }
        System.out.println();


        //
        //return the times between where possession changes
        //if ball changes possession from one player to another then at least one action has taken place so
        //classify the time windows in 'times; to find the actions that took place
        return times;
    }
}
