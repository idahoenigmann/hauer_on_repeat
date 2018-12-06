//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_CHORDS_H
#define HAUER_ON_REPEAT_CHORDS_H

#include <vector>
#include "torus.h"
#include "monophonie.h"

std::vector<std::vector<int>> chords(Node* start, int shift, bool anschlussklang, bool midi=true);
Notes create_chords(Node* start, int shift, bool anschlussklang);

std::vector<std::vector<int>> notes(Node* start, int shift, bool anschlussklang, bool midi=true);
Notes create_notes(Node* start, int shift, bool anschlussklang);

#endif //HAUER_ON_REPEAT_CHORDS_H
