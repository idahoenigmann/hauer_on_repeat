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
    std::string height = "";
    while (i > 11) {
        i = i - 12;
        height += "'";
    }

    switch (i){
        case 0:
            return "c" + height;
        case 1:
            return "cis" + height;
        case 2:
            return "d" + height;
        case 3:
            return "dis" + height;
        case 4:
            return "e" + height;
        case 5:
            return "f" + height;
        case 6:
            return "fis" + height;
        case 7:
            return "g" + height;
        case 8:
            return "gis" + height;
        case 9:
            return "a" + height;
        case 10:
            return "ais" + height;
        case 11:
            return "b" + height;
        default:
            return "";
    }
}

void create_monophonie(Node* start, int shift) {   //to be tested

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

    /*create new file*/
    std::ofstream file;
    file.open("test.ly");

    file << "\\version \"2.18.2\"\n\\score {\n\\relative c'' {\n\\time 4/8\n";

    bool up = true;
    int original_voice;
    std::list<int> l;
    Node* original_node;

    for (int bar=0; bar < 12; bar++) {

        up = true;
        original_voice = voice;
        original_node = curr;
        l.clear();

        std::cout << curr->get_int_representation(voice, shift) << ", ";

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
            file << "\\tuplet 3/2 { ";
        } else {
            len = "8";
        }

        file << convert_int_to_note(first_note) + len + " ";

        for (int i : l) {
            std::cout << i << ", ";
            if (l.size()+1 == 3) {
                file << convert_int_to_note(i) + " ";
            } else {
                file << convert_int_to_note(i) + len + " ";
            }

        }

        if (l.size()+1 == 3) {
            file << " }";
        }

        file << "\n";

        curr = curr->right; //go to next bar
        std::cout << std::endl;

    }
    std::cout << curr->get_int_representation(voice, shift) << std::endl;
    file << convert_int_to_note(curr->get_int_representation(voice, shift)) + " 2 ";

    file  << "}\\midi {}\\layout{}\n}";
    file.close();
    system("lilypond test.ly");
    system("timidity test.midi -Ow -o test.mp3");
    system("vlc test.mp3 &");

    std::string path = getexepath();
    path.erase(path.rfind('/'));
    std::string str = "firefox file://" + path + "/test.pdf";
    system(str.c_str());
}
