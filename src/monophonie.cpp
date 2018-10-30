//
// Created by ida on 09.10.18.
//
#include <iostream>
#include <fstream>
#include "torus.h"

#include <string>
#include <limits.h>
#include <unistd.h>
#include <cstring>
#include <list>

std::string getexepath()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    return std::string( result, (count > 0) ? count : 0 );
}

std::string convert_int_to_note(int i) {
    i = i % 12;
    switch (i){
        case 0:
            return "c'";
        case 1:
            return "cis'";
        case 2:
            return "d'";
        case 3:
            return "dis'";
        case 4:
            return "e'";
        case 5:
            return "f'";
        case 6:
            return "fis'";
        case 7:
            return "g'";
        case 8:
            return "gis'";
        case 9:
            return "a'";
        case 10:
            return "ais'";
        case 11:
            return "b'";
        default:
            return "";
    }
}

void create_monophonie(Node* start) {   //to be tested

    Node* curr = start;
    int voice = 0;

    while(!curr->is_twelve_tone) {
        curr = curr->up;
        voice++;
        if (voice > 3) {
            voice = 0;
        }
    }

    /*create new file*/
    std::ofstream file;
    file.open("test.ly");

    std::ofstream file2;
    file2.open("test_midi.ly"); //für das zweite .ly file für die midi erzeugung

    //file << "\\version \"2.18.2\"{\n\\score{\n{\\time 4/4\n";
    file << "\\version \"2.18.2\"\n{";
    file2 << "\\version \"2.18.2\"\n\\score {\n\\relative{";

    bool up = true;
    int original_voice;
    std::list<int> l;
    Node* original_node;

    for (int bar=0; bar < 12; bar++) {

        up = true;
        original_voice = voice;
        original_node = curr;
        l.clear();

        std::cout << voice*3+curr->pitch << ", ";

        int first_note = voice*3+curr->pitch;

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

            l.push_back(voice*3+curr->pitch);

        }

        std::string len = "";

        if (l.size()+1 == 1) {
            len = "1";
        } else if (l.size()+1 == 2) {
            len = "2";
        } else if (l.size()+1 == 3) {
            len = "4";
            file << "\\tuplet 3/2 4 { ";
            file2 << "\\tuplet 3/2 4 { ";
        } else if (l.size()+1 == 4) {
            len = "4";
        }

        file << convert_int_to_note(voice*3+curr->pitch) + len + " ";
        file2 << convert_int_to_note(voice*3+curr->pitch) + len + " ";

        bool first = true;
        for (int i : l) {
            std::cout << i << ", ";

            if (l.size()+1 == 3 and !first) {
                file << convert_int_to_note(i) + " ";
                file2 << convert_int_to_note(i) + " ";
            } else {
                file << convert_int_to_note(i) + len + " ";
                file2 << convert_int_to_note(i) + len + " ";
                first = false;
            }
        }

        if (l.size()+1 == 3) {
            file << "}";
            file2 << "}";
        }

        curr = curr->right; //go to next bar
        std::cout << std::endl;

    }
    std::cout << voice*3+curr->pitch << std::endl;
    file << convert_int_to_note(voice*3+curr->pitch) + " ";
    file2 << convert_int_to_note(voice*3+curr->pitch) + " ";
    // file << "\n}\n\\midi {}\n\\layout {}";

    file << "}\n";
    file2 << "}\n";

    file.close();

    file2  << "\\midi {}\n}";
    file2.close();
    system("lilypond test.ly");
    system("lilypond test_midi.ly");
    system("timidity test_midi.midi -Ow -o test.mp3");
    system("vlc test.mp3 &");

    std::string path = getexepath();
    path.erase(path.rfind('/'));
    std::string str = "firefox file://" + path + "/test.pdf";
    system(str.c_str());
}
