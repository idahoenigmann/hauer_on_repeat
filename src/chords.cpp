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

void play_notes(Node* start, int shift) {

    std::string input = "";

    std::cout << "  _   _       _            \n"
                 " | \\ | |     | |           \n"
                 " |  \\| | ___ | |_ ___  ___ \n"
                 " | . ` |/ _ \\| __/ _ \\/ __|\n"
                 " | |\\  | (_) | ||  __/\\__ \\\n"
                 " |_| \\_|\\___/ \\__\\___||___/\n"
                 "                           \n"
                 "                           " << std::endl;

    Node* curr;
    Node* lowerst_node = start;

    input += "\\version \"2.18.2\"\n\\score {\n\\relative c' {\n\\time 4/8\n";

    for (int bar=0; bar < 12; bar++) {
        curr = lowerst_node;
        for (int i=0; i<4; i++) {
            if (curr->is_twelve_tone) {
                std::cout << curr->get_int_representation(i, shift) << ", ";
                std::cout << convert_int_to_note(curr->get_int_representation(i, shift)) << std::endl;
                input += convert_int_to_note(curr->get_int_representation(i, shift)) + " ";
                break;
            }
            curr = curr->up;
        }
        lowerst_node = lowerst_node->right; //go to next bar
    }


    input += "}\\midi {}\\layout{}\n}";

    File file = File("notes");
    file.write(input);
    file.create_midi_pdf();
}