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

    void dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y, int &mark, int &islandArea, unsigned int &n) {
        if (visited[x][y] || grid[x][y] == 0) {
            return;
        }

        visited[x][y] = true;
        grid[x][y] = mark;
        islandArea++;

        for (auto dir: dirs) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (!isValid(newX, newY, n)) {
                continue;
            }

            dfs(grid, visited, newX, newY, mark, islandArea, n);
        }
    }

public:
    [[maybe_unused]] int largestIsland(vector<vector<int>> &grid) {
        unsigned int n = grid.size();
        int mark = 2;
        int res = 0;
        bool noZero = true;
        vector<vector<bool>> visited = vector<vector<bool>>(n, vector<bool>(n, false));
        unordered_map<int, int> islandAreaMap;


        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    noZero = false;
                }

                if (!visited[i][j] && grid[i][j] == 1) {
                    int islandArea = 0;
                    dfs(grid, visited, i, j, mark, islandArea, n);
                    islandAreaMap[mark++] = islandArea;
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
                    for (auto dir: dirs) {
                        int newX = i + dir[0];
                        int newY = j + dir[1];
                        int currMark = grid[newX][newY];

                        if (!isValid(newX, newY, n) || countedIslandSet.count(currMark)) {
                            continue;
                        }

                        totalIslandArea += islandAreaMap[currMark];
                        countedIslandSet.insert(currMark);
                    }
                }

                res = max(res, totalIslandArea);
            }
        }

        return res;
    }
};

[[maybe_unused]] int main() {
    return 0;
}