//
// Created by ida on 09.10.18.
//
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <cstring>
#include <list>

#include "torus.h"
#include "files.h"

std::list<std::list<int>> create_monophonie(Node* start, int shift, bool midi=true) {   //to be tested

    std::string input = "";

    std::cout << "  __  __                         _                 _      \n"
                 " |  \\/  |                       | |               (_)     \n"
                 " | \\  / | ___  _ __   ___  _ __ | |__   ___  _ __  _  ___ \n"
                 " | |\\/| |/ _ \\| '_ \\ / _ \\| '_ \\| '_ \\ / _ \\| '_ \\| |/ _ \\\n"
                 " | |  | | (_) | | | | (_) | |_) | | | | (_) | | | | |  __/\n"
                 " |_|  |_|\\___/|_| |_|\\___/| .__/|_| |_|\\___/|_| |_|_|\\___|\n"
                 "                          | |                             \n"
                 "                          |_|                             " << std::endl;

    Node* curr = start;
    int voice = 0;

    while(!curr->is_twelve_tone) {
        curr = curr->up;
        voice++;
        if (voice > 3) {
            voice = 0;
        }
    }


    input += "\\version \"2.18.2\"\n\\score {\n\\relative c'' {\n\\time 4/8\n";

    bool up = true;
    int original_voice;
    std::list<int> l;
    std::list<std::list<int>> ret {};
    Node* original_node;

    for (int bar=0; bar < 12; bar++) {
        std::list<int> beat{};
        up = true;
        original_voice = voice;
        original_node = curr;
        l.clear();

        //std::cout << curr->get_int_representation(voice, shift) << ", ";

        int first_note = curr->get_int_representation(voice, shift);

        while (curr->pitch == curr->right->pitch) {
            if (up) {
                curr = curr->up;
                voice++;

                if (voice > 3) {
                    voice = original_voice;
                    curr = original_node;
                    up = false;
                    l.clear();
                    continue;
                }
            } else {
                curr = curr->down;
                voice--;

                if (voice < 0) {
                    voice = original_voice;
                    curr = original_node;
                    up = false;
                    l.clear();
                    continue;
                }
            }

            l.push_back(curr->get_int_representation(voice, shift));

        }

        std::string len = "";

        if (l.size()+1 == 1) {
            len = "2";
        } else if (l.size()+1 == 2) {
            len = "4";
        } else if (l.size()+1 == 3) {
            len = "4";
            input += "\\tuplet 3/2 { ";
        } else {
            len = "8";
        }

        input += convert_int_to_note(first_note) + len + " ";
        beat.push_back(first_note);

        for (int i : l) {
            //std::cout << i << ", ";
            if (l.size()+1 == 3) {
                input += convert_int_to_note(i) + " ";
            } else {
                input += convert_int_to_note(i) + len + " ";
            }
            beat.push_back(i);
        }

        ret.push_back(beat);

        if (l.size()+1 == 3) {
            input += " }";
        }

        input += "\n";

        curr = curr->right; //go to next bar
        //std::cout << std::endl;

    }
    //std::cout << curr->get_int_representation(voice, shift) << std::endl;
    ret.push_back(std::list<int> {curr->get_int_representation(voice, shift)});
    input += convert_int_to_note(curr->get_int_representation(voice, shift)) + " 2 ";

    input += "}\\midi {}\\layout{}\n}";

    File file = File("monophonie");
    file.write(input);
    if (midi)
        file.create_midi_pdf();

    return ret;
}
