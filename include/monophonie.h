#include <utility>

//
// Created by ida on 09.10.18.
//

#ifndef HAUER_ON_REPEAT_MONOPHONIE_H
#define HAUER_ON_REPEAT_MONOPHONIE_H

#include <vector>
#include "torus.h"

//! Store music piece in lilypond syntax
struct Notes {
    std::string input;  //! string in lilypond syntax
    std::vector<std::vector<int>> list; //! vector representation of music

    //! constructor
    /*!
     * @param input string in lilypond syntax
     * @param list vector representation of music
     */
    Notes(std::string input, std::vector<std::vector<int>> list) {
        this->input = std::move(input);
        this->list = list;
    }
};

//! creates monophonie, displays and plays it
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @param midi false if chords should not be displayed and played; true otherwise
 * @return vector representation of music piece
 */
std::vector<std::vector<int>> monophonie(Node* start, int shift, bool midi=true);

//! converts monophonie into a string in lilypond syntax
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @return notes storing a string in lilypond syntax
 */
Notes create_monophonie(Node* start, int shift);

//! playes monphonie and chords simultaneously
/*!
 * @param start Node pointer to lowest note of first four chord
 * @param shift difference between lowest note and c
 * @param anschlussklang true if anschlussklang is needed; false otherwise
 * @param midi false if chords should not be displayed and played; true otherwise
 */
void monophonie_and_chords(Node* start, int shift, bool midi=true);

#endif //HAUER_ON_REPEAT_MONOPHONIE_H
