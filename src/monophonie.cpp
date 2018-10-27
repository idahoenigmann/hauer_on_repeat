//
// Created by ida on 09.10.18.
//
#include <iostream>
#include "torus.h"

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

    for (int bar=0; bar < 12; bar++) {
        std::cout << voice*3+curr->pitch << ", ";

        while (curr->pitch == curr->right->pitch) {
            curr = curr->up;
            voice++;
            if (voice > 3) {
                voice = 0;
            }
            std::cout << voice*3+curr->pitch << ", ";

        }
        curr = curr->right; //go to next bar
        std::cout << std::endl;
    }
    std::cout << voice*3+curr->pitch << std::endl;
}