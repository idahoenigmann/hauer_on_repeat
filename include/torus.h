//
// Created by ida on 25.09.18.
//

#ifndef HAUER_ON_REPEAT_TORUS_H
#define HAUER_ON_REPEAT_TORUS_H

enum Pitch {
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
};



class Torus {
  public:
    Torus();


  private:
    Node* start;
};

#endif //HAUER_ON_REPEAT_TORUS_H
