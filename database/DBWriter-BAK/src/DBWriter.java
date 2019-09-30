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
        input = calc(input);

        conn.addEntry(rotate(input).source, rotate(input).delta);
        System.exit(exitCode);
    }

    //11,7,6,3,10,5,2,1,8,9,4,0

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

    private static String calc(String source) { //processes the input data
        String[] arr = source.split(",");
        Integer[] erg = new Integer[12];

        int after;
        for (int i=0; i<12; i++) {
            if (i+1 > 11) {
                after = 0;
            } else {
                after = i+1;
            }

        erg[i] = (Integer.parseInt(arr[after]) - Integer.parseInt(arr[i])) % 12;

        }

        String toReturn="";
        for (int e : erg) {
            toReturn += e + ",";
        }

        toReturn = toReturn.substring(0, toReturn.length() - 1);
        return toReturn;

    }

    private static RestultTuple rotate(String source) {
        int acc=12;
        String[] arr = source.split(",");
        RestultTuple res = new RestultTuple("", 12);
        int pos=0;

        for (int i=0; i<12; i++) {
            if (Integer.parseInt(arr[i]) < acc) {
                acc = Integer.parseInt(arr[i]);
                pos = i;
            }
        }

        String[] rotated = new String[12];
        int newPos;

        for (int i=0; i<12; i++) {
            newPos = i - pos;
            if (newPos < 0) {
                newPos = 12 + newPos;
            }

            rotated[newPos] = arr[i];
        }

        String moved="";
        for(String i : rotated) {
            moved += i + ",";
        }
        moved = moved.substring(0, moved.length() - 1);
        res.source = moved;
        res.delta = pos;

        return res;
    }


    private static LinkedList<String> list = new LinkedList<String>();
    private static DBConn conn;
    private static int exitCode;
}

final class RestultTuple {
    RestultTuple(String source, int delta) {
        this.source = source;
        this.delta = delta;
    }

    public String source;
    public int delta;
}
