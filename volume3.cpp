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

class [[maybe_unused]] Solution1335 {
public:
    [[maybe_unused]] static int minDifficulty(vector<int> &jobDifficulty, int d) {
        unsigned int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }

        vector<vector<int>> dp(d + 1, vector<int>(n + 1, INT_MAX / 2));
        dp[0][0] = 0;

        for (int i = 1; i <= d; ++i) {
            for (int j = i; j <= n; ++j) {
                int difficulty = 0;
                for (int k = j; k >= i; k--) {
                    difficulty = max(jobDifficulty[k - 1], difficulty);
                    dp[i][j] = min(dp[i][j], dp[i - 1][k - 1] + difficulty);
                }
            }
        }

        return dp[d][n];
    }
};

class [[maybe_unused]] Solution1335_1 {
public:
    [[maybe_unused]] static int minDifficulty(vector<int> &jobDifficulty, int d) {
        unsigned int n = jobDifficulty.size();
        if (n < d) {
            return -1;
        }

        vector<int> dp(n + 1, INT_MAX / 2);
        dp[0] = 0;

        for (int i = 1; i <= d; ++i) {
            for (int j = int(n); j >= i; --j) {
                int difficulty = 0;
                dp[j] = INT_MAX / 2;
                for (int k = j; k >= i; k--) {
                    difficulty = max(jobDifficulty[k - 1], difficulty);
                    dp[j] = min(dp[j], dp[k - 1] + difficulty);
                }
            }
        }

        return dp[n];
    }
};

class [[maybe_unused]] Solution1458 {
public:
    [[maybe_unused]] static int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        unsigned m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MIN));

        dp[0][0] = nums1[0] * nums2[0];
        for (int i = 1; i < m; ++i) {
            dp[i][0] = max(dp[i - 1][0], nums1[i] * nums2[0]);
        }
        for (int j = 1; j < n; ++j) {
            dp[0][j] = max(dp[0][j - 1], nums1[0] * nums2[j]);
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                int num = nums1[i] * nums2[j];
                dp[i][j] = max({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] + num, num});
            }
        }

        return dp[m - 1][n - 1];
    }
};

class [[maybe_unused]] Solution1458_1 {
private:
    static int helper(vector<int> &nums1, vector<int> &nums2) {
        unsigned m = nums1.size(), n = nums2.size();
        vector<int> dp(n);
        vector<int> memo(n);

        dp[0] = nums1[0] * nums2[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1], nums1[0] * nums2[i]);
        }
        memo = dp;

        for (int i = 1; i < m; i++) {
            dp[0] = max(dp[0], nums1[i] * nums2[0]);
            for (int j = 1; j < n; j++) {
                int num = nums1[i] * nums2[j];
                dp[j] = max({dp[j], dp[j - 1], memo[j - 1] + num, num});
            }
            memo = dp;
        }

        return dp[n - 1];
    }

public:
    [[maybe_unused]] static int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        return nums1.size() >= nums2.size() ? helper(nums1, nums2) : helper(nums2, nums1);
    }
};

class [[maybe_unused]] Solution1458_2 {
private:
    static int helper(vector<int> &nums1, vector<int> &nums2) {
        unsigned m = nums1.size(), n = nums2.size();
        vector<int> dp(n);

        dp[0] = nums1[0] * nums2[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(dp[i - 1], nums1[0] * nums2[i]);
        }

        for (int i = 1; i < m; i++) {
            int prev = dp[0];
            dp[0] = max(dp[0], nums1[i] * nums2[0]);
            for (int j = 1; j < n; j++) {
                int temp = dp[j];
                int num = nums1[i] * nums2[j];

                dp[j] = max({dp[j], dp[j - 1], prev + num, num});
                prev = temp;
            }
        }

        return dp[n - 1];
    }

public:
    [[maybe_unused]] static int maxDotProduct(vector<int> &nums1, vector<int> &nums2) {
        return nums1.size() >= nums2.size() ? helper(nums1, nums2) : helper(nums2, nums1);
    }
};

class [[maybe_unused]] Solution_2477 {
private:
    long long res = 0;

    int dfs(int prevIdx, int curIdx, vector<vector<int>> &graph, int &seats) {
        int cnt = 1;

        for (auto nextIdx: graph[curIdx]) {
            if (nextIdx != prevIdx) {
                cnt += dfs(curIdx, nextIdx, graph, seats);
            }
        }

        if (curIdx > 0) {
            res += int(ceil(cnt * 1.0 / seats));
        }

        return cnt;
    }

public:
    [[maybe_unused]] long long minimumFuelCost(vector<vector<int>> &roads, int seats) {
        unsigned int n = roads.size();

        vector<vector<int>> graph(n + 1);
        for (auto &road: roads) {
            graph[road[0]].emplace_back(road[1]);
            graph[road[1]].emplace_back(road[0]);
        }

        dfs(-1, 0, graph, seats);

        return res;
    }
};

class [[maybe_unused]] Solution1312 {
public:
    [[maybe_unused]] static int minInsertions(string s) {
        int n = int(s.size());
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                }
            }
        }

        return dp[0][n - 1];
    }
};

class [[maybe_unused]] Solution1312_1 {
public:
    [[maybe_unused]] static int minInsertions(string s) {
        int n = int(s.size());
        vector<int> dp(n, 0);

        for (int i = n - 1; i >= 0; --i) {
            int prev = 0;
            for (int j = i + 1; j < n; ++j) {
                int temp = dp[j];

                if (s[i] == s[j]) {
                    dp[j] = prev;
                } else {
                    dp[j] = min(dp[j], dp[j - 1]) + 1;
                }

                prev = temp;
            }
        }

        return dp[n - 1];
    }
};

class [[maybe_unused]] Solution713 {
public:
    [[maybe_unused]] static int numSubarrayProductLessThanK(vector<int> &nums, int k) {
        int res = 0;
        int left = 0, right = 0;
        int mul = 1;
        unsigned int n = nums.size();

        while (right < n) {
            mul *= nums[right];
            while (left <= right && mul >= k) {
                mul /= nums[left];
                left++;
            }
            res += right - left + 1;
            right++;
        }

        return res;
    }
};

class [[maybe_unused]] Solution_209 {
public:
    [[maybe_unused]] static int minSubArrayLen(int target, vector<int> &nums) {
        int left = 0, right = 0;
        unsigned int n = nums.size();
        int sum = 0;
        int res = INT_MAX;

        while (right < n) {
            sum += nums[right];
            while (sum >= target) {
                res = min(res, right - left + 1);
                sum -= nums[left++];
            }
            right++;
        }

        return res == INT_MAX ? 0 : res;
    }
};

class [[maybe_unused]] Solution97 {
public:
    [[maybe_unused]] static bool isInterleave(string &s1, string &s2, string &s3) {
        unsigned int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3) {
            return false;
        }

        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));
        dp[0][0] = true;
        for (int i = 1; i <= n1; ++i) {
            dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
        }
        for (int j = 1; j <= n2; ++j) {
            dp[0][j] = dp[0][j - 1] && s2[j - 1] == s3[j - 1];
        }

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                bool cond1 = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]);
                bool cond2 = (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
                dp[i][j] = cond1 || cond2;
            }
        }

        return dp[n1][n2];
    }
};

class [[maybe_unused]] Solution97_1 {
private:
    static bool helper(string &s1, string &s2, string &s3) {
        unsigned m = s1.size(), n = s2.size();
        vector<bool> dp(n + 1, false);

        dp[0] = true;
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
        }

        for (int i = 1; i <= m; ++i) {
            dp[0] = dp[0] && s1[i - 1] == s3[i - 1];
            for (int j = 1; j <= n; ++j) {
                bool cond1 = (dp[j] && s1[i - 1] == s3[i + j - 1]);
                bool cond2 = (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
                dp[j] = cond1 || cond2;
            }
        }

        return dp[n];
    }

public:
    [[maybe_unused]] static bool isInterleave(string &s1, string &s2, string &s3) {
        unsigned int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        if (n1 + n2 != n3) {
            return false;
        }

        return n1 >= n2 ? helper(s1, s2, s3) : helper(s2, s1, s3);
    }
};

class [[maybe_unused]] Solution1049 {
public:
    [[maybe_unused]] static int lastStoneWeightII(vector<int> &stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        unsigned int n = stones.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= target; ++j) {
                if (j < stones[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - stones[i - 1]];
                }
            }
        }
        for (int j = target; j >= 0; --j) {
            if (dp[n][j]) {
                target = j;
                break;
            }
        }

        return sum - 2 * target;
    }
};

class [[maybe_unused]] Solution1049_1 {
public:
    [[maybe_unused]] static int lastStoneWeightII(vector<int> &stones) {
        int sum = accumulate(stones.begin(), stones.end(), 0);
        int target = sum / 2;
        unsigned int n = stones.size();
        vector<bool> dp(target + 1, false);

        dp[0] = true;
        for (int i = 1; i <= n; ++i) {
            for (int j = target; j >= 0; --j) {
                if (j >= stones[i - 1]) {
                    dp[j] = dp[j] || dp[j - stones[i - 1]];
                }
            }
        }
        for (int j = target; j >= 0; --j) {
            if (dp[j]) {
                target = j;
                break;
            }
        }

        return sum - 2 * target;
    }
};

class [[maybe_unused]] Solution1248 {
public:
    [[maybe_unused]] static int numberOfSubarrays(vector<int> &nums, int k) {
        int right = 0, left = 0, flag = 0;
        unsigned int n = nums.size();
        int res = 0;
        int cnt = 0;

        while (right < n) {
            cnt += nums[right++] & 1;

            while (left <= right && cnt > k) {
                cnt -= nums[left++] & 1;
                flag = left;
            }
            while (flag <= right && !(nums[flag] & 1)) {
                flag++;
            }

            if (cnt == k) {
                res += flag - left + 1;
            }
        }

        return res;
    }
};

[[maybe_unused]] int main() {
    return 0;
}