//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_CHORDS_H
#define HAUER_ON_REPEAT_CHORDS_H

#include <vector>
#include "torus.h"

std::vector<std::vector<int>> play_chords(Node* start, int shift, bool anschlussklang, bool midi=true);
void play_notes(Node* start, int shift);

#endif //HAUER_ON_REPEAT_CHORDS_H
