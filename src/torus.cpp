//
// Created by ida on 25.09.18.
//

#include <list>
#include "torus.h"

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

    write_notes(notes);
}

void Torus::write_notes(int notes[]) {}

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