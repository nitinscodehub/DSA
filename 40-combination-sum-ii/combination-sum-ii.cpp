#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void backtrack(int index, vector<int>& candidates, int target,
                   vector<int>& current, vector<vector<int>>& result) {

        if (target == 0) {
            result.push_back(current);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {

            // ❌ skip duplicates
            if (i > index && candidates[i] == candidates[i - 1]) continue;

            // ❌ stop if exceeds
            if (candidates[i] > target) break;

            // ✅ pick element
            current.push_back(candidates[i]);
            backtrack(i + 1, candidates, target - candidates[i], current, result);
            current.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // 🔥 must
        vector<vector<int>> result;
        vector<int> current;

        backtrack(0, candidates, target, current, result);
        return result;
    }
};