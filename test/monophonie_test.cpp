#include <cstdlib>
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include "monophonie.h"

using namespace std;

TEST(monophonie_test, test_monophonie) {
    {
    int nums[12] {0, 4, 1, 5, 10, 11, 6, 2, 8, 9, 7, 3};
    Torus t = Torus(nums);

    vector<vector<int>> correct {vector<int>{0, 3}, vector<int>{4,0}, vector<int>{1,4},
            vector<int>{5,7,9}, vector<int>{10}, vector<int>{11, 7}, vector<int>{6,5,1},
            vector<int>{2,5,6}, vector<int>{8,11}, vector<int>{9,8}, vector<int>{7, 5},
            vector<int>{3,2}, vector<int>{0}};

    vector<vector<int>> m{monophonie(t.start, 0, false)};

    ASSERT_EQ(correct, m);
    }

    {
        int nums[12] = {7, 4, 0, 8, 1, 5, 10, 2, 6, 11, 9, 3};
        Torus t = Torus(nums);

        vector<vector<int>> correct {vector<int>{7, 3}, vector<int>{4,2}, vector<int>{0,4,7},
                vector<int>{8,4,0}, vector<int>{1,4}, vector<int>{5,8,9}, vector<int>{10,8,5,1},
                vector<int>{2,5,8}, vector<int>{6,10}, vector<int>{11}, vector<int>{9,6,5},
                vector<int>{3,6}, vector<int>{7}};

        vector<vector<int>> m{monophonie(t.start, 0, false)};

        ASSERT_EQ(correct, m);
    }
}

TEST(monophonie_test, test_random_monophonie) {
    vector<int> randoms {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    random_device rd;
    default_random_engine e1(rd());

    int nums[12] {};

    int i{11};
    while (!randoms.empty()) {
        uniform_int_distribution<int> uniform_dist(0, static_cast<int>(randoms.size() - 1));

        int idx{uniform_dist(e1)};

        //cout << randoms[idx] << ", ";
        nums[11-i] = randoms[idx];
        randoms.erase(randoms.begin()+idx);
        i--;
    }

    Torus t = Torus(nums);

    vector<vector<int>> m{monophonie(t.start, 0, false)};
    for (int j{0}; j < 12; j++) {
        ASSERT_EQ(nums[j], m[j][0]);
        ASSERT_LE(m[j].size(), 4);
    }
}