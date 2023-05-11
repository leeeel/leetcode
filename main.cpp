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

struct ListNode {
    [[maybe_unused]] int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    [[maybe_unused]] explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
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
    [[maybe_unused]] static int numPairsDivisibleby60(vector<int> &time) {
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

class [[maybe_unused]] Solution1263 {
public:
    [[maybe_unused]] static int minPushBox(vector<vector<char>> &grid) {
        int m = int(grid.size());
        int n = int(grid[0].size());
        int sx = 0, sy = 0;
        int bx = 0, by = 0;
        int tx = 0, ty = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    sx = i, sy = j;
                    continue;
                }
                if (grid[i][j] == 'B') {
                    bx = i, by = j;
                }
                if (grid[i][j] == 'T') {
                    tx = i, ty = j;
                }
            }
        }

        auto f = [&](int &i, int &j) -> int {
            return i * n + j;
        };
        auto check = [&](int &i, int &j) -> bool {
            return i >= 0 && i < m && j >= 0 && j < n && grid[i][j] != '#';
        };

        deque<tuple<int, int, int>> q;
        q.emplace_back(f(sx, sy), f(bx, by), 0);
        vector<vector<bool>> visited(m * n, vector<bool>(m * n, false));
        visited[f(sx, sy)][f(bx, by)] = true;
        vector<vector<int>> dirs = {{0,  1},
                                    {0,  -1},
                                    {1,  0},
                                    {-1, 0}};

        while (!q.empty()) {
            auto [s, b, d] = q.front();
            q.pop_front();

            sx = s / n;
            sy = s % n;
            bx = b / n;
            by = b % n;

            if (bx == tx && ty == by) {
                return d;
            }

            for (int i = 0; i < 4; ++i) {
                int dx = dirs[i][0];
                int dy = dirs[i][1];

                int ssx = sx + dx;
                int ssy = sy + dy;
                if (!check(ssx, ssy)) {
                    continue;
                }

                if (ssx == bx && ssy == by) {
                    int bbx = bx + dx;
                    int bby = by + dy;
                    if (!check(bbx, bby) || visited[f(ssx, ssy)][f(bbx, bby)]) {
                        continue;
                    }

                    visited[f(ssx, ssy)][f(bbx, bby)] = true;
                    q.emplace_back(f(ssx, ssy), f(bbx, bby), d + 1);
                } else if (!visited[f(ssx, ssy)][f(bx, by)]) {
                    visited[f(ssx, ssy)][f(bx, by)] = true;
                    q.emplace_front(f(ssx, ssy), f(bx, by), d);
                }
            }
        }

        return -1;
    }
};

class [[maybe_unused]] Solution92 {
public:
    [[maybe_unused]] static ListNode *reverseBetween(ListNode *head, int left, int right) {
        auto *dummy = new ListNode(0, head);
        auto *pre = dummy;

        for (int i = 0; i < left - 1; ++i) {
            pre = pre->next;
        }
        auto cur = pre->next;

        for (int j = 0; j < right - left; ++j) {
            auto temp = cur->next;
            cur->next = temp->next;
            temp->next = pre->next;
            pre->next = temp;
        }

        return dummy->next;
    }
};

class [[maybe_unused]] Solution1015 {
public:
    [[maybe_unused]] static int smallestRepunitDivByK(int k) {
        int res = 1;
        int num = 1;

        for (int i = 0; i < k; ++i, ++res) {
            if (num % k == 0) {
                return res;
            }
            num = (num * 10 + 1) % k;
        }

        return -1;
    }
};

class [[maybe_unused]] Solution1016 {
public:
    [[maybe_unused]] static bool queryString(string s, int n) {
        unsigned int m = s.size();
        unordered_set<int> set;

        for (int i = 0; i < m; ++i) {
            if (s[i] == '0') {
                continue;
            }
            int num = 1;

            for (int j = i + 1; num <= n; ++j) {
                set.insert(num);
                if (j== m) {
                    break;
                }
                num = (num << 1) | (s[j] - '0');
            }
        }

        return set.size() == n;
    }
};

int main() {
    return 0;
}