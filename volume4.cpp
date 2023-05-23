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

[[maybe_unused]] int main() {
    return 0;
}