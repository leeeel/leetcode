#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class [[maybe_unused]] Solution1162 {
public:
    [[maybe_unused]] static int maxDistance(vector<vector<int>> &grid) {
        unsigned int n = grid.size();
        const vector<vector<int>> dirs = {{0, 1},
                                          {0, -1},
                                          {-1, 0},
                                          {1, 0}};
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

class [[maybe_unused]] Solution974 {
public:
    [[maybe_unused]] static int subarraysDivByK(vector<int> &nums, int k) {
        int res = 0;
        int preSum = 0;
        unordered_map<int, int> cnt = {{0, 1}};

        for (auto &num: nums) {
            preSum += num;
            int key = (preSum % k + k) % k;
            res += cnt[key];
            cnt[key]++;
        }

        return res;
    }
};

class [[maybe_unused]] Solution611 {
public:
    [[maybe_unused]] static int triangleNumber(vector<int> &nums) {
        int res = 0;
        unsigned int n = nums.size();
        sort(nums.begin(), nums.end());

        for (int i = 0; i < n; ++i) {
            for (int k = i + 1, j = i + 2; j < n; ++j) {
                while (k < j & nums[i] + nums[k] <= nums[j]) {
                    k++;
                }
                res += j - k;
            }
        }
        return res;
    }
};

class [[maybe_unused]] Solution567 {
public:
    [[maybe_unused]] static bool checkInclusion(string &s1, string s2) {
        unsigned int m = s1.size(), n = s2.size();
        if (m > n) {
            return false;
        }

        vector<int> cnt(26, 0);
        for (auto &ch: s1) {
            cnt[ch - 'a']++;
        }

        int left = 0, right = 0;
        while (right < n) {
            int ch = s2[right] - 'a';
            cnt[ch]--;

            while (cnt[ch] < 0) {
                cnt[s2[left++] - 'a']++;
            }

            if (right - left + 1 == m) {
                return true;
            }

            right++;
        }

        return false;
    }
};

class [[maybe_unused]] Solution1233 {
private:
    struct Trie {
        Trie() : index(-1) {}

        int index;
        unordered_map<string, Trie *> next;
    };

public:
    [[maybe_unused]] static vector<string> removeSubfolders(vector<string> &folder) {
        vector<string> res;
        Trie *root = new Trie();

        auto split = [](string &str) -> vector<string> {
            vector<string> res;
            const char splitCh = '/';
            string temp;

            for (auto &ch: str) {
                if (ch == splitCh) {
                    res.push_back(std::move(temp));
                    temp.clear();
                } else {
                    temp.push_back(ch);
                }
            }
            res.push_back(std::move(temp));

            return res;
        };

        function<void(Trie *)> dfs = [&](Trie *root) -> void {
            if (root->index != -1) {
                res.push_back(folder[root->index]);
                return;
            }

            for (auto &node: root->next) {
                dfs(node.second);
            }
        };

        for (int i = 0; i < folder.size(); i++) {
            vector<string> path = split(folder[i]);
            Trie *cur = root;

            for (auto &str: path) {
                if (!cur->next.count(str)) {
                    cur->next[str] = new Trie();
                }
                cur = cur->next[str];
            }

            cur->index = i;
        }

        dfs(root);

        return res;
    }
};

class [[maybe_unused]] Solution991 {
public:
    [[maybe_unused]] static int brokenCalc(int startValue, int target) {
        int res = 0;

        while (startValue < target) {
            if (target % 2 == 0) {
                target /= 2;
                res++;
            } else {
                target += 1;
                target /= 2;
                res += 2;
            }
        }

        return res + startValue - target;
    }
};

class [[maybe_unused]] Solution393 {
public:
    [[maybe_unused]] static bool validUtf8(vector<int> &data) {
        int bytesNum = 0;

        for (auto const &elem: data) {
            if (bytesNum == 0) {
                if (elem >> 5 == 0b110) {
                    bytesNum = 1;
                } else if (elem >> 4 == 0b1110) {
                    bytesNum = 2;
                } else if (elem >> 3 == 0b11110) {
                    bytesNum = 3;
                } else if (elem >> 7) {
                    return false;
                }
            } else {
                if (elem >> 6 != 0b10) {
                    return false;
                }
                bytesNum--;
            }
        }

        return bytesNum == 0;
    }
};

class [[maybe_unused]] Solution988 {
private:
    string res;

    void dfs(TreeNode *root, string str) {
        if (!root) {
            return;
        }

        str.push_back(char(root->val + 'a'));

        if (!root->left && !root->right) {
            reverse(str.begin(), str.end());

            if (res.empty() || res > str) {
                res = str;
            }

            return;
        }

        dfs(root->left, str);
        dfs(root->right, str);
    }

public:
    [[maybe_unused]] string smallestFromLeaf(TreeNode *root) {
        dfs(root, "");

        return res;
    }
};

class BSTIterator {
private:
    vector<int> traversalRes;
    int index;

    static void inorderTraversal(TreeNode *root, vector<int> &nums) {
        if (!root) {
            return;
        }

        inorderTraversal(root->left, nums);
        nums.push_back(root->val);
        inorderTraversal(root->right, nums);
    }

public:
    explicit BSTIterator(TreeNode *root) {
        index = 0;
        inorderTraversal(root, traversalRes);
    }

    int next() {
        return traversalRes[index++];
    }

    bool hasNext() {
        return index < traversalRes.size();
    }
};

class Solution109 {
private:
    vector<int> traversalRes;

    TreeNode *buildBST(int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int mid = (left + right) >> 1;
        auto *root = new TreeNode(traversalRes[mid]);

        root->left = buildBST(left, mid - 1);
        root->right = buildBST(mid + 1, right);

        return root;
    }

public:
    TreeNode *sortedListToBST(ListNode *head) {
        while (head != nullptr) {
            traversalRes.push_back(head->val);
            head = head->next;
        }

        return buildBST(0, int(traversalRes.size() - 1));
    }
};

class [[maybe_unused]] Solution980 {
public:
    [[maybe_unused]] static int uniquePathsIII(vector<vector<int>> &grid) {
        const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        unsigned int m = grid.size(), n = grid[0].size();

        int startX = 0, startY = 0;
        int endX = 0, endY = 0;
        int res = 0;
        int total = 0;

        auto check = [&](int x, int y) -> bool {
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == -1 || grid[x][y] == -1) {
                return false;
            }
            return true;
        };

        function<void(int, int, int)> dfs = [&](int x, int y, int cnt) -> void {
            if (cnt == total) {
                if (x == endX && y == endY) {
                    res++;
                }
                return;
            }

            for (int i = 0; i < 4; ++i) {
                int newX = x + dirs[i][0];
                int newY = y + dirs[i][1];

                if (check(newX, newY)) {
                    int temp = grid[newX][newY];
                    grid[newX][newY] = -1;
                    dfs(newX, newY, cnt + 1);
                    grid[newX][newY] = temp;
                }
            }
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    startX = i, startY = j;
                }
                if (grid[i][j] == 2) {
                    endX = i, endY = j;
                    total++;
                }
                if (grid[i][j] == 0) {
                    total++;
                }
            }
        }

        grid[startX][startY] = -1;
        dfs(startX, startY, 0);

        return res;
    }
};


int main() {
    return 0;
}
