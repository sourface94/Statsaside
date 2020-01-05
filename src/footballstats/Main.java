package footballstats;/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.*;

/**
 *
 * @author natha
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws FileNotFoundException, IOException, Exception {
//        System.out.println("Working Directory = " +
//             System.getProperty("user.dir"));
//          String[] actions = {"tackle", "pass", "inaccurateP", "dribble", "dribble2"};
        String[] actions = {"pass_251118"};
        //     String[] tagIDs = {"0B3A", "921E", "59AD"};
//921e = ball
        // these are the arrays for the second logfile / set of data
        String[] tagIDs = {"41AA", "88B4", "CC03"};  //41aa = ball
        PosLogToArffFast pos = new PosLogToArffFast();
//        pos.readFile("100219","actions_100219", tagIDs, false, true);
        //PosLogToArff pos = new PosLogToArff();
        RealTimeProcessing rtp = new RealTimeProcessing(tagIDs,"100219.txt", 10);
        rtp.liveClassificationAnalysis();
//        String[] actions = {"pass2", "inaccurateP2"};

 //       for (String action : actions) {
//          PosLogToArff pos = new PosLogToArff();
          //pos.readFile("100219","actions_100219", tagIDs, false, true);
//////              //String filePath = action + "_output.txt";
//            ARFFBuilder arff = new ARFFBuilder("pass_251118_output no extension.txt", false, tagIDs.length);
//            LogSummarisation summarisation = new LogSummarisation(tagIDs, 5.0, arff);
//            summarisation.readOuputFile("combined_actions_251118_output.txt");
////        liveClassification()
//       }
            //   mergeOutputs(actions, "_output.txtPossesion2.txt");
            //ARFFBuilder arff = new ARFFBuilder("pass_251118_output no extension.txt", false, tagIDs.length);
            //arff.createArffFile(true);
            // Experiments.runExperiments();;
//        TimeWindow t = new TimeWindow();
//        t.changeInPossession("pass_output.txt");
//              LogSummarisation summarisation = new LogSummarisation(tagIDs, 1.40);
//             summarisation.readOuputFile("pass_output.txt");

        //}
    }

    public static void mergeOutputs(String[] actions, String output) {
        String firstFile = actions[0] + output;
        String destination = "newcombinedPossesion2_output.txt";


        try (FileWriter fw = new FileWriter(destination, true);
             BufferedWriter bw = new BufferedWriter(fw);
             PrintWriter out = new PrintWriter(bw)) {
            for (String action : actions) {
                String filePath = action + output;
                FileReader fr = new FileReader(filePath);
                BufferedReader br = new BufferedReader(fr);

                String line = "";
                while ((line = br.readLine()) != null) {
                    out.println(line);
                }
            }
        } catch (IOException e) {
            //exception handling left as an exercise for the reader
        }


    }



    }
    

