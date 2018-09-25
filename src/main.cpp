//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include "torus.h"
#include <cstdlib>


int main() {
    Torus torus = Torus();
    Node* curr = torus.start;
    curr->pitch = low;

    for (int i = 0; i < 100; i++) {
        if (rand() % 4 == 0) {
            curr = curr->up;
            std::cout << curr->pitch << std::endl;
            curr->pitch = low;
        } else if (rand() % 4 == 1) {
            curr = curr->down;
            std::cout << curr->pitch << std::endl;
            curr->pitch = low;
        } else if (rand() % 4 == 2) {
            curr = curr->left;
            std::cout << curr->pitch << std::endl;
            curr->pitch = low;
        } else if (rand() % 4 == 3) {
            curr = curr->right;
            std::cout << curr->pitch << std::endl;
            curr->pitch = low;
        }
    }
}