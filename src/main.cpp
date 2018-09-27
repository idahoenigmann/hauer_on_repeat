//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include "torus.h"
#include "test_torus.h"


int main() {
    Torus torus = Torus();
    std::cout << test_move_random_path(100, torus) << std::endl;
    std::cout << test_continuity(torus) << std::endl;
}