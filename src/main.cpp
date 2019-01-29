//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include <random>
#include <utility>
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

    val0.export_gpio();
    val1.export_gpio();
    val2.export_gpio();
    val3.export_gpio();
    val4.export_gpio();
    val5.export_gpio();
    val6.export_gpio();
    val7.export_gpio();
    val8.export_gpio();
    val9.export_gpio();
    val10.export_gpio();
    val11.export_gpio();

    val0.setdir_gpio("in");
    val1.setdir_gpio("in");
    val2.setdir_gpio("in");
    val3.setdir_gpio("in");
    val4.setdir_gpio("in");
    val5.setdir_gpio("in");
    val6.setdir_gpio("in");
    val7.setdir_gpio("in");
    val8.setdir_gpio("in");
    val9.setdir_gpio("in");
    val10.setdir_gpio("in");
    val11.setdir_gpio("in");

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
    
    led0.export_gpio();
    led1.export_gpio();
    led2.export_gpio();
    led3.export_gpio();
    led4.export_gpio();
    led5.export_gpio();
    led6.export_gpio();
    led7.export_gpio();
    led8.export_gpio();
    led9.export_gpio();
    led10.export_gpio();
    led11.export_gpio();

    led0.setdir_gpio("out");
    led1.setdir_gpio("out");
    led2.setdir_gpio("out");
    led3.setdir_gpio("out");
    led4.setdir_gpio("out");
    led5.setdir_gpio("out");
    led6.setdir_gpio("out");
    led7.setdir_gpio("out");
    led8.setdir_gpio("out");
    led9.setdir_gpio("out");
    led10.setdir_gpio("out");
    led11.setdir_gpio("out");



    //system("echo \"1\" > /sys/class/gpio/gpio17/value");
    //while (gpio17.setval_gpio("1"));
    //cout << "worked!" << endl;

    string val{};
    val0.getval_gpio(val);
    while (val == "1") {
        val0.getval_gpio(val);
    }

    //gpio17.setval_gpio("0");
    system("echo \"0\" > /sys/class/gpio/gpio17/value");

    val0.unexport_gpio();
    led0.unexport_gpio();
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