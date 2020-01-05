/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 *//*

package football_stats;

import java.io.FileReader;
import java.util.Random;
import timeseriesweka.classifiers.ensembles.elastic_ensemble.DTW1NN;
import weka.classifiers.Classifier;
import weka.classifiers.bayes.NaiveBayes;
import weka.classifiers.functions.LibSVM;
import weka.classifiers.functions.LinearRegression;
import weka.classifiers.functions.Logistic;
import weka.classifiers.functions.MultilayerPerceptron;
import weka.classifiers.functions.SMO;
import weka.classifiers.lazy.DTW_1NN;
import weka.classifiers.lazy.kNN;
import weka.classifiers.meta.RotationForest;
import weka.classifiers.trees.RandomForest;
import weka.core.Instance;
import weka.core.Instances;

*/
/**
 *
 * @author natha
 *//*

public class Experiments {
    
    public static void main(String[] args) throws Exception{
        double[] accuracies = new double[7];
        //read in file
        //String filePath = "C:/Users/natha/Documents/bell fen/Football Stat Tracking/arffs/pass_dribble_2.arff";
        String filePath = "C:/Users/natha/Documents/bell fen/Football Stat Tracking/arffs/actions_minus_one.arff";
        Instances inst = loadData(filePath);
        inst.setClassIndex(inst.numAttributes()-1);
        for (int i = 0; i < 1; i++){
            System.out.println("class: " + inst.instance(0).classValue());
            inst.randomize(new Random(i));
            int numInstancesTrain = inst.numInstances()/2;
            System.out.println(numInstancesTrain);
            Instances train = new Instances(inst, 0, numInstancesTrain);
            System.out.println(train.numInstances());
            Instances test = new Instances(inst, numInstancesTrain, inst.numInstances()-(numInstancesTrain));
            System.out.println(test.numInstances());

//            String trainFilePath = "C:/Users/natha/Documents/bell fen/Football Stat Tracking/arffs/actions_train.arff";
//            Instances train = loadData(trainFilePath);
//            String testFilePath = "C:/Users/natha/Documents/bell fen/Football Stat Tracking/arffs/actions_test.arff";
//            Instances test = loadData(testFilePath);

            train.setClassIndex(train.numAttributes()-1);
            test.setClassIndex(test.numAttributes()-1);

            //train and test classifier and return accuracy
            RandomForest randf = new RandomForest();
            double rfAcc = wekaClassifiers(randf, train, test);
            System.out.println("Random Forest: " + rfAcc + "/" + test.numInstances());
            accuracies[0] += rfAcc;
            
            NaiveBayes nb = new NaiveBayes();
            double nbAcc = wekaClassifiers(nb, train, test);
            System.out.println("Naive Bayes: " + nbAcc + "/" + test.numInstances());
            accuracies[1] += nbAcc;
//            
            RotationForest rotf = new RotationForest();
            
            double rotfAcc = wekaClassifiers(rotf, train, test);
            System.out.println("Rotation Forest: " + rotfAcc + "/" + test.numInstances());
            accuracies[2] += rotfAcc;
            
            SMO smo = new SMO();
            double smoAcc = wekaClassifiers(smo, train, test);
            System.out.println("SMO : " + smoAcc + "/" + test.numInstances());
            accuracies[3] += smoAcc;
//            
//            smo = new SMO();
//            smo.setC(1);
//            smoAcc = wekaClassifiers(smo, train, test);
//            System.out.println("SMO 1 : " + smoAcc + "/" + test.numInstances());
//            accuracies[3] += smoAcc;
//            
//            smo = new SMO();
//            smo.setC(0.1);
//            smoAcc = wekaClassifiers(smo, train, test);
//            System.out.println("SMO 0.1 : " + smoAcc + "/" + test.numInstances());
//            accuracies[3] += smoAcc;
//            
//            smo = new SMO();
//            smo.setC(0.001);
//            smoAcc = wekaClassifiers(smo, train, test);
//            System.out.println("SMO 0.001 : " + smoAcc + "/" + test.numInstances());
//            accuracies[3] += smoAcc;
//            
//            smo = new SMO();
//            smo.setC(0.0001);
//            smoAcc = wekaClassifiers(smo, train, test);
//            System.out.println("SMO 0.0001 : " + smoAcc + "/" + test.numInstances());
//            accuracies[3] += smoAcc;
//            
//            smo = new SMO();
//            smo.setC(0.00001);
//            smoAcc = wekaClassifiers(smo, train, test);
//            System.out.println("SMO 0.00001 : " + smoAcc + "/" + test.numInstances());
//            accuracies[3] += smoAcc;
           

            MultilayerPerceptron mlp = new MultilayerPerceptron();
            double mlpAcc = wekaClassifiers(mlp, train, test);
            System.out.println("MLP: " + mlpAcc + "/" + test.numInstances());
            accuracies[4] += mlpAcc;

            Logistic logistic = new Logistic();
            double logAcc = wekaClassifiers(logistic, train, test);
            System.out.println("Logistic: " + logAcc + "/" + test.numInstances());
            accuracies[5] += logAcc;

            LibSVM libSVM = new LibSVM();
            double libsvmAcc = wekaClassifiers(libSVM, train, test);
            System.out.println("LibSVM: " + libsvmAcc + "/" + test.numInstances());
            accuracies[6] += libsvmAcc;
        }
        
        for (int i = 0; i < accuracies.length; i++){
            accuracies[i] /= 11;
        }
        System.out.println("---------------------------------------------------------------------------------------");
        
        System.out.println("Random Forest Avg Accuracy: " + accuracies[0] + "/20");
        System.out.println("Naive Bayes Avg Accuracy: " + accuracies[1] + "/20");
        System.out.println("Rotation Forest Avg Accuracy: " + accuracies[2] + "/20");
        System.out.println("SMO Avg Accuracy: " + accuracies[3] + "/20");
        System.out.println("MLP Avg Accuracy: " + accuracies[4] + "/20");
        System.out.println("Logistic Avg Accuracy: " + accuracies[5] + "/20");
        System.out.println("LibSVM Avg Accuracy: " + accuracies[6] + "/20");       
    }
    
    public static double wekaClassifiers(Classifier c, Instances train, Instances test) throws Exception{
        c.buildClassifier(train);
        int count = 0;
        for (Instance i : test){
            double res = c.classifyInstance(i);
            if (res == i.classValue())
                count++;
            else
            {
                System.out.println("real: " + i.classValue() + " pred: " + res);
            }
            
        }
        //return (double)count/test.numInstances();
        return count;
    }
    
    public void attributeSelectionWekaClassifiers(Classifier c){
        
    }
    
    
    public static Instances loadData(String filePath){
        Instances i = null;
        try{
            FileReader reader = new FileReader(filePath);
            i = new Instances(reader);
        }
        catch(Exception e){
            System.out.println("Exception caught:" + e);
        }
        return i;
    }
}

*/
