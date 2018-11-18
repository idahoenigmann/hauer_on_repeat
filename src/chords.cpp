//
// Created by ida on 03.11.18.
//

#include <iostream>
#include <vector>

#include "files.h"
#include "torus.h"
#include "chords.h"

using namespace std;

vector<vector<int>> play_chords(Node* start, int shift, bool anschlussklang, bool midi) {

    if (midi) {
        cout << "   _____ _                   _     \n"
                "  / ____| |                 | |    \n"
                " | |    | |__   ___  _ __ __| |___ \n"
                " | |    | '_ \\ / _ \\| '__/ _` / __|\n"
                " | |____| | | | (_) | | | (_| \\__ \\\n"
                "  \\_____|_| |_|\\___/|_|  \\__,_|___/\n"
                "                                   " << endl;
    }

    vector<vector<int>> ret {};
    vector<int> l {};
    string input;
    Node* curr = start;
    int arr[4] = {};

    input += "\\version \"2.18.2\"\n\\score {\n\\relative c {\n\\time 4/4\nr2\n";

    if (anschlussklang) {
        int great_four_chord[] {0, 1, 1, 2};
        input += "<<";

        for (int i=0; i<4; i++) {
            input += convert_int_to_note(great_four_chord[i] + 3 * i + shift) + "4 ";
            l.push_back(great_four_chord[i] + 3 * i + shift);
        }
        ret.push_back(l);
        input += ">>\n";
    }

    for (int bar=0; bar < 12; bar++) {
        get_four_chord(arr, curr);
        l.clear();

        input += "<<";

        for (int i=0; i<4; i++) {
            if (i != 0) {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + "4 ";
            } else {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + ",4 ";
            }
            l.push_back(arr[i] + i * 3 + shift);
        }
        ret.push_back(l);
        input += ">>\n";
        curr = curr->right; //go to next bar
    }

    if (anschlussklang) {
        get_four_chord(arr, curr);  //add great four chord at the end
        l.clear();

        input += "<<";

        for (int i = 0; i < 4; i++) {
            if (i != 0) {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + "4 ";
            } else {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + ",4 ";
            }
            l.push_back(arr[i] + i * 3 + shift);
        }
        ret.push_back(l);
        input += ">>\n";

        l.clear();

        int great_four_chord[] {0, 1, 1, 2};
        input += "<<";

        for (int i=0; i<4; i++) {
            if (i != 0) {
                input += convert_int_to_note(great_four_chord[i] + 3 * i + shift) + "2 ";
            } else {
                input += convert_int_to_note(great_four_chord[i] + 3 * i + shift) + ",2 ";
            }
            l.push_back(great_four_chord[i] + 3 * i + shift);
        }
        ret.push_back(l);
        input += ">>\n";

    } else {
        get_four_chord(arr, curr);  //add great four chord at the end
        l.clear();

        input += "<<";

        for (int i = 0; i < 4; i++) {
            if (i != 0) {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + "2 ";
            } else {
                input += convert_int_to_note(arr[i] + i * 3 + shift) + ",2 ";
            }
            l.push_back(arr[i] + 3 * i + shift);
        }
        ret.push_back(l);
        input += ">>\n";
    }

    input += "}\\midi {}\\layout{}\n}";

    if (midi) {
        File file = File("chords");
        file.write(input);
        file.create_midi_pdf();
    }
    return ret;
}

void play_notes(Node* start, int shift) {

    string input;

    cout << "  _   _       _            \n"
            " | \\ | |     | |           \n"
            " |  \\| | ___ | |_ ___  ___ \n"
            " | . ` |/ _ \\| __/ _ \\/ __|\n"
            " | |\\  | (_) | ||  __/\\__ \\\n"
            " |_| \\_|\\___/ \\__\\___||___/\n"
            "                           " << endl;

    Node* curr;
    Node* lowerst_node = start;

    input += "\\version \"2.18.2\"\n\\score {\n\\absolute {\n\\time 4/8\n";

    for (int bar=0; bar < 12; bar++) {
        curr = lowerst_node;
        for (int i=0; i<4; i++) {
            if (curr->is_twelve_tone) {
                cout << curr->get_int_representation(i, shift) << ", ";
                cout << convert_int_to_note(curr->get_int_representation(i, shift)) << endl;
                input += convert_int_to_note(curr->get_int_representation(i, shift)) + "' ";
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