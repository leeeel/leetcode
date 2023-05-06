#include "bits/stdc++.h"

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class [[maybe_unused]] Solution1487 {
public:
    static string addSuffix(string str, int num) {
        return str.append("(" + to_string(num) + ")");
    }

    [[maybe_unused]] static vector<string> getFolderNames(vector<string> &names) {
        vector<string> res;
        unordered_map<string, int> mp;

        for (auto &name: names) {
            if (!mp.count(name)) {
                mp[name]++;
                res.push_back(name);
            } else {
                int version = mp[name];
                while (mp.count(addSuffix(name, version))) {
                    version++;
                }

                mp[addSuffix(name, version)]++;
                mp[name] = version;
                res.push_back(addSuffix(name, version));
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1642 {
public:
    [[maybe_unused]] static int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
        unsigned int n = heights.size();
        priority_queue<int, vector<int>, greater<>> pq;

        for (int i = 1; i < n; ++i) {
            int gap = heights[i] - heights[i - 1];
            if (gap > 0) {
                pq.push(gap);
                int temp = 0;
                if (pq.size() > ladders) {
                    temp = pq.top();
                    pq.pop();
                }
                if (temp > bricks) {
                    return i - 1;
                } else {
                    bricks -= temp;
                }
            }
        }

        return int(n) - 1;
    }
};

class [[maybe_unused]] Solution1010 {
public:
    [[maybe_unused]] static int numPairsDivisibleBy60(vector<int> &time) {
        long int res = 0;
        unordered_map<int, int> mp;

        for (int &t: time) {
            mp[t % 60]++;
        }

        // [1, 29]
        for (int i = 1; i < 30; ++i) {
            res += mp[i] * mp[60 - i];
        }

        // [30, 30]
        res += (long) mp[30] * (mp[30] - 1) / 2;
        // [0, 0]
        res += (long) mp[0] * (mp[0] - 1) / 2;

        return (int) res;
    }
};

class [[maybe_unused]] Solution513 {
public:
    [[maybe_unused]] static int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        int res;

        q.push(root);
        res = root->val;

        while (!q.empty()) {
            unsigned int size = q.size();

            for (int i = 0; i < size; i++) {
                auto temp = q.front();
                q.pop();

                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (temp->left != nullptr) {
                    q.push(temp->left);
                }

                res = temp->val;    // right -> left
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution165 {
public:
    [[maybe_unused]] static int compareVersion(string version1, string version2) {
        int i = 0, j = 0;
        unsigned int m = version1.size(), n = version2.size();

        while (i < m || j < n) {
            unsigned int num1 = 0, num2 = 0;

            for (; i < m && version1[i] != '.'; ++i) {
                num1 = num1 * 10 + version1[i] - '0';
            }
            for (; j < n && version2[j] != '.'; ++j) {
                num2 = num2 * 10 + version2[j] - '0';
            }

            if (num1 < num2) {
                return -1;
            } else if (num1 > num2) {
                return 1;
            }

            i++, j++;
        }

        return 0;
    }
};

int main() {
    return 0;
}