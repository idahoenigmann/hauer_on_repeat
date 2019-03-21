import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.*;
import java.util.HashMap;
import java.util.Map;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.File;
import java.util.Arrays;
import java.util.concurrent.TimeUnit;
import java.util.*;
import java.nio.file.Files;

public class SSH {
    public static void main(String[] argv) throws Exception {

        //String cmd="ssh mani@mani.kubu.at 'cd Uploader; bash complete.sh monophonie.mp3 monophonie.pdf' > erg.txt";
        //run(cmd);


        File file = new File("erg.txt");
        lines = Files.readAllLines(file.toPath());

        String url = lines.get(lines.size() - 1);


        run("qrencode -o qrcode.png " + url);
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

    private static List<String> lines;

}
