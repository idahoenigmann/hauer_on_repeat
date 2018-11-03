//
// Created by ida on 03.11.18.
//

#include <iostream>

#include "files.h"
#include "torus.h"
#include "chords.h"

void play_chords(Node* start, int shift) {

    std::string input = "";

    std::cout << "   _____ _                   _     \n"
                 "  / ____| |                 | |    \n"
                 " | |    | |__   ___  _ __ __| |___ \n"
                 " | |    | '_ \\ / _ \\| '__/ _` / __|\n"
                 " | |____| | | | (_) | | | (_| \\__ \\\n"
                 "  \\_____|_| |_|\\___/|_|  \\__,_|___/\n"
                 "                                   \n"
                 "                                   " << std::endl;

    Node* curr = start;

    input += "\\version \"2.18.2\"\n\\score {\n\\relative c'' {\n\\time 4/8\nr2\n";


    int arr[4] = {};

    for (int bar=0; bar < 12; bar++) {
        get_four_chord(arr, curr);

        input += "<<";

        for (int i=0; i<4; i++) {
            if (i != 0) {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + "2 ";
            } else {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + ",2 ";
            }
        }

        input += ">>\n";

        curr = curr->right; //go to next bar
    }


    input += "}\\midi {}\\layout{}\n}";

    File file = File("chords");
    file.write(input);
    file.create_midi_pdf();
}