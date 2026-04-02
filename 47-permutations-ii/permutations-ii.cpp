class Solution {
public:
    vector<vector<int>> ans;
    
    void backtrack(vector<int>& nums, vector<int>& temp, vector<bool>& used) {
        if (temp.size() == nums.size()) {
            ans.push_back(temp);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            
            // skip used elements
            if (used[i]) continue;
            
            // 🔥 skip duplicates
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            temp.push_back(nums[i]);
            used[i] = true;
            
            backtrack(nums, temp, used);
            
            // backtrack
            temp.pop_back();
            used[i] = false;
        }
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // 🔥 important
        
        vector<int> temp;
        vector<bool> used(nums.size(), false);
        
        backtrack(nums, temp, used);
        
        return ans;
    }
};