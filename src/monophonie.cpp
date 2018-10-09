//
// Created by ida on 09.10.18.
//
#include <iostream>
#include "torus.h"

void create_monophonie(Node* start) {   //to be tested
    int voice = 0;
    Node* curr = start;
    Node* bar = start;
    Node* next;
    int next_voice = 0;

    std::list<int> notes;

    while (curr->pitch == curr->right->pitch) {
        voice++;
        curr = curr->up;
    }

    for (int i=0; i < 12; i++) {
        notes.push_back(voice*3+curr->pitch);

        next = bar->right;

        while (next->pitch == next->right->pitch) {
            next_voice++;
            next = next->up;
        }

        while (voice != next_voice) {
            if (voice < next_voice) {
                curr = curr->up;
                voice++;
            } else {
                curr = curr->down;
                voice--;
            }
            notes.push_back(voice*3+curr->pitch);
        }

        for (int note : notes) {
            std::cout << note << ", ";
        }
        std::cout << std::endl;

        notes.clear();
        bar = bar->right;
    }
}