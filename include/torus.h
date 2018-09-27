//
// Created by ida on 25.09.18.
//

#ifndef HAUER_ON_REPEAT_TORUS_H
#define HAUER_ON_REPEAT_TORUS_H

#include <list>

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

    Node();
};



class Torus {
  public:
    Torus();

    Torus(int notes[]);

    ~Torus();

    void write_notes(int notes[]);

    Node* start;

  private:
    std::list <Node*> allNodes;
};

#endif //HAUER_ON_REPEAT_TORUS_H
