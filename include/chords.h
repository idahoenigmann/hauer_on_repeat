//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_CHORDS_H
#define HAUER_ON_REPEAT_CHORDS_H

#include <vector>
#include "torus.h"

void chords(Node* start, int shift, bool anschlussklang, bool midi=true);
std::string create_chords(Node* start, int shift, bool anschlussklang);

void notes(Node* start, int shift, bool anschlussklang, bool midi=true);
std::string create_notes(Node* start, int shift, bool anschlussklang);

#endif //HAUER_ON_REPEAT_CHORDS_H
