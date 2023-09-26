#include "bits/stdc++.h"
#include "structs.h"

using namespace std;

class [[maybe_unused]] Solution827 {
private:
    const vector<vector<int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    static bool isValid(int x, int y, unsigned int n) {
        if (x < 0 || y < 0 || x >= n || y >= n) {
            return false;
        }

        return true;
    }

    int dfs(vector<vector<int>> &grid, int x, int y, int tag) {
        if (grid[x][y] != 1) {
            return 0;
        }

        unsigned int n = grid.size();
        int res = 1;

        grid[x][y] = tag;

        for (int i = 0; i < 4; i++) {// Using auto for iteration will result in copying operations, which can slow down the program.
            int newX = x + dirs[i][0];
            int newY = y + dirs[i][1];

            if (!isValid(newX, newY, n)) {
                continue;
            }

            res += dfs(grid, newX, newY, tag);
        }

        return res;
    }

public:
    [[maybe_unused]] int largestIsland(vector<vector<int>> &grid) {
        unsigned int n = grid.size();
        int tag = 2;
        int res = 0;
        bool noZero = true;
        unordered_map<int, int> islandAreaMap;


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    noZero = false;
                }

                if (grid[i][j] == 1) {
                    int islandArea = dfs(grid, i, j, tag);
                    islandAreaMap[tag++] = islandArea;
                    res = max(res, islandArea);
                }
            }
        }

        if (noZero) {
            return int(n * n);
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int totalIslandArea = 1;
                unordered_set<int> countedIslandSet;

                if (grid[i][j] == 0) {
                    for (int k = 0; k < 4; k++) {// Using auto for iteration will result in copying operations, which can slow down the program.
                        int newX = i + dirs[k][0];
                        int newY = j + dirs[k][1];

                        if (!isValid(newX, newY, n)) {
                            continue;
                        }

                        int currTag = grid[newX][newY];
                        if (currTag == 0 || countedIslandSet.count(currTag)) {
                            continue;
                        }

                        totalIslandArea += islandAreaMap[currTag];
                        countedIslandSet.insert(currTag);
                    }
                }

                res = max(res, totalIslandArea);
            }
        }

        return res;
    }
};

class [[maybe_unused]] DiningPhilosophers {
private:
    mutex lock[5];

public:
    DiningPhilosophers() = default;

    [[maybe_unused]] void wantsToEat(int philosopher,
                                     const function<void()> &pickLeftFork,
                                     const function<void()> &pickRightFork,
                                     const function<void()> &eat,
                                     const function<void()> &putLeftFork,
                                     const function<void()> &putRightFork) {
        int leftChopstick = philosopher;
        int rightChopstick = (philosopher + 1) % 5;

        if (philosopher % 2 == 0) {
            lock[leftChopstick].lock();
            lock[rightChopstick].lock();
            pickLeftFork();
            pickRightFork();
        } else {
            lock[rightChopstick].lock();
            lock[leftChopstick].lock();
            pickLeftFork();
            pickRightFork();
        }

        eat();
        putLeftFork();
        putRightFork();
        lock[leftChopstick].unlock();
        lock[rightChopstick].unlock();
    }
};

class [[maybe_unused]] Solution68 {
private:
    static string genBlankStr(int n) {
        string res;

        return res.assign(n, ' ');
    }

    static string joinStr(vector<string> &words, int left, int right, const string &sepStr) {
        string res = words[left];

        for (int i = left + 1; i < right; ++i) {
            res.append(sepStr);
            res.append(words[i]);
        }

        return res;
    }

public:
    [[maybe_unused]] static vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> res;
        int right = 0, n = int(words.size());
        int left;

        while (true) {
            left = right;
            int curLineWordsWidth = 0;

            while (right < n && curLineWordsWidth + words[right].length() + right - left <= maxWidth) {
                curLineWordsWidth += int(words[right++].length());
            }

            if (right == n) {
                string s = joinStr(words, left, right, " ");
                res.emplace_back(s.append(genBlankStr(maxWidth - int(s.length()))));

                return res;
            }

            int curLineWordsNum = right - left;
            int curLineBlanksNum = maxWidth - curLineWordsWidth;

            if (curLineWordsNum == 1) {
                string s = words[left];
                res.emplace_back(s.append(genBlankStr(maxWidth - int(s.length()))));

                continue;
            }

            int curLineAvgBlanksNum = curLineBlanksNum / (curLineWordsNum - 1);
            int curLineExactBlanksNum = curLineBlanksNum % (curLineWordsNum - 1);

            string s1 = joinStr(words, left, left + curLineExactBlanksNum + 1, genBlankStr(curLineAvgBlanksNum + 1));
            string s2 = joinStr(words, left + curLineExactBlanksNum + 1, right, genBlankStr(curLineAvgBlanksNum));
            s1.append(genBlankStr(curLineAvgBlanksNum));
            s1.append(s2);

            res.emplace_back(s1);
        }
    }
};

class [[maybe_unused]] Solution875 {
public:
    [[maybe_unused]] static bool stoneGame([[maybe_unused]] vector<int> &piles) {
        return true;
    }
};

class [[maybe_unused]] Solution785 {
private:
    static constexpr int RED = 1;
    static constexpr int BLUE = 2;
    static constexpr int UNCOLORED = 0;

    bool dfs(vector<vector<int>> &graph, vector<int> &color, int node, int curNodeColor) {
        unsigned int n = graph[node].size();
        int nextNodeColor = curNodeColor == RED ? BLUE : RED;
        color[node] = curNodeColor;

        for (int i = 0; i < n; ++i) {
            if (color[graph[node][i]] == UNCOLORED && !dfs(graph, color, graph[node][i], nextNodeColor) || color[graph[node][i]] == curNodeColor) {
                return false;
            }
        }

        return true;
    }

public:
    [[maybe_unused]] bool isBipartite(vector<vector<int>> &graph) {
        unsigned int n = graph.size();
        vector<int> color(n, UNCOLORED);

        for (int i = 0; i < n; ++i) {
            if (color[i] == UNCOLORED && !dfs(graph, color, i, RED)) {
                return false;
            }
        }

        return true;
    }
};

[[maybe_unused]] int main() {
    return 0;
}