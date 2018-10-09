//
// Created by manuel on 25.09.18.
//

#include <iostream>
#include "torus.h"

using namespace std;

int main(int argc, char* argv[]) {

    //DEBUG
    //cout << argc << endl;

    
    if (argc - 1 != 12) {
        throw runtime_error("Needs 12 Numbers");
    }


    //save into new array (as integers)
    int numbers[12];
    for (int i{1}; i <= 12; i++) {
        numbers[i - 1] = stoi((string)argv[i]);
    }



    Torus torus = Torus(numbers);
}