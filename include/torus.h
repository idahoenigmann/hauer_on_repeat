//
// Created by ida on 25.09.18.
//

#ifndef HAUER_ON_REPEAT_TORUS_H
#define HAUER_ON_REPEAT_TORUS_H

#include <list>
#include <string>

enum Pitch {
    def = -1, //default
    low = 0,
    med,
    high
};

struct Node {
    Node* up;
    Node* left;
    Node* down;
    Node* right;

    Pitch pitch;
    bool is_twelve_tone = false;

    Node();

    int get_int_representation(int voice,int shift=0);
};

void get_four_chord(int* array, Node* node);

std::string convert_int_to_note(int i);

class Torus {
  public:
    Torus();

    Torus(int notes[]);

    ~Torus();

    bool write_notes(int notes[]);

    Node* start;

    void fill_out_notes();

    bool move_start();

    std::string to_string();

    int shift=0;
  private:
    std::list <Node*> allNodes;
    int numbers[12];
};

#endif //HAUER_ON_REPEAT_TORUS_H
