import java.util.*;

/*
Exit-Code: 98 .. [ERROR] kein Input angegeben
Exit-Code: 99 ..[ERROR] zu viele Parameter angegeben
Exit-Code: 96 Der String ist nicht 25 Zeichen lang
Exit-Code: 95 Der String enthält falsche Zahlen!
Exit-Code: 100 .. Es wurde nur der Input angegeben
Exit-Code: 101 .. Es wurde zusätzlich noch der Path der DB angegeben
*/


class DBWriter {
    public static void main(String[] argv) {
        switch (argv.length) {
            case 0:
                System.out.println("Es wurde kein Input angegeben!");
                System.exit(98);
                break;
            case 1:
                conn = new DBConn();
                exitCode = 100;
                break;
            case 2:
                conn = new DBConn(argv[1]);
                exitCode = 101;
                break;
            default:
                System.out.println("Es wurden zu viele Parameter angegeben!");
                System.exit(99);
        }


        String input = argv[0];

        check(input);
        input = rotate(input);
        System.out.println(input);
        check(input);

        conn.addEntry(input);
        System.exit(exitCode);
    }

    //0,1,2,3,4,5,6,7,8,9,10,11

    private static void check(String source) { //checks if the input is correct

        list.addLast("0");
        list.addLast("1");
        list.addLast("2");
        list.addLast("3");
        list.addLast("4");
        list.addLast("5");
        list.addLast("6");
        list.addLast("7");
        list.addLast("8");
        list.addLast("9");
        list.addLast("10");
        list.addLast("11");

        int quoteCnt=0;

        if (source.length() != 25) {
            System.out.println("String ist nicht 25 Zeichen lang!");
            System.exit(96);
        }

        for (char i : source.toCharArray()) {
            if (i == '\u002C') {
                quoteCnt++;
            }
        }

        if (quoteCnt != 11) {
            System.out.println("Falsche Anzahl an Beistrichen!");
            System.exit(97);
        }

        for (String i : source.split(",")) {
            if (!list.remove(i)) {
                System.out.println("Falsche Zahl enthalten!");
                System.exit(95);
            }
        }
    }

    private static String rotate(String source) { //rotates the input that it starts with a 0

        String[] arr = source.split(",");
        String[] ergArr = new String[12];
        int zeroPos=0;
        // [3, 0, 1, 2] [0,1,2,3]

        if (arr[0] != "0") {
            for (int i=0; i < 12; i++) {
                if (arr[i].equals("0")) {
                    zeroPos = i;
                    break;
                }
            }
            int arrInt=0;
            for (int i=0; i < 12; i++) {
                arrInt = i + zeroPos;
                if (arrInt > 11) {
                    arrInt = arrInt - 12;
                }
                ergArr[i] = arr[arrInt];
            }
            String toReturn="";
            for (String e : ergArr) {
                toReturn += e + ",";
            }

            toReturn = toReturn.substring(0, toReturn.length() - 1);
            return toReturn;
        } else {
            String toReturn="";
            for (String i : arr) {
                toReturn += i + ",";
            }
            toReturn = toReturn.substring(0, toReturn.length() - 1);
            return toReturn;
        }
    }

    private static LinkedList<String> list = new LinkedList<String>();
    private static DBConn conn;
    private static int exitCode;
}
