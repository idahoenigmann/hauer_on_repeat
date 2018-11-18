#include "torus.h"
#include <cstdlib>
#include <gtest/gtest.h>

TEST(torus_test, test_nullptr) {
    Torus torus = Torus();
    Node* curr = torus.start;

    for (int i = 0; i < 10000000; i++) {
        int num = rand();

        ASSERT_TRUE(curr->up != nullptr);
        ASSERT_TRUE(curr->right != nullptr);
        ASSERT_TRUE(curr->down != nullptr);
        ASSERT_TRUE(curr->left != nullptr);

        if (num % 4 == 0) {
            curr = curr->up;
        } else if (num % 4 == 1) {
            curr = curr->down;
        } else if (num % 4 == 2) {
            curr = curr->left;
        } else if (num % 4 == 3) {
            curr = curr->right;
        }
    }
}

TEST(torus_test, test_continuity) {
    /*checks if pointers on the "edges" are set correctly*/
    Torus torus = Torus();

    Node* start = torus.start;
    Node* curr = start;
    for (int i=0; i < 4; i++) {     //test if after moving up 4 times start is reached again
        curr = curr->up;
    }
    ASSERT_TRUE(curr == start);

    for (int i=0; i < 4; i++) {     //test if after moving down 4 times start is reached again
        curr = curr->down;
    }
    ASSERT_TRUE(curr == start);

    for (int e = 0; e < 4; e++) {
        start = curr;   //set start node to first node in row
        for (int i=0; i < 12; i++) {    //test if after moving right 12 times start is reached again
            curr = curr->right;
        }
        ASSERT_TRUE(curr == start);

        for (int i=0; i < 12; i++) {    //test if after moving left 12 times start is reached again
            curr = curr->left;
        }
        ASSERT_TRUE(curr == start);

        curr = curr->down;  //test every row
    }
}

TEST(torus_test, test_constructor) {
    int notes[12] {4,7,2,9,0,11,3,6,1,10,5,8};
    Torus torus = Torus(notes);
    int x{0};

    for (int note : notes) {
        int y{0};
        Node* curr = torus.start;

        //set x
        for (int i{0}; i < x; i++) {
            curr = curr->right;
        }

        //set y
        while (y != (int)(note/3)) {
            y = (y < 3 ? y+1 : 0);
            curr = curr->up;
        }

        ASSERT_TRUE(curr->pitch == note%3);
        x++;
    }
}

TEST(torus_test, test_move_start) {
    {
        int notes[12]{2, 11, 1, 8, 5, 3, 10, 0, 7, 6, 4, 9};
        Torus torus = Torus(notes);

        torus.move_start();

        int arr[4] = {};
        int correct_arr[4] = {0, 1, 1, 2};  //is equal to 0, 4, 7, 11 without voices
        get_four_chord(arr, torus.start);
        for (int i{0}; i < 4; i++) {
            ASSERT_EQ(arr[i], correct_arr[i]);
        }
    }
    {
        int notes[12]{4, 1, 8, 6, 10, 9, 11, 5, 0, 7, 3, 2};
        Torus torus = Torus(notes);

        torus.move_start();

        int arr[4] = {};
        int correct_arr[4] = {0, 1, 1, 2};  //is equal to 0, 4, 7, 11 without voices
        get_four_chord(arr, torus.start);
        for (int i{0}; i < 4; i++) {
            ASSERT_EQ(arr[i], correct_arr[i]);
        }
    }
}

TEST(torus_test, test_anschlussklang) {
    int notes[12]{6, 10, 8, 4, 9, 11, 3, 1, 0, 7, 2, 5};
    Torus torus = Torus(notes);

    bool anschlussklang = !torus.move_start();
    ASSERT_TRUE(anschlussklang);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}