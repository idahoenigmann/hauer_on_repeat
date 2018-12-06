//
// Created by ida on 09.10.18.
//

#ifndef HAUER_ON_REPEAT_MONOPHONIE_H
#define HAUER_ON_REPEAT_MONOPHONIE_H

#include "torus.h"
#include <vector>

void monophonie(Node* start, int shift, bool anschlussklang, bool midi=true);

std::string create_monophonie(Node* start, int shift, bool anschlussklang);

#endif //HAUER_ON_REPEAT_MONOPHONIE_H
