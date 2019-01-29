//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include <random>
#include <utility>
#include <array>
#include <vector>
#include "torus.h"
#include "monophonie.h"
#include "chords.h"
#include "GPIOClass.h"

using namespace std;


void input(int* nums) {

    //      GPIO SETUP
    //  --- input
    GPIOClass val0 = GPIOClass("2");
    GPIOClass val1 = GPIOClass("3");
    GPIOClass val2 = GPIOClass("4");
    GPIOClass val3 = GPIOClass("17");
    GPIOClass val4 = GPIOClass("27");
    GPIOClass val5 = GPIOClass("22");
    GPIOClass val6 = GPIOClass("10");
    GPIOClass val7 = GPIOClass("9");
    GPIOClass val8 = GPIOClass("11");
    GPIOClass val9 = GPIOClass("5");
    GPIOClass val10 = GPIOClass("6");
    GPIOClass val11 = GPIOClass("13");

    //  --- output
    GPIOClass led0 = GPIOClass("19");
    GPIOClass led1 = GPIOClass("26");
    GPIOClass led2 = GPIOClass("18");
    GPIOClass led3 = GPIOClass("23");
    GPIOClass led4 = GPIOClass("24");
    GPIOClass led5 = GPIOClass("25");
    GPIOClass led6 = GPIOClass("8");
    GPIOClass led7 = GPIOClass("7");
    GPIOClass led8 = GPIOClass("12");
    GPIOClass led9 = GPIOClass("16");
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
    }


    //  WAIT FOR INPUT
    vector<array<GPIOClass, 2>> cpy_buttons {buttons};
    while (true) {
        int idx{0};
        for (auto button : cpy_buttons) {
            if (button[0].getval_gpio() == "0") {
                button[1].setval_gpio("0");
                cpy_buttons.erase(cpy_buttons.begin() + idx);
            } else {
                idx++;
            }
        }
    }


    // UNEXPORT EVERYTHING
    val0.unexport_gpio();
    val1.unexport_gpio();
    val2.unexport_gpio();
    val3.unexport_gpio();
    val4.unexport_gpio();
    val5.unexport_gpio();
    val6.unexport_gpio();
    val7.unexport_gpio();
    val8.unexport_gpio();
    val9.unexport_gpio();
    val10.unexport_gpio();
    val11.unexport_gpio();

    led0.unexport_gpio();
    led1.unexport_gpio();
    led2.unexport_gpio();
    led3.unexport_gpio();
    led4.unexport_gpio();
    led5.unexport_gpio();
    led6.unexport_gpio();
    led7.unexport_gpio();
    led8.unexport_gpio();
    led9.unexport_gpio();
    led10.unexport_gpio();
    led11.unexport_gpio();
}



int main(int argc, char* argv[]) {
/*
    if (argc - 1 != 12) {
        throw runtime_error("Needs 12 Numbers (" + to_string(argc - 1) + " given)");
    }
*/


    //save into new array (as integers)
    int numbers[12]{};

    input(numbers);

    for (int i{1}; i <= 12; i++) {
        numbers[i - 1] = stoi((string)argv[i]);
    }

    string dbwriter = "";
    dbwriter = (string)argv[1];
    for (int i{2}; i <= 12; i++) {
        dbwriter += "," + (string)argv[i];
    }


    string writer = "../database/DBWriter/build/bin/dbwriter " + dbwriter;
    system(writer.c_str());

    Torus torus = Torus(numbers);

    int anschlussklang = torus.move_start();
    //cout << "anschlussklang: " << anschlussklang << endl;
    //torus.shift = 0;

    //monophonie(torus.start, torus.shift, anschlussklang);
    //chords(torus.start, torus.shift, anschlussklang);
    //notes(torus.start, torus.shift, anschlussklang);
    monophonie_and_chords(torus.start, torus.shift, anschlussklang);


   /* cout << "  _______       _____ _        _             \n"
            " |__   __|     / ____| |      (_)            \n"
            "    | | ___   | (___ | |_ _ __ _ _ __   __ _ \n"
            "    | |/ _ \\   \\___ \\| __| '__| | '_ \\ / _` |\n"
            "    | | (_) |  ____) | |_| |  | | | | | (_| |\n"
            "    |_|\\___/  |_____/ \\__|_|  |_|_| |_|\\__, |\n"
            "                                        __/ |\n"
            "                                       |___/ " << endl;

    cout << torus.to_string() << endl;
*/

}
