#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class [[maybe_unused]] Solution992 {
private:
    static int helper(vector<int> &nums, int k) {
        int left = 0, right = 0;
        unordered_map<int, int> mp;
        unsigned int n = nums.size();
        int res = 0;
        int cnt = 0;

        while (right < n) {
            if (!mp[nums[right]]++) {
                cnt++;
            }

            while (left <= right && cnt > k) {
                if (!--mp[nums[left++]]) {
                    cnt--;
                }
            }

            res += right - left + 1;
            right++;
        }

        return res;
    }

public:
    [[maybe_unused]] static int subarraysWithKDistinct(vector<int> &nums, int k) {
        return helper(nums, k) - helper(nums, k - 1);
    }
};


[[maybe_unused]] int main() {
    return 0;
}