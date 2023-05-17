#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class [[maybe_unused]] Solution679 {
private:
    constexpr static const int target = 24;
    constexpr static const double EPSILON = 1e-6;

    static bool solve(vector<double> &nums) {
        unsigned int m = nums.size();

        if (m == 1) {
            return abs(nums[0] - target) < EPSILON;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j == i) {
                    continue;
                }

                vector<double> nums1;
                for (int k = 0; k < m; ++k) {
                    if (k == j || k == i) {
                        continue;
                    }
                    nums1.emplace_back(nums[k]);
                }

                double a = nums[i], b = nums[j];
                vector<double> nums2 = {a + b, a - b, a * b};
                if (b != 0) {
                    nums2.emplace_back(a / b);
                }

                unsigned int n = nums2.size();
                for (int k = 0; k < n; ++k) {
                    nums1.emplace_back(nums2[k]);
                    if (solve(nums1)) {
                        return true;
                    }
                    nums1.pop_back();
                }
            }
        }

        return false;
    }

public:
    [[maybe_unused]] static bool judgePoint24(vector<int> &cards) {
        unsigned int n = cards.size();
        vector<double> nums(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = double(cards[i]);
        }

        return solve(nums);
    }
};

[[maybe_unused]] int main() {
    return 0;
}