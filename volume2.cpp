#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class Solution151 {
public:
    static string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int idx = 0;

        for (int start = 0; start < s.size(); ++start) {
            if (s[start] != ' ') {
                if (idx != 0) {
                    s[idx++] = ' ';
                }

                int end = start;
                while (end < s.size() && s[end] != ' ') {
                    s[idx++] = s[end++];
                }

                reverse(s.begin() + idx - (end - start), s.begin() + idx);
                start = end;
            }
        }

        s.erase(s.begin() + idx, s.end());

        return s;
    }
};

class Solution986 {
public:
    static vector<vector<int>>
    intervalIntersection(vector<vector<int>> &firstList, vector<vector<int>> &secondList) {
        vector<vector<int>> res;
        int i = 0, j = 0;
        unsigned int m = firstList.size(), n = secondList.size();

        while (i < m && j < n) {
            if (firstList[i][0] > secondList[j][1]) {
                j++;
                continue;
            }
            if (firstList[i][1] < secondList[j][0]) {
                i++;
                continue;
            }

            int left = max(firstList[i][0], secondList[j][0]);
            int right = min(firstList[i][1], secondList[j][1]);
            res.push_back({left, right});

            if (firstList[i][1] >= secondList[j][1]) {
                j++;
            } else {
                i++;
            }
        }

        return res;
    }
};

class Solution701 {
public:
    static TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        TreeNode *cur = root;

        //        if (val< root->val){
        //            if (root->left == nullptr){
        //                root->left = new TreeNode(val);
        //            }else{
        //                insertIntoBST(root->left,val);
        //            }
        //        }else{
        //            if (root->right == nullptr){
        //                root->right = new TreeNode(val);
        //            }else{
        //                insertIntoBST(root->right,val);
        //            }
        //        }

        while (true) {
            if (val < cur->val) {
                if (cur->left == nullptr) {
                    cur->left = new TreeNode(val);
                    break;
                } else {
                    cur = cur->left;
                }
            } else {
                if (cur->right == nullptr) {
                    cur->right = new TreeNode(val);
                    break;
                } else {
                    cur = cur->right;
                }
            }
        }

        return root;
    }
};

class Solution973 {
public:
    static vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        vector<vector<int>> res;
        priority_queue<pair<double, int>> pq;

        for (int i = 0; i < points.size(); ++i) {
            double dis = sqrt(pow(points[i][0], 2) + pow(points[i][1], 2));

            if (pq.size() < k) {
                pq.emplace(dis, i);
            } else {
                if (pq.top().first > dis) {
                    pq.pop();
                    pq.emplace(dis, i);
                }
            }
        }

        while (!pq.empty()) {
            res.emplace_back(points[pq.top().second]);
            pq.pop();
        }

        return res;
    }
};

class Solution1419 {
public:
    static int minNumberOfFrogs(string &croakOfFrogs) {
        unordered_map<char, int> mp = {{'c', 0},
                                       {'r', 1},
                                       {'o', 2},
                                       {'a', 3},
                                       {'k', 4}};
        vector<int> help(5, 0);
        int cnt = 0;
        int res = 0;

        for (auto &ch: croakOfFrogs) {
            int idx = mp[ch];

            if (idx == 0) {
                cnt++;
                help[idx]++;
            } else {
                if (help[idx - 1] > help[idx]) {
                    help[idx]++;
                } else {
                    return -1;
                }

                if (idx == 4) {
                    res = max(res, cnt);
                    cnt--;
                }
            }
        }

        if (help[0] == help[4]) {
            return res;
        }

        return -1;
    };
};

class Solution1190 {
public:
    static string reverseParentheses(string &s) {
        stack<string> stk;
        string str;

        for (auto &ch: s) {
            if (ch == '(') {
                stk.push(str);
                str = "";
            } else if (ch == ')') {
                reverse(str.begin(), str.end());
                str = stk.top().append(str);
                stk.pop();
            } else {
                str.push_back(ch);
            }
        }

        return str;
    }
};

class Solution1190_1 {
public:
    static string reverseParentheses(string &s) {
        unsigned int n = s.size();
        vector<int> pair(n);
        stack<int> stk;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                int j = stk.top();
                stk.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        string res;
        int idx = 0, dir = 1;
        while (idx < n) {
            if (s[idx] == '(' || s[idx] == ')') {
                idx = pair[idx];
                dir *= -1;
            } else {
                res.push_back(s[idx]);
            }

            idx += dir;
        }

        return res;
    }
};

class Solution223 {
public:
    static int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int s1 = abs((ax2 - ax1) * (ay2 - ay1));
        int s2 = abs((bx2 - bx1) * (by2 - by1));
        int overlapWidth = min(ax2, bx2) - max(ax1, bx1);
        int overlapHeight = min(ay2, by2) - max(ay1, by1);

        return s1 + s2 - max(0, overlapHeight) * max(0, overlapWidth);
    }
};

class Solution468 {
public:
    static string validIPAddress(string &queryIP) {
        string ipv4 = "IPv4";
        string ipv6 = "IPv6";
        string neither = "Neither";
        unsigned int n = queryIP.size();

        if (queryIP.find('.') != string::npos) {
            int idx = 0;
            int cnt = 0;

            while (idx < int(n)) {
                string temp;
                while (idx < n && queryIP[idx] != '.') {
                    if (!isdigit(queryIP[idx])) {
                        return neither;
                    }
                    temp.push_back(queryIP[idx++]);
                }

                if (temp.size() > 3 || temp.empty()) {
                    return neither;
                }
                int num = stoi(temp);
                if (num < 0 || num > 255) {
                    return neither;
                }
                if (num > 0 && temp[0] == '0' || num == 0 && temp.size() != 1) {
                    return neither;
                }
                if (queryIP[n - 1] == '.') {
                    return neither;
                }

                idx++, cnt++;
            }
            if (cnt != 4) {
                return neither;
            }

            return ipv4;
        }

        if (queryIP.find(':') != string::npos) {
            int idx = 0;
            int cnt = 0;
            int zeroCnt = 0;

            while (idx < int(n)) {
                string temp;
                while (idx < n && queryIP[idx] != ':') {
                    char ch = queryIP[idx];
                    if (!isdigit(queryIP[idx]) && !(ch <= 'F' && ch >= 'A') && !(ch <= 'f' && ch >= 'a')) {
                        return neither;
                    }
                    if (queryIP[idx] == '0') {
                        zeroCnt++;
                    }
                    temp.push_back(queryIP[idx++]);
                }

                if (temp.size() > 4 || temp.empty()) {
                    return neither;
                }
                if (zeroCnt == queryIP.size() && zeroCnt != 1) {
                    return neither;
                }
                if (queryIP[n - 1] == ':') {
                    return neither;
                }

                idx++, cnt++;
            }
            if (cnt != 8) {
                return neither;
            }

            return ipv6;
        }

        return neither;
    }
};

class Solution63 {
public:
    static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        unsigned int m = obstacleGrid.size();
        unsigned int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) {
                break;
            }
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) {
                break;
            }
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

class Solution63_1 {
public:
    static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        unsigned int m = obstacleGrid.size();
        unsigned int n = obstacleGrid[0].size();
        vector<int> dp(n, 0);

        dp[0] = obstacleGrid[0][0] == 1 ? 0 : 1;
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) {
                break;
            }
            dp[j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }
                if (j >= 1) {
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }

        return dp[n - 1];
    }
};

class Solution871 {
public:
    static int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
        int res = 0;
        priority_queue<int> pq;

        stations.push_back({target, 0});
        for (auto &station: stations) {
            while (startFuel < station[0] && !pq.empty()) {
                auto temp = pq.top();
                pq.pop();
                res++;
                startFuel += temp;
            }

            if (startFuel < station[0]) {
                return -1;
            }

            pq.emplace(station[1]);
        }

        return res;
    }
};

class Solution117 {
public:
    static Node *connect(Node *root) {
        if (root == nullptr) {
            return root;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            unsigned int n = q.size();
            for (int i = 0; i < n; ++i) {
                auto temp = q.front();
                q.pop();

                if (temp->left != nullptr) {
                    q.push(temp->left);
                }
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (i < n - 1) {
                    temp->next = q.front();
                }
            }
        }

        return root;
    }
};

class Solution2437 {
public:
    static int countTime(string time) {
        int hourCnt = 0, minCnt = 0;

        for (int i = 0; i < 24; ++i) {
            int a = i / 10;
            int b = i % 10;

            if ((time[0] == '?' || time[0] == a + '0') && (time[1] == '?' || time[1] == b + '0')) {
                hourCnt++;
            }
        }

        for (int j = 0; j < 60; ++j) {
            int a = j / 10;
            int b = j % 10;

            if ((time[3] == '?' || time[3] == a + '0') && (time[4] == '?' || time[4] == b + '0')) {
                minCnt++;
            }
        }

        return hourCnt * minCnt;
    }
};

class Solution1035 {
public:
    static int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
        unsigned int m = nums1.size();
        unsigned int n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }
};