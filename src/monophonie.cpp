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
#include "chords.h"
#include "monophonie.h"

using namespace std;

string convert_notes_to_string(vector<int> l) {
    string res;
    string len;

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

vector<vector<int>> monophonie(Node* start, int shift, int delta, bool midi) {
    if (midi) {
        cout << "  __  __                         _                 _      \n"
                     " |  \\/  |                       | |               (_)     \n"
                     " | \\  / | ___  _ __   ___  _ __ | |__   ___  _ __  _  ___ \n"
                     " | |\\/| |/ _ \\| '_ \\ / _ \\| '_ \\| '_ \\ / _ \\| '_ \\| |/ _ \\\n"
                     " | |  | | (_) | | | | (_) | |_) | | | | (_) | | | | |  __/\n"
                     " |_|  |_|\\___/|_| |_|\\___/| .__/|_| |_|\\___/|_| |_|_|\\___|\n"
                     "                          | |                             \n"
                     "                          |_|                             " << endl;
    }

    string input;

    input += "\\version \"2.18.2\"\n\\score {\n\\absolute {\n\\time 4/4\n<< \\new Staff {";

    Notes notes = create_monophonie(start, shift, delta);
    input += notes.input;

    input += "}>>}\\midi {}\n}";

    File file = File("monophonie");
    file.write(input, "ly");

    if (midi)
        file.create_midi_pdf(false);
    return notes.list;
}

void monophonie_and_chords(Node* start, int shift, int delta, bool midi) {
    if (midi) {
        cout << "  __  __                         _                 _                        _    _____ _                   _     \n"
                " |  \\/  |                       | |               (_)                      | |  / ____| |                 | |    \n"
                " | \\  / | ___  _ __   ___  _ __ | |__   ___  _ __  _  ___    __ _ _ __   __| | | |    | |__   ___  _ __ __| |___ \n"
                " | |\\/| |/ _ \\| '_ \\ / _ \\| '_ \\| '_ \\ / _ \\| '_ \\| |/ _ \\  / _` | '_ \\ / _` | | |    | '_ \\ / _ \\| '__/ _` / __|\n"
                " | |  | | (_) | | | | (_) | |_) | | | | (_) | | | | |  __/ | (_| | | | | (_| | | |____| | | | (_) | | | (_| \\__ \\\n"
                " |_|  |_|\\___/|_| |_|\\___/| .__/|_| |_|\\___/|_| |_|_|\\___|  \\__,_|_| |_|\\__,_|  \\_____|_| |_|\\___/|_|  \\__,_|___/\n"
                "                          | |                                                                                    \n"
                "                          |_|                                                                                    " << endl;
    }

    string input;

    input += "\\version \"2.18.2\"\n\\score {\n\\absolute {\n\\time 4/4\n<< \\new Staff {";

    input += create_monophonie(start, shift+12, delta).input;
    input += "}\n\\new Staff {\n\\clef bass\n";
    input += create_chords(start, shift, delta).input;
    input += "}>>}\\midi {}\n}";

    File file = File("monophonie_and_chords");
    file.write(input, "ly");
    if (midi)
        file.create_midi_pdf();
}

Notes create_monophonie(Node* start, int shift, int delta) {
    string input;
    Node *curr = start;
    int voice = 0;
    bool up;
    int original_voice;
    std::vector<std::vector<int>> ret{};
    vector<int> l;
    Node *original_node;
    int arr[4] = {};

    if (delta > 0) {
        curr = curr->right;
    }

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
        }
        l.push_back(curr->get_int_representation(voice, shift));

        input += convert_notes_to_string(l);
        ret.push_back(l);
        curr = curr->right; //go to next bar

    }
    curr = start;
    l.clear();

    if (delta == 2) {
        l.clear();
        arr[0] = 0;
        arr[1] = 1;
        arr[2] = 1;
        arr[3] = 2;

        int last_chord_arr[4] = {};
        get_four_chord(last_chord_arr, curr);

        for (int i{}; i < 4; i++) {
            if (arr[i] != last_chord_arr[i]) {
                last_chord_arr[i] = arr[i];
                break;
            }
        }

        input += "<<";
        for (int i=0; i<4; i++) {
            input += convert_int_to_note(last_chord_arr[i] + 3 * i + shift) + "4 ";
            l.push_back(last_chord_arr[i] + 3 * i + shift);
        }
        ret.push_back(l);
        input += ">>\n";

    }

    l.clear();

    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 2;

    input += "<<";
    for (int i=0; i<4; i++) {
        input += convert_int_to_note(arr[i] + 3 * i + shift) + "2 ";
        l.push_back(arr[i] + 3 * i + shift);
    }
    ret.push_back(l);
    input += ">>\n";


    return Notes(input, ret);
}
