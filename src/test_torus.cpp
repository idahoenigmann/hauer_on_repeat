//
// Created by ida on 27.09.18.
//

#include <cstdlib>
#include "torus.h"

bool test_move_random_path(int num_of_moves, Torus torus) {
    /*moves along a random path to find nullptrs*/

    Node* curr = torus.start;

    for (int i = 0; i < num_of_moves; i++) {
        if (rand() % 4 == 0) {
            curr = curr->up;
        } else if (rand() % 4 == 1) {
            curr = curr->down;
        } else if (rand() % 4 == 2) {
            curr = curr->left;
        } else if (rand() % 4 == 3) {
            curr = curr->right;
        }
    }
    return true;
}

bool test_continuity(Torus torus) {
    /*checks if pointers on the "edges" are set correctly*/

    Node* curr = torus.start;
    for (int i=0; i < 4; i++) {     //test if after moving up 4 times start is reached again
        curr = curr->up;
    }
    if (curr != torus.start) return false;

    for (int i=0; i < 4; i++) {     //test if after moving down 4 times start is reached again
        curr = curr->down;
    }
    if (curr != torus.start) return false;

    for (int i=0; i < 12; i++) {    //test if after moving right 12 times start is reached again
        curr = curr->right;
    }
    if (curr != torus.start) return false;

    for (int i=0; i < 12; i++) {    //test if after moving left 12 times start is reached again
        curr = curr->left;
    }
    if (curr != torus.start) return false;

    return true;
}