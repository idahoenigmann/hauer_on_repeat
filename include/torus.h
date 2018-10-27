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
};



class Torus {
  public:
    Torus();

    Torus(int notes[]);

    ~Torus();

    bool write_notes(int notes[]);

    Node* start;

    void fill_out_notes();

     std::string to_string();

  private:
    std::list <Node*> allNodes;
};

#endif //HAUER_ON_REPEAT_TORUS_H
