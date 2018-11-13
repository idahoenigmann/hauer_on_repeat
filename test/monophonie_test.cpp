#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>
#include "monophonie.h"

using namespace std;

TEST(monophonie_test, test_create_monophonie) {
    int nums[12] {0, 4, 1, 5, 10, 11, 6, 2, 8, 9, 7, 3};
    Torus t = Torus(nums);

    vector<vector<int>> correct {vector<int>{0, 3}, vector<int>{4,0}, vector<int>{1,4},
            vector<int>{5,7,9}, vector<int>{10}, vector<int>{11, 7}, vector<int>{6,5,1},
            vector<int>{2,5,6}, vector<int>{8,11}, vector<int>{9,8}, vector<int>{7, 5},
            vector<int>{3,2}, vector<int>{0}};

    vector<vector<int>> monophonie{create_monophonie(t.start, 0, false)};

    ASSERT_EQ(correct, monophonie);
}