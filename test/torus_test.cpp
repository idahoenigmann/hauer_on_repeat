#include "../src/torus.cpp"
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
    int notes[12] {0,1,2,3,4,5,6,7,8,9,10,11};
    Torus torus = Torus(notes);

    for (int x{0}; x < 12; x++) {
        
    }
}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}