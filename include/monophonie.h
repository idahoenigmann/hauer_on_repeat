//
// Created by ida on 09.10.18.
//

#ifndef HAUER_ON_REPEAT_MONOPHONIE_H
#define HAUER_ON_REPEAT_MONOPHONIE_H

#include "torus.h"
#include <vector>

struct Notes {
    std::string input;
    std::vector<std::vector<int>> list;

    Notes(std::string input, std::vector<std::vector<int>> list) {
        this->input = input;
        this->list = list;
    }
};

std::vector<std::vector<int>> monophonie(Node* start, int shift, bool anschlussklang, bool midi=true);

Notes create_monophonie(Node* start, int shift, bool anschlussklang);

#endif //HAUER_ON_REPEAT_MONOPHONIE_H
