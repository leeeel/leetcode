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

    int dfs(vector<vector<int>> &grid, vector<vector<bool>> &visited, int x, int y, int &tag) {
        if (visited[x][y] || grid[x][y] == 0) {
            return 0;
        }

        unsigned int n = grid.size();
        int res = 1;

        visited[x][y] = true, grid[x][y] = tag;

        for (auto dir: dirs) {
            int newX = x + dir[0];
            int newY = y + dir[1];

            if (!isValid(newX, newY, n)) {
                continue;
            }

            res += dfs(grid, visited, newX, newY, tag);
        }

        return res;
    }

public:
    [[maybe_unused]] int largestIsland(vector<vector<int>> &grid) {
        unsigned int n = grid.size();
        int tag = 2;
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
                    int islandArea = dfs(grid, visited, i, j, tag);
                    islandAreaMap[tag++] = islandArea;
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

                        if (!isValid(newX, newY, n)) {
                            continue;
                        }

                        int currTag = grid[newX][newY];
                        if (countedIslandSet.count(currTag)) {
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

[[maybe_unused]] int main() {
    return 0;
}