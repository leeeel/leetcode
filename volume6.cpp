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

        for (int i = 0; i < 4; i++) {   // Using auto for iteration will result in copying operations, which can slow down the program.
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
                    for (int k = 0; k < 4; k++) {   // Using auto for iteration will result in copying operations, which can slow down the program.
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

[[maybe_unused]] int main() {
    return 0;
}