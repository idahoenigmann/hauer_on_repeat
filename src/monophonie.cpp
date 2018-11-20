//
// Created by ida on 09.10.18.
//
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <cstring>
#include <vector>

#include "torus.h"
#include "files.h"

std::string convert_notes_to_string(std::vector<int> l) {
    std::string res;
    std::string len;

    bool triad = false;

    if (l.size() == 1) {
        len = "4";
    } else if (l.size() == 2) {
        len = "8";
    } else if (l.size() == 3) {
        len = "8";
        res += "\\tuplet 3/2 { ";
        triad = true;
    } else {
        len = "16";
    }

    for (int i : l) {
        if (l.size() == 3 && !triad) {
            res += convert_int_to_note(i) + " ";
        } else {
            res += convert_int_to_note(i) + len + " ";
            triad = false;
        }
    }

    if (l.size() == 3) {
        res += " }";
    }

    res += "\n";
    return res;
}

std::vector<std::vector<int>> create_monophonie(Node* start, int shift, bool anschlussklang, bool midi=true) {

    if (midi) {
        std::cout << "  __  __                         _                 _      \n"
                     " |  \\/  |                       | |               (_)     \n"
                     " | \\  / | ___  _ __   ___  _ __ | |__   ___  _ __  _  ___ \n"
                     " | |\\/| |/ _ \\| '_ \\ / _ \\| '_ \\| '_ \\ / _ \\| '_ \\| |/ _ \\\n"
                     " | |  | | (_) | | | | (_) | |_) | | | | (_) | | | | |  __/\n"
                     " |_|  |_|\\___/|_| |_|\\___/| .__/|_| |_|\\___/|_| |_|_|\\___|\n"
                     "                          | |                             \n"
                     "                          |_|                             " << std::endl;
    }
    std::string input;
    Node *curr = start;
    int voice = 0;
    bool up;
    int original_voice;
    std::vector<int> l;
    std::vector<std::vector<int>> ret{};
    Node *original_node;
    int great_four_chord[4]{0, 1, 1, 2};   //equals (0, 4, 7, 11)

    input += "\\version \"2.18.2\"\n\\score {\n\\absolute {\n\\time 4/4\n";

    while (!curr->is_twelve_tone) {
        curr = curr->up;
        voice++;
        if (voice > 3) {
            voice = 0;
        }
    }

    for (int bar = 0; bar < 12; bar++) {
        up = true;
        original_voice = voice;
        original_node = curr;
        l.clear();

        int comp = curr->right->pitch;

        while (curr->pitch == comp) {

            l.push_back(curr->get_int_representation(voice, shift));

            if (up) {
                curr = curr->up;
                voice++;

                if (voice > 3) {
                    voice = original_voice;
                    curr = original_node;
                    up = false;
                    l.clear();
                }
            } else {
                curr = curr->down;
                voice--;

                if (voice < 0) {
                    voice = original_voice;
                    curr = original_node;
                    up = false;
                    l.clear();
                }
            }
            comp = curr->right->pitch;
            if (anschlussklang && bar == 11) {
                comp = great_four_chord[voice];
            }
        }
        l.push_back(curr->get_int_representation(voice, shift));

        input += convert_notes_to_string(l);
        ret.push_back(l);
        curr = curr->right; //go to next bar

    }
    if (anschlussklang) {
        ret.push_back(std::vector<int>{great_four_chord[voice] + 3 * voice + shift});
        input += convert_int_to_note(great_four_chord[voice] + 3 * voice + shift) + " 4 ";
    } else {
        ret.push_back(std::vector<int>{curr->get_int_representation(voice, shift)});
        input += convert_int_to_note(curr->get_int_representation(voice, shift)) + " 4 ";
    }

    input += "}\\midi {}\\layout{}\n}";

    File file = File("monophonie");
    file.write(input);
    if (midi)
        file.create_midi_pdf();

    return ret;
}
