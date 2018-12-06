#include <utility>

//
// Created by ida on 09.10.18.
//

#ifndef HAUER_ON_REPEAT_MONOPHONIE_H
#define HAUER_ON_REPEAT_MONOPHONIE_H

#include <vector>
#include "torus.h"

struct Notes {
    std::string input;
    std::vector<std::vector<int>> list;

    Notes(std::string input, std::vector<std::vector<int>> list) {
        this->input = std::move(input);
        this->list = list;
    }
};

std::vector<std::vector<int>> monophonie(Node* start, int shift, bool anschlussklang, bool midi=true);

Notes create_monophonie(Node* start, int shift, bool anschlussklang);

void monophonie_and_chords(Node* start, int shift, bool anschlussklang, bool midi=true);

#endif //HAUER_ON_REPEAT_MONOPHONIE_H
