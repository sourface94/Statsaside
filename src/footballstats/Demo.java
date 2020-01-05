package footballstats;

import java.io.DataInputStream;

public class Demo {

    public void read(DataInputStream ins) {
        try {
            while(true) {
                if(ins.available() > 0) {
                    //BufferedReader reader = new BufferedReader(new InputStreamReader(ins));
                    //System.out.println(reader.readLine());
                    System.out.println(ins.readLine());
                }
                else {
                    Thread.sleep(200);
                }
            }
        }
        catch(Exception e) {
            e.printStackTrace();
        }
    }
}
