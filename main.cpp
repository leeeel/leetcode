#include "bits/stdc++.h"

using namespace std;

class [[maybe_unused]] Solution1487 {
public:
    static string addSuffix(string str, int num) {
        return str.append("(" + to_string(num) + ")");
    }

    [[maybe_unused]] static vector <string> getFolderNames(vector <string> &names) {
        vector <string> res;
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

class [[maybe_unused]] Solution {
public:
    [[maybe_unused]] static int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
        unsigned int n = heights.size();
        for (int i = 1; i < n - 1; ++i) {
            if (heights[i] > heights[i + 1]) {
                continue;
            } else {
                int gap = heights[i + 1] - heights[i];
                if (gap <= bricks) {
                    bricks -= gap;
                    continue;
                } else if (ladders > 0) {
                    ladders--;
                    continue;
                } else {
                    return i;
                }
            }
        }

       gi return int(n);
    }
};

int main() {
    vector<int> test = {14,3,9,13};
    cout << Solution::furthestBuilding(test, 5, 1);
    return 0;
}