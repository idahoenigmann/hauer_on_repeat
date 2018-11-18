//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_CHORDS_H
#define HAUER_ON_REPEAT_CHORDS_H

#include <vector>
#include "torus.h"

std::vector<std::vector<int>> play_chords(Node* start, int shift, bool anschlussklang, bool midi=true);
std::vector<std::vector<int>> play_notes(Node* start, int shift, bool anschlussklang, bool midi=true);

#endif //HAUER_ON_REPEAT_CHORDS_H
