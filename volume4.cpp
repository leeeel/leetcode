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

class [[maybe_unused]] Solution1373 {
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
    [[maybe_unused]] int maxSumBST(TreeNode *root) {
        res = 0;
        dfs(root);

        return res;
    }
};

class [[maybe_unused]] Solution979 {
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
    [[maybe_unused]] int distributeCoins(TreeNode *root) {
        dfs(root);

        return res;
    }
};

class [[maybe_unused]] Solution968 {
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
    [[maybe_unused]] int minCameraCover(TreeNode *root) {
        if (dfs(root) == 0) {
            res++;
        }

        return res;
    }
};

class [[maybe_unused]] Solution662 {
public:
    [[maybe_unused]] static int widthOfBinaryTree(TreeNode *root) {
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

class [[maybe_unused]] Solution90 {
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
    [[maybe_unused]] vector<vector<int>> subsetsWithDup(vector<int> &nums) {
        n = nums.size();
        sort(nums.begin(), nums.end());
        dfs(nums, 0);

        return res;
    }
};

class [[maybe_unused]] Solution {
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
            if(!visited[node]){
                res += dfs(node, graph, visited, newTime, target);
            }
        }

        return res / size;
    }

public:
    [[maybe_unused]]  double frogPosition(int n, vector<vector<int>> &edges, int t, int target) {
        vector<vector<int>> graph(n + 1);
        vector<bool> visited(n + 1, false);

        for (auto &edge: edges) {
            graph[edge[0]].emplace_back(edge[1]);
            graph[edge[1]].emplace_back(edge[0]);
        }

        return dfs(1, graph, visited, t, target);
    }
};

class [[maybe_unused]] Solution133 {
public:
    [[maybe_unused]] static GraphNode *cloneGraph(GraphNode *node) {
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

[[maybe_unused]] int main() {
    return 0;
}