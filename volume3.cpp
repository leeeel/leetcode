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

[[maybe_unused]] int main() {
    return 0;
}