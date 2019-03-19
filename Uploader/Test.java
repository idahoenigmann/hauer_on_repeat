import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;

public class Test {
    public static void main(String[] argv) throws Exception {


        String init = "bash init.sh";
        String append = "bash append.sh";
        String finalize = "bash finalize.sh";
        String status = "bash status.sh";
        String save = "bash save.sh";

        //init
        String totalBytes = run("wc -c " + argv[0]).split(" ")[0].trim();

        writeToFile("twurl -X POST -H upload.twitter.com \"/1.1/media/upload.json?additional_owners=1072433162368765952\" -d \"command=INIT&media_type=video/mp4&media_category=tweet_video&total_bytes=" + totalBytes + "\"", "init.sh");
        String mediaID = parseMap(run(init)).get("\"media_id\"");
        System.out.println("Init-Phase done!");
        System.out.println("MediaID: " + mediaID);

        //append
        run("mkdir splitFolder");
        run("split -b 1m "+argv[0]+" splitFolder/");



        File[] listOfFiles = new File("splitFolder").listFiles();

        String[] files = new String[listOfFiles.length];
        for (int i=0; i<files.length; i++) {
            files[i] = listOfFiles[i].getName();
        }
        Arrays.sort(files);

        String toWrite="";
        int cnt=0;
        for (String i : files) {
            toWrite += "twurl -X POST -H upload.twitter.com \"/1.1/media/upload.json\" -d \"command=APPEND&media_id="+mediaID+"&segment_index="+cnt+"\" --file splitFolder/"+i+" --file-field \"media\"\n";
            cnt++;
        }
        writeToFile(toWrite, "append.sh");




        run(append);
        System.out.println("Append-Phase done!");
        //finalize

        writeToFile("twurl -X POST -H upload.twitter.com \"/1.1/media/upload.json\" -d \"command=FINALIZE&media_id="+mediaID+"&allow_async=true\"", "finalize.sh");


        run(finalize);
        System.out.println("Finalize-Phase done!");
        //status


        //HashMap<String, String> progress;

        writeToFile("twurl -X GET -H upload.twitter.com \"/1.1/media/upload.json?command=STATUS&media_id="+mediaID+"\"", "status.sh");


        while (!parseMap(run(status)).get("\"progress_percent\"").equals("100")) {
            System.out.println("Progress: " + parseMap(run(status)).get("\"progress_percent\""));
            System.out.println("[Sleep]");
            TimeUnit.SECONDS.sleep(1);
        }
        System.out.println("Succeeded!!");
        //System.out.println(parseMap(run(status)).get("\"progress_percent\""));

        //save
        writeToFile("twurl \"/1.1/statuses/update.json\" -d \"batch_mode=off&media_ids="+mediaID+"&status=test\"", "save.sh");


        String link = "https://twitter.com/HauerOnRepeat/status/" + parseMap(run(save)).get("\"id\"");
        System.out.println(link);


        Process proc = Runtime.getRuntime().exec("qrencode " + link + " -o qrcode.png");
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String result="";
        String line = "";
        while((line = reader.readLine()) != null) {
            System.out.println(line);
        }
        proc.waitFor();

        //after all
        run("rm init.sh");
        run("rm append.sh");
        run("rm finalize.sh");
        run("rm status.sh");
        run("rm save.sh");
        run("rm splitFolder -r");
    }


    private static void writeToFile(String msg, String file) throws Exception {
        BufferedWriter writer = new BufferedWriter(new FileWriter(file));
        writer.write(msg);
        writer.close();
    }

    private static HashMap<String, String> parseMap(String source) {

        source = source.replace("{", "");
        source = source.replace("}", "");
        source = source.replace("\n", "");

        HashMap<String, String> toReturn = new HashMap<String, String>();
        for (String i : source.split(",")) {
            try {
            toReturn.put(i.split(":")[0], i.split(":")[1]);
        } catch (Exception e) {} //do nothing
        }

        return toReturn;
    }

    private static String run(String cmd) throws Exception {
        Process proc = Runtime.getRuntime().exec(cmd);
        BufferedReader reader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
        String result="";
        String line = "";
        while((line = reader.readLine()) != null) {
            result = line + "\n";
        }
        proc.waitFor();
        return result;
    }

    private static HashMap<String, String> map = new HashMap<String, String>();
}
