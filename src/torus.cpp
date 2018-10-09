//
// Created by ida on 25.09.18.
//

#include <list>
#include <iostream>
#include "torus.h"

using namespace std;

Torus::Torus(int notes[]) {

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


bool Torus::write_notes(int notes[]) {

    Node* curr{start};
    int y = 0;

    for (int i{0}; i < 12; i++) {
        if (notes[i] < 0 || notes[i] > 11) {
            return false;  //number out of range -> false
        }
    }

    for (int x{0}; x < 12; x++) {
        

        while (y != (int) (notes[x] / 3)) {
            curr = curr->down;
            y++;
            if (y == 4) y = 0;
        }

        curr->pitch = Pitch(notes[x] % 3);
        cout << Pitch(notes[x] % 3) << " (x: " << x << "/group: " << y << ")" << endl;

        curr = curr->right;
    }
    return true;
}