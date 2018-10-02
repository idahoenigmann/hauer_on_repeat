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

}

TEST(torus_test, test_constructor) {

}


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}