//
// Created by ida on 25.09.18.
//

#include <iostream>
#include "torus.h"

Torus::Torus() {

    Node* firstNodeRowPtr;
    Node* upperNodePtr;

    //x and y as in coordinates
    for (int y = 0; y < 4; y++) {
        Node* firstNodePtr;
        Node* lastNodePtr;
        for (int x = 0; x < 12; x++) {
            Node* curr = new Node();

            if (x == 0) {
                //set pointer for first node -> connection last and first node
                firstNodePtr = curr;
                if (y == 0) {
                    //set pointer for very first node -> connection last and first row
                    firstNodeRowPtr = curr;
                }
            }



        }
    }
}