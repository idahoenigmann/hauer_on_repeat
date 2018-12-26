//
// Created by ida on 25.09.18.
//

#ifndef HAUER_ON_REPEAT_TORUS_H
#define HAUER_ON_REPEAT_TORUS_H

#include <list>
#include <string>

//! enum Pitch - The different heights of notes
enum Pitch {
    def = -1, //! note is not yet known
    low = 0, //! lowest note of that group
    med, //! middle note of that group
    high //! highest note of that group
};

//! Represent tone of a torus
struct Node {
    Node* up; //! pointer to next node above
    Node* left; //! pointer to next node left
    Node* down; //! pointer to next node below
    Node* right; //! pointer to next node right

    Pitch pitch; //! height of the node
    bool is_twelve_tone = false;

    //! constructor
    Node();

    //! returns integer corresponding to the note represented
    /*!
     * @param voice group of the note (1 - 4)
     * @param shift interval of lowest note from c
     */
    int get_int_representation(int voice,int shift=0);
};

//! stores the four notes that are played simultaneous into a given array
/*!
 * @param array array into which the notes are stored
 * @param node pointer to the lowest note of the four notes
 */
void get_four_chord(int* array, Node* node);

//! returns the name of the given integer
/*!
 * @param i interger representing a note
 * @return string containing the note name (e.g. cis)
 */
std::string convert_int_to_note(int i);

//! Represents piece of music
class Torus {
  public:
    //! constructor
    /*!
     * Pitch of each note will be set to default value
     */
    Torus();

    //! constructor
    /*!
     * @param notes integer representation of notes to be stored into the torus
     */
    explicit Torus(int notes[]);

    //! deconstructor
    /*!
     * deletes all nodes
     */
    ~Torus();

    //! stores the given notes into the corresponding nodes of the torus
    /*!
     * @param notes integer representation of the notes to be stored
     * @return true if successful, false otherwise
     */
    bool write_notes(int notes[]);

    Node* start; //!pointer to lowest note of the first four chord

    //! sets all pitches in the torus to default value
    void clear_torus();

    //! fill out all pitchless nodes in the torus
    /*!
     * repeats each pitch until another pitch of the same group already is filled in
     * then this pitch is repeated
     */
    void fill_out_notes();

    //! sets start pinter of torus to the lowest note of the correct four chord
    /*!
     * @return true if great four chord is found in torus; false if anschlussklang needs to be added
     */
    bool move_start();

    //! returns string representation of torus
    /*!
     * @return string representing the torus
     */
    std::string to_string();

    int shift=0; //! interval of lowest note from c
  private:
    std::list <Node*> allNodes; //! list of all nodes used to delete them in deconstructor
    int numbers[12]; //! array of the numbers used to create the torus
};

#endif //HAUER_ON_REPEAT_TORUS_H
