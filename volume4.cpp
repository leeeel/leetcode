#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class Solution992 {
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
    static int subarraysWithKDistinct(vector<int> &nums, int k) {
        return helper(nums, k) - helper(nums, k - 1);
    }
};

class Solution1373 {
private:
    struct subTree {
        int maxVal;
        int minVal;
        int sumVal;
        bool isBST;

        explicit subTree(int maxVal, int minVal, int sumVal, bool isBST) : maxVal(maxVal), minVal(minVal), sumVal(sumVal), isBST(isBST) {}
    };

    int res;

    subTree dfs(TreeNode *root) {
        if (root == nullptr) {
            return subTree(INT_MIN, INT_MAX, 0, true);
        }

        auto leftSubTree = dfs(root->left);
        auto rightSubTree = dfs(root->right);

        if (leftSubTree.isBST && rightSubTree.isBST && leftSubTree.maxVal < root->val && rightSubTree.minVal > root->val) {
            int sum = root->val + leftSubTree.sumVal + rightSubTree.sumVal;
            res = max(res, sum);
            return subTree(max(rightSubTree.maxVal, root->val), min(leftSubTree.minVal, root->val), sum, true);
        } else {
            return subTree(0, 0, 0, false);
        }
    }

public:
    int maxSumBST(TreeNode *root) {
        res = 0;
        dfs(root);

        return res;
    }
};

class Solution979 {
private:
    int res = 0;

    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        auto left = dfs(root->left);
        auto right = dfs(root->right);
        res += abs(left) + abs(right);

        return left + right + root->val - 1;
    }

public:
    int distributeCoins(TreeNode *root) {
        dfs(root);

        return res;
    }
};

class Solution968 {
private:
    int res = 0;

    int dfs(TreeNode *root) {
        if (root == nullptr) {
            return 1;
        }

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        // 0 -- not covered, 1 -- covered, 2 -- camera
        if (left == 0 || right == 0) {
            res++;
            return 2;
        } else if (left == 2 || right == 2) {
            return 1;
        } else if (left == 1 && right == 1) {
            return 0;
        }

        return -1;
    }

public:
    int minCameraCover(TreeNode *root) {
        if (dfs(root) == 0) {
            res++;
        }

        return res;
    }
};

class Solution662 {
public:
    static int widthOfBinaryTree(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        unsigned int res = 1;
        vector<pair<TreeNode *, unsigned int>> arr;
        arr.emplace_back(root, 1);

        while (!arr.empty()) {
            int n = int(arr.size());
            res = max(res, arr[n - 1].second - arr[0].second + 1);

            for (int i = 0; i < n; ++i) {
                auto [node, index] = arr[i];

                if (node->left != nullptr) {
                    arr.emplace_back(node->left, index * 2);
                }
                if (node->right != nullptr) {
                    arr.emplace_back(node->right, index * 2 + 1);
                }
            }

            arr.erase(arr.begin(), arr.begin() + n);
        }

        return int(res);
    }
};

class Solution90 {
private:
    vector<vector<int>> res;
    vector<int> subset;
    unsigned int n;

    void dfs(vector<int> &nums, int startIdx) {
        res.emplace_back(subset);

        for (int i = startIdx; i < n; ++i) {
            if (i != startIdx && nums[i] == nums[i - 1]) {
                continue;
            }

            subset.emplace_back(nums[i]);
            dfs(nums, i + 1);
            subset.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        n = nums.size();
        sort(nums.begin(), nums.end());
        dfs(nums, 0);

        return res;
    }
};

class Solution1377 {
private:
    double dfs(int index, vector<vector<int>> &graph, vector<bool> &visited, int t, int target) {
        unsigned int size = index == 1 ? graph[index].size() : graph[index].size() - 1;
        if (t == 0 || size == 0) {
            return index == target ? 1.0 : 0;
        }

        double res = 0;
        int newTime = --t;
        visited[index] = true;

        for (auto node: graph[index]) {
            if (!visited[node]) {
                res += dfs(node, graph, visited, newTime, target);
            }
        }

        return res / size;
    }

public:
    double frogPosition(int n, vector<vector<int>> &edges, int t, int target) {
        vector<vector<int>> graph(n + 1);
        vector<bool> visited(n + 1, false);

        for (auto &edge: edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        return dfs(1, graph, visited, t, target);
    }
};

class Solution133 {
public:
    static GraphNode *cloneGraph(GraphNode *node) {
        if (node == nullptr) {
            return nullptr;
        }

        queue<GraphNode *> q;
        q.push(node);
        unordered_map<GraphNode *, GraphNode *> visited;
        visited[node] = new GraphNode(node->val);

        while (!q.empty()) {
            auto temp = q.front();
            q.pop();
            for (auto &neighbor: temp->neighbors) {
                if (visited.find(neighbor) == visited.end()) {
                    visited[neighbor] = new GraphNode(neighbor->val);
                    q.emplace(neighbor);
                }

                visited[temp]->neighbors.emplace_back(visited[neighbor]);
            }
        }

        return visited[node];
    }
};

class Solution382 {
private:
    ListNode *head = nullptr;

public:
    explicit Solution382(ListNode *node) {
        this->head = node;
    }

    int getRandom() {
        int i = 1;
        int res = 0;
        for (auto node = this->head; node != nullptr; node = node->next, i++) {
            //            if (rand() % i == 0) {
            res = node->val;
            //            }
        }

        return res;
    }
};

class Solution115 {
public:
    static int numDistinct(string s, string t) {
        unsigned int m = s.size(), n = t.size();
        if (m < n) {
            return 0;
        }

        vector<vector<unsigned int>> dp(m + 1, vector<unsigned int>(n + 1, 0));
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return int(dp[m][n]);
    }
};

class Solution115_1 {
public:
    static int numDistinct(string s, string t) {
        unsigned int m = s.size(), n = t.size();
        if (m < n) {
            return 0;
        }

        vector<unsigned int> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= m; ++i) {
            for (int j = int(n); j >= 1; --j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return int(dp[n]);
    }
};

class Solution1438 {
public:
    static int longestSubarray(vector<int> &nums, int limit) {
        int res = 0;
        int right = 0, left = 0;
        unsigned int n = nums.size();
        deque<int> maxQue, minQue;

        while (right < n) {
            while (!maxQue.empty() && maxQue.back() < nums[right]) {
                maxQue.pop_back();
            }
            maxQue.push_back(nums[right]);
            while (!minQue.empty() && minQue.back() > nums[right]) {
                minQue.pop_back();
            }
            minQue.push_back(nums[right]);

            while (left <= right && maxQue.front() - minQue.front() > limit) {
                if (maxQue.front() == nums[left]) {
                    maxQue.pop_front();
                }
                if (minQue.front() == nums[left]) {
                    minQue.pop_front();
                }

                left++;
            }

            res = max(res, right - left + 1);
            right++;
        }

        return res;
    }
};

class NumMatrix304 {
private:
    vector<vector<int>> sums;

public:
    explicit NumMatrix304(vector<vector<int>> &matrix) {
        unsigned int m = matrix.size();
        unsigned int n = matrix[0].size();
        sums = vector<vector<int>>(m, vector<int>(n, 0));

        sums[0][0] = matrix[0][0];
        for (int j = 1; j < n; ++j) {
            sums[0][j] = sums[0][j - 1] + matrix[0][j];
        }
        for (int i = 1; i < m; ++i) {
            sums[i][0] = sums[i - 1][0] + matrix[i][0];
            for (int j = 1; j < n; ++j) {
                sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int a = sums[row2][col2];
        int b = row1 == 0 || col1 == 0 ? 0 : sums[row1 - 1][col1 - 1];
        int c = row1 == 0 ? 0 : sums[row1 - 1][col2];
        int d = col1 == 0 ? 0 : sums[row2][col1 - 1];

        return a + b - c - d;
    }
};

class NumMatrix304_1 {
private:
    vector<vector<int>> sums;

public:
    explicit NumMatrix304_1(vector<vector<int>> &matrix) {
        unsigned int m = matrix.size();
        unsigned int n = matrix[0].size();
        sums = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2 + 1][col2 + 1] + sums[row1][col1] - sums[row1][col2 + 1] - sums[row2 + 1][col1];
    }
};

class Solution1314 {
public:
    static vector<vector<int>> matrixBlockSum(vector<vector<int>> &mat, int k) {
        unsigned int m = mat.size();
        unsigned int n = mat[0].size();
        vector<vector<int>> sums = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + mat[i][j];
            }
        }

        vector<vector<int>> res(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int row1 = max(0, i - k);
                int col1 = max(0, j - k);
                int row2 = min(int(m) - 1, i + k);
                int col2 = min(int(n) - 1, j + k);
                res[i][j] = sums[row2 + 1][col2 + 1] + sums[row1][col1] - sums[row1][col2 + 1] - sums[row2 + 1][col1];
            }
        }

        return res;
    }
};

class Solution797 {
private:
    vector<vector<int>> res;
    vector<int> path;
    int target;

    void dfs(int index, vector<vector<int>> &graph) {
        if (index == target) {
            res.emplace_back(path);
            return;
        }


        for (auto &next: graph[index]) {
            path.emplace_back(next);
            dfs(next, graph);
            path.pop_back();
        }
    }

public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph) {
        target = int(graph.size()) - 1;
        path.emplace_back(0);
        dfs(0, graph);

        return res;
    }
};
