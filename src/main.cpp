//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include "torus.h"
#include "monophonie.h"
#include "chords.h"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc - 1 != 12) {
        throw runtime_error("Needs 12 Numbers (" + to_string(argc - 1) + " given)");
    }

    //save into new array (as integers)
    int numbers[12];
    for (int i{1}; i <= 12; i++) {
        numbers[i - 1] = stoi((string)argv[i]);
    }

    Torus torus = Torus(numbers);

    bool anschlussklang = !torus.move_start();
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