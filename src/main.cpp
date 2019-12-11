//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include <random>
#include <utility>
#include <array>
#include <vector>
#include <limits.h>
#include <unistd.h>
#include <time.h>
#include "torus.h"
#include "monophonie.h"
#include "chords.h"
#include "GPIOClass.h"
#include "files.h"

using namespace std;


bool in(int num, int* d) {
    for (int i{0}; i < 12; i++) {
        if (d[i] == num) return true; 
    }
    return false;
}

bool checkTime(time_t begin, double timespan) {
    if (begin) {
        if (time(NULL) - begin >= timespan)
            return true;
    }
    return false;
}

void input(int* nums) {
    cout << "GPIO Setup" << endl;

    //      GPIO SETUP
    //  --- input
    GPIOClass val0 = GPIOClass("2");
    GPIOClass val1 = GPIOClass("3");
    GPIOClass val2 = GPIOClass("4");
    GPIOClass val3 = GPIOClass("17");
    GPIOClass val4 = GPIOClass("27");
    GPIOClass val5 = GPIOClass("22");
    GPIOClass val6 = GPIOClass("5"); //10
    GPIOClass val7 = GPIOClass("9");
    GPIOClass val8 = GPIOClass("11");
    GPIOClass val9 = GPIOClass("10"); //5
    GPIOClass val10 = GPIOClass("6");
    GPIOClass val11 = GPIOClass("13");

    //  --- output
    GPIOClass led0 = GPIOClass("19");
    GPIOClass led1 = GPIOClass("26");
    GPIOClass led2 = GPIOClass("18");   
    GPIOClass led3 = GPIOClass("23");
    GPIOClass led4 = GPIOClass("24");
    GPIOClass led5 = GPIOClass("25");
    GPIOClass led6 = GPIOClass("16"); //8
    GPIOClass led7 = GPIOClass("7");
    GPIOClass led8 = GPIOClass("12");
    GPIOClass led9 = GPIOClass("8"); //16
    GPIOClass led10 = GPIOClass("20");
    GPIOClass led11 = GPIOClass("21");


    vector<array<GPIOClass, 2>> buttons {{val0, led0}, {val1, led1}, {val2, led2},
                              {val3, led3}, {val4, led4}, {val5, led5},
                              {val6, led6}, {val7, led7}, {val8, led8},
                              {val9, led9}, {val10, led10}, {val11, led11}};


    for (auto button : buttons) {
        //INPUT
        button[0].export_gpio();
        button[0].setdir_gpio("in");

        //OUTPUT
        button[1].export_gpio();
        button[1].setdir_gpio("out");
        usleep(100000);
        button[1].setval_gpio("1");
    }


    cout << "GPIO Setup complete!" << endl << "Wait for Input" << endl;

    time_t time_lpress {};

    //  WAIT FOR INPUT
    //vector<string> pressed {};
    File cntfile = File("../web/cnt");
    cntfile.write(std::to_string(12), "txt");

    int index = 0;
    while (in(-1, nums)) {
        for (int i{0}; i < buttons.size(); i++) {
            if (buttons[i][0].getval_gpio() == "1" && !in(i, nums)) {
                buttons[i][1].setval_gpio("0");
                nums[index] = i;
                cout << "Button " << i << " pressed!" << endl;
                time(&time_lpress);
                cntfile.write(std::to_string(11 - index), "txt");
                index++;
            }
        }

        if (checkTime(time_lpress, 60000)) return;
    }
}

int main(int argc, char* argv[]) {

    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {

        //save into new array (as integers)
        int numbers[12]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

        input(numbers);

        File cntfile = File("../web/cnt");
        cntfile.write(std::to_string(12), "txt");

        //use terminal to input numbers
        /*for (int i{0}; i < 12; i++) {
            cin >> numbers[i];
            cntfile.write(std::to_string(11 - i), "txt");
        }*/

        //reset after timeout
        if (in(-1, numbers)) continue;

        string dbwriter = "";
        dbwriter = to_string(numbers[0]);
        for (int i{1}; i < 12; i++) {
            dbwriter += "," + to_string(numbers[i]);
        }

        string writer = "sqlite3 -line ../database.db \"insert into saves values (datetime(), '" + dbwriter + "')\"";
	    cout << writer << endl;
        system(writer.c_str());

        Torus torus = Torus(numbers);
        int delta = torus.move_start();
        cout << "delta: " << delta << endl;

        File file = File("../web/example");
        file.write(torus.to_string(), "xml");

        notes(torus.start, torus.shift);
        auto res_c = chords(torus.start, torus.shift, delta);
        monophonie_and_chords(torus.start, torus.shift, delta);

        //auto res_m = monophonie(torus.start, torus.shift, delta, false);

        /*cout << "chords" << endl;
        for(auto r : res_c) {
            for (auto e : r) {
                cout << e << " ";
            }
            cout << endl;
        }

        cout << "monophonie" << endl;
        for(auto r : res_m) {
            for (auto e : r) {
                cout << e << " ";
            }
            cout << endl;
        }*/

        usleep(63000000);

    }
#pragma clang diagnostic pop

}
