#include <cstdlib>
#include <gtest/gtest.h>
#include "monophonie.h"

using namespace std;

TEST(monophonie_test, test_create_monophonie) {
    int nums[12] {0, 4, 1, 5, 10, 11, 6, 2, 8, 9, 7, 3};
    Torus t = Torus(nums);

    for (auto sub : create_monophonie(t.start, 0, false)) {
        cout << "[";
        for (int i : sub) {
            cout << i << ", ";
        }
        cout << "], ";
    }
}