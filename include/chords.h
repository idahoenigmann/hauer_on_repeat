//
// Created by ida on 03.11.18.
//

#ifndef HAUER_ON_REPEAT_CHORDS_H
#define HAUER_ON_REPEAT_CHORDS_H

#include <vector>
#include "torus.h"
#include "monophonie.h"

//! creates chords, displays and plays them
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @param midi false if chords should not be displayed and played; true otherwise
 * @return vector representation of music piece
 */
std::vector<std::vector<int>> chords(Node* start, int shift, int anschlussklang, bool midi=true);

//! converts chords into a string in lilypond syntax
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @return notes storing a string in lilypond syntax
 */
Notes create_chords(Node* start, int shift, int anschlussklang);

//! creates notes, displays and plays them
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @param midi false if chords should not be displayed and played; true otherwise
 * @return vector representation of music piece
 */
std::vector<std::vector<int>> notes(Node* start, int shift, int anschlussklang, bool midi=true);

//! converts notes into a string in lilypond syntax
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @return notes storing a string in lilypond syntax
 */
Notes create_notes(Node* start, int shift, int anschlussklang);

#endif //HAUER_ON_REPEAT_CHORDS_H
