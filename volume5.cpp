#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class [[maybe_unused]] Solution1162 {
public:
    [[maybe_unused]] static int maxDistance(vector<vector<int>> &grid) {
        unsigned int n = grid.size();
        const vector<vector<int>> dirs = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
        queue<pair<int, int>> q;
        int res = -1;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j]) {
                    q.emplace(i, j);
                }
            }
        }

        if (q.empty() || q.size() == n * n) {
            return res;
        }

        while (!q.empty()) {
            res++;
            unsigned int size = q.size();

            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (auto &dir: dirs) {
                    int newX = x + dir[0];
                    int newY = y + dir[1];

                    if (newX < 0 || newX >= n || newY < 0 || newY >= n || grid[newX][newY] == 1) {
                        continue;
                    }

                    grid[newX][newY] = 1;
                    q.emplace(newX, newY);
                }
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution848 {
public:
    [[maybe_unused]] static string shiftingLetters(string s, vector<int> &shifts) {
        int n = int(shifts.size());
        for (int i = n - 1; i >= 1; --i) {
            shifts[i - 1] += shifts[i];
            shifts[i - 1] %= 26;
        }

        for (int i = 0; i < n; ++i) {
            s[i] = char((s[i] - 'a' + shifts[i]) % 26);
            s[i] += 'a';
        }

        return s;
    }
};

class [[maybe_unused]] Solution137 {
public:
    [[maybe_unused]] static int singleNumber(vector<int> &nums) {
        int res = 0;

        for (int i = 0; i < 32; ++i) {
            int cnt = 0;
            for (int num: nums) {
                if (num >> i & 1) {
                    cnt++;
                }
            }

            res |= (cnt % 3) << i;
        }

        return res;
    }
};

class [[maybe_unused]] Solution1123 {
public:
    [[maybe_unused]] static TreeNode *lcaDeepestLeaves(TreeNode *root) {
        function<pair<TreeNode *, int>(TreeNode *, int)> dfs = [&](TreeNode *node, int depth) -> pair<TreeNode *, int> {
            if (node == nullptr) {
                return {nullptr, depth};
            }

            auto [leftNode, leftDepth] = dfs(node->left, depth + 1);
            auto [rightNode, rightDepth] = dfs(node->right, depth + 1);

            if (leftDepth > rightDepth) {
                return {leftNode, leftDepth};
            }
            if (leftDepth < rightDepth) {
                return {rightNode, rightDepth};
            }
            return {node, leftDepth};
        };

        auto [res, depth] = dfs(root, 0);

        return res;
    }
};

class [[maybe_unused]] Solution1439 {
public:
    [[maybe_unused]] static int kthSmallest(vector<vector<int>> &mat, int k) {
        unsigned int m = mat.size();
        priority_queue<int> pq;
        vector<int> sums = mat[0];

        for (int i = 1; i < m; ++i) {
            for (auto &x: sums) {
                for (auto &y: mat[i]) {
                    int num = x + y;
                    if (pq.size() < k) {
                        pq.emplace(num);
                    } else if (pq.top() > num) {
                        pq.pop();
                        pq.emplace(num);
                    }
                }
            }

            sums.clear();
            while (!pq.empty()) {
                sums.emplace_back(pq.top());
                pq.pop();
            }
        }

        if (m != 1) {
            reverse(sums.begin(), sums.end());
        }

        return sums[k - 1];
    }
};

[[maybe_unused]] int main() {
    vector<vector<int>> test = {{1, 10, 10}, {1, 4, 5}, {2, 3, 6}};
    cout << Solution1439::kthSmallest(test, 7);
    return 0;
}
