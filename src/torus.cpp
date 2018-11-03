//
// Created by ida on 25.09.18.
//

#include <list>
#include <iostream>
#include <string>
#include <cstring>
#include "torus.h"

using namespace std;

Torus::Torus(int notes[]) {
    memcpy(numbers, notes, sizeof(numbers));

    Node* firstNodeRowPtr = nullptr;
    Node* uppNodePtr = nullptr;

    //x and y as in coordinates
    for (int y = 0; y < 4; y++) {
        Node* firstNodePtr = nullptr;
        Node* leftNodePtr = nullptr;
        for (int x = 0; x < 12; x++) {
            Node* curr = new Node();
            allNodes.push_back(curr);

            if (x == 0) {
                //set pointer for first node -> connection last and first node
                firstNodePtr = curr;
                if (y == 0) {
                    //set pointer for very first node -> connection last and first row
                    firstNodeRowPtr = curr;
                    start = curr;
                }
            }
            curr->left = leftNodePtr;
            if (leftNodePtr) {
                leftNodePtr->right = curr;
            }
            curr->up = uppNodePtr;
            if (uppNodePtr) {
                uppNodePtr->down = curr;
                uppNodePtr = uppNodePtr->right;
            }

            leftNodePtr = curr;

            if (x == 11) {
                curr->right = firstNodePtr;
                firstNodePtr->left = curr;
            }
            if (y == 3) {
                curr->down = firstNodeRowPtr;
                firstNodeRowPtr->up = curr;
                firstNodeRowPtr = firstNodeRowPtr->right;
            }
        }
        uppNodePtr = firstNodePtr;
    }

    if (!write_notes(notes)) {
        cerr << "Only notes from 0 to 11 are allowed!" << endl;
    }
    fill_out_notes();
}

Torus::Torus() : Torus(new int[12] {def, def, def, def, def, def, def, def, def, def, def, def}) {}

Torus::~Torus() {
    for (Node* node : allNodes) {
        delete node;
    }
}

Node::Node() {
    up = nullptr;
    left = nullptr;
    down = nullptr;
    right = nullptr;

    pitch = def;
}

int Node::get_int_representation(int voice, int shift) {
    return voice*3+pitch+shift;
}

bool Torus::write_notes(int notes[]) {

    Node* curr{start};
    int y = 0;

    for (int i{0}; i < 12; i++) {
        if ((notes[i] < 0 || notes[i] > 11) && notes[i] != def) {
            return false;  //number out of range -> false
        }
    }

    for (int x{0}; x < 12; x++) {

        while (y != (int) (notes[x] / 3)) {
            curr = curr->up;
            y++;
            if (y == 4) y = 0;
        }

        curr->pitch = Pitch(notes[x] % 3);
        curr->is_twelve_tone = true;
        //cout << Pitch(notes[x] % 3) << " (x: " << x << "/group: " << y << ")" << endl;

        curr = curr->right;
    }
    return true;
}

void Torus::fill_out_notes() {

    Node* curr = start;

    Pitch voices[] = {def, def, def, def};

    for (int bar=0; bar < 24; bar++) {  //go through bars twice

        for (int voice=0; voice < 4; voice++) {
            if (curr->is_twelve_tone) {
                voices[voice] = curr->pitch;    //store new pitch in array
            } else {
                curr->pitch = voices[voice];    //insert pitch of last twelve tone from voice
            }
            curr = curr->up;
        }
        curr = curr->right; //go back down again and change bar
    }
}

void get_four_chord(int* array, Node* node) {
    for (int i=0; i<4; i++) {
        array[i] = node->pitch;
        node = node->up;
    }
}

bool Torus::move_start() {
    int arr[4] = {0};
    int compare[4] = {0, 1, 1, 2};
    Node* curr = start;
    bool found = false;

    for (int k=0; k < 3; k++) {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 12; i++) {
                get_four_chord(arr, curr);
                if (memcmp(arr, compare, sizeof(arr)) == 0) {
                    found = true;
                    break;
                }
                cout << "right, ";
                curr = curr->right;

            }
            if (found) {
                break;
            }
            cout << endl << "up, ";
            shift += 3;
            curr = curr->up;
        }

        if (found) {
            break;
        }

        for (int i=0; i < 12; i++) {
            numbers[i]++;
            if (numbers[i] < 0) {
                numbers[i] = 11;
            }
        }

        shift = 1;
        cout << endl << "shift, ";
        write_notes(numbers);
        fill_out_notes();
    }

    if (found) {
        start = curr;
        return true;
    }
    return false;
}

string Torus::to_string() {

    std::string str = "";

    Node* curr = start;

    for (int bar=0; bar < 12; bar++) {
        for (int voice=0; voice < 4; voice++) {

            if (curr->pitch == def) {
                str += "-";
            } else {
                str += std::to_string(curr->get_int_representation(voice));
            }
            //str += std::to_string(curr->pitch);
            str += ", ";

            curr = curr->up;    //change voice
        }
        str += "\n";
        curr = curr->right; //go back down and change bar
    }
    return str;
}