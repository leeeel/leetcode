#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class Solution1487 {
public:
    static string addSuffix(string str, int num) {
        return str.append("(" + to_string(num) + ")");
    }

    static vector<string> getFolderNames(vector<string> &names) {
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

class Solution1642 {
public:
    static int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
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

class Solution1010 {
public:
    static int numPairsDivisibleby60(vector<int> &time) {
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

class Solution513 {
public:
    static int findBottomLeftValue(TreeNode *root) {
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

                res = temp->val;// right -> left
            }
        }

        return res;
    }
};

class Solution165 {
public:
    static int compareVersion(string version1, string version2) {
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

class Solution1263 {
public:
    static int minPushBox(vector<vector<char>> &grid) {
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
        vector<vector<int>> dirs = {{0, 1},
                                    {0, -1},
                                    {1, 0},
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

class Solution92 {
public:
    static ListNode *reverseBetween(ListNode *head, int left, int right) {
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

class Solution1015 {
public:
    static int smallestRepunitDivByK(int k) {
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

class Solution1016 {
public:
    static bool queryString(string s, int n) {
        unsigned int m = s.size();
        unordered_set<int> set;

        for (int i = 0; i < m; ++i) {
            if (s[i] == '0') {
                continue;
            }
            int num = 1;

            for (int j = i + 1; num <= n; ++j) {
                set.insert(num);
                if (j == m) {
                    break;
                }
                num = (num << 1) | (s[j] - '0');
            }
        }

        return set.size() == n;
    }
};

class Solution224 {
public:
    static int calculate(string s) {
        int res = 0, op = 1;
        stack<int> stk;
        stk.push(op);
        unsigned int n = s.size();

        for (int i = 0; i < n; i++) {
            char ch = s[i];
            if (ch == ' ') {
                continue;
            } else if (ch == '(') {
                stk.push(op);
            } else if (ch == ')') {
                stk.pop();
            } else if (ch == '-') {
                op = -stk.top();
            } else if (ch == '+') {
                op = stk.top();
            } else {
                int num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                res += op * num;
                i--;
            }
        }

        return res;
    }
};

class Solution1096 {
public:
    static vector<string> braceExpansionII(string expression) {
        stack<char> op;// '{', '+', '*'
        stack<set<string>> st;
        unsigned int n = expression.size();

        auto cal = [&]() {
            auto strSet1 = st.top();
            st.pop();
            auto &strSet2 = st.top();
            st.pop();

            auto opr = op.top();
            if (opr == '+') {
                strSet1.merge(strSet2);
                st.emplace(strSet1);
            } else if (opr == '*') {
                set<string> temp;
                for (auto &str2: strSet2) {
                    for (auto &str1: strSet1) {
                        temp.insert(str2 + str1);
                    }
                }

                st.emplace(temp);
            }
            op.pop();
        };

        for (int i = 0; i < n; ++i) {
            switch (expression[i]) {
                case '{':
                    if (i > 0 && (expression[i - 1] == '}' || isalpha(expression[i - 1]))) {
                        op.emplace('*');
                    }
                    op.emplace(expression[i]);
                    continue;
                case '}':
                    while (!op.empty() && op.top() != '{') {
                        cal();
                    }
                    op.pop();
                    continue;
                case ',':
                    while (!op.empty() && op.top() == '*') {
                        cal();
                    }
                    op.emplace('+');
                    continue;
                default:
                    if (i > 0 && (expression[i - 1] == '}' || isalpha(expression[i - 1]))) {
                        op.emplace('*');
                    }
                    st.push({string(1, expression[i])});
            }
        }

        while (!op.empty()) {
            cal();
        }

        return {st.top().begin(), st.top().end()};
    }
};

class Solution264 {
public:
    static int nthUglyNumber(int n) {
        vector<int> dp(n + 1, 1);
        int p2 = 1, p3 = 1, p5 = 1;
        int num1, num2, num3;

        for (int i = 2; i <= n; ++i) {
            num1 = dp[p2] * 2;
            num2 = dp[p3] * 3;
            num3 = dp[p5] * 5;
            dp[i] = min(num1, min(num2, num3));
            if (num1 == dp[i]) {
                p2++;
            }
            if (num2 == dp[i]) {
                p3++;
            }
            if (num3 == dp[i]) {
                p5++;
            }
        }

        return dp[n];
    }
};

class Solution1023 {
public:
    static vector<bool> camelMatch(vector<string> &queries, string pattern) {
        unsigned int n = queries.size();
        unsigned int m = pattern.size();

        vector<bool> res(n, true);

        for (int i = 0; i < n; ++i) {
            int k = 0;
            for (char &c: queries[i]) {
                if (k < m && pattern[k] == c) {
                    k++;
                    continue;
                }
                if (isupper(c)) {
                    res[i] = false;
                    break;
                }
            }

            if (k != m) {
                res[i] = false;
            }
        }

        return res;
    }
};

class Solution1041 {
public:
    static bool isRobotBounded(const string &instructions) {
        int x = 0, y = 0, index = 0;
        int dx, dy;

        vector<vector<int>> dirs = {{0, 1},
                                    {1, 0},
                                    {0, -1},
                                    {-1, 0}};
        for (auto instruction: instructions) {
            if (instruction == 'R') {
                index = (index + 1) % 4;
            } else if (instruction == 'L') {
                index = (index + 3) % 4;
            } else {
                dx = dirs[index][0];
                dy = dirs[index][1];
                x += dx;
                y += dy;
            }
        }

        return index != 0 || (x == 0 && y == 0);
    }
};

class Solution1033 {
public:
    static vector<int> numMovesStones(int a, int b, int c) {
        vector<int> res(2, 0);
        int minNum = min({a, b, c});
        int maxNum = max({a, b, c});
        int midNum = a + b + c - minNum - maxNum;

        if (maxNum - midNum == 1 && midNum - minNum == 1) {
            res[0] = 0;
        } else if (maxNum - midNum <= 2 || midNum - minNum <= 2) {
            res[0] = 1;
        } else {
            res[0] = 2;
        }
        res[1] = maxNum - minNum - 2;

        return res;
    }
};

class Solution970 {
public:
    static vector<int> powerfulIntegers(int x, int y, int bound) {
        unordered_set<int> tempSet;
        int a = 0, b = 0;
        int sum = 0;

        if (x == 1) {
            a = 1;
        } else {
            while (pow(x, a) <= bound) {
                a++;
            }
        }
        if (y == 1) {
            b = 1;
        } else {
            while (pow(y, b) <= bound) {
                b++;
            }
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                sum = int(pow(x, i) + pow(y, j));
                if (sum <= bound) {
                    tempSet.emplace(sum);
                }
            }
        }

        return {tempSet.begin(), tempSet.end()};
    }
};

class Solution1376 {
public:
    static int numOfMinutes(int n, int headID, vector<int> &manager, vector<int> &informTime) {
        int res = 0;

        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < manager.size(); ++i) {
            mp[manager[i]].push_back(i);
        }

        queue<pair<int, int>> q;
        q.emplace(headID, 0);
        while (!q.empty()) {
            int unsigned size = q.size();

            for (int i = 0; i < size; ++i) {
                auto temp = q.front();
                q.pop();
                if (!mp[temp.first].empty()) {
                    for (auto item: mp[temp.first]) {
                        q.emplace(item, temp.second + informTime[temp.first]);
                    }
                } else {
                    res = max(res, temp.second);
                }
            }
        }

        return res;
    }
};

class Solution1003 {
public:
    static bool isValid(const string &s) {
        string st;

        for (auto ch: s) {
            st.push_back(ch);
            if (st.size() >= 3 && st.substr(st.size() - 3, 3) == "abc") {
                st.erase(st.size() - 3, 3);
            }
        }

        return st.empty();
    }
};

class Solution2106 {
public:
    static int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k) {
        int res = 0;
        int cnt = 0;

        auto steps = [&fruits, &startPos](int &i, int &j) -> int {
            return fruits[j][0] - fruits[i][0] + min(abs(startPos - fruits[i][0]), abs(startPos - fruits[j][0]));
        };

        for (int i = 0, j = 0; j < fruits.size(); ++j) {
            cnt += fruits[j][1];
            while (i <= j &&
                   steps(i, j) > k) {
                cnt -= fruits[i++][1];
            }

            res = max(res, cnt);
        }

        return res;
    }
};

class Solution692 {
public:
    static vector<string> topKFrequent(vector<string> &words, int k) {
        vector<string> res(k);
        unordered_map<string, int> cnt;

        for (const auto &word: words) {
            cnt[word]++;
        }

        auto cmp = [](const pair<string, int> &a, const pair<string, int> &b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        };

        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
        for (const auto &it: cnt) {
            pq.emplace(it);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        for (int i = k - 1; i >= 0; --i) {
            res[i] = pq.top().first;
            pq.pop();
        }

        return res;
    }
};

class Solution2432 {
public:
    static int hardestWorker(int n, vector<vector<int>> &logs) {
        int res = logs[0][0];
        int maxCost = logs[0][1];

        for (int i = 1; i < logs.size(); ++i) {
            int curCost = logs[i][1] - logs[i - 1][1];

            if (curCost > maxCost || curCost == maxCost && logs[i][0] < res) {
                res = logs[i][0];
                maxCost = curCost;
            }
        }

        return res;
    }
};

class Solution1497 {
public:
    static bool canArrange(vector<int> &arr, int k) {
        unordered_map<int, int> mp;
        for (auto &num: arr) {
            mp[(num % k + k) % k]++;
        }
        for (auto [key, value]: mp) {
            if (key != 0 && (mp.count(k - key) == 0 || mp[k - key] != value)) {
                return false;
            }
        }

        return mp[0] % 2 == 0;
    }
};

class Solution1344 {
public:
    static double angleClock(int hour, int minutes) {
        double minuteAngle = minutes == 60 ? 0 : minutes * 6;
        double hourAngle = (hour == 12 ? 0 : hour * 30) + double(minutes) / 2.0;
        double res = abs(hourAngle - minuteAngle);

        return res > 180 ? 360 - res : res;
    }
};

class Solution199 {
public:
    static vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        queue<TreeNode *> q;

        if (root != nullptr) {
            q.emplace(root);
        }

        while (!q.empty()) {
            unsigned int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *temp = q.front();
                q.pop();

                if (temp->left != nullptr) {
                    q.push(temp->left);
                }
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (i == size - 1) {
                    res.emplace_back(temp->val);
                }
            }
        }

        return res;
    }
};