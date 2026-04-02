class Solution {
public:
    vector<int> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        vector<int> ans;
        
        for (int i = 0; i <= n - k; i++) {
            
            unordered_map<int, int> freq;
            
            // count frequency
            for (int j = i; j < i + k; j++) {
                freq[nums[j]]++;
            }
            
            // convert to vector
            vector<pair<int,int>> v; // {freq, value}
            for (auto &p : freq) {
                v.push_back({p.second, p.first});
            }
            
            // sort
            sort(v.begin(), v.end(), [](auto &a, auto &b) {
                if (a.first != b.first) return a.first > b.first; // freq desc
                return a.second > b.second; // value desc
            });
            
            // take top x
            int sum = 0;
            for (int t = 0; t < x && t < v.size(); t++) {
                sum += v[t].first * v[t].second;
            }
            
            ans.push_back(sum);
        }
        
        return ans;
    }
};