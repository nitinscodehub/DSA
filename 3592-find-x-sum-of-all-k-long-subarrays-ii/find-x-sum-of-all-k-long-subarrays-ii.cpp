class Solution {
public:
    using pii = pair<int,int>; // {freq, value}
    
    struct cmp {
        bool operator()(const pii &a, const pii &b) const {
            if (a.first != b.first) return a.first > b.first;
            return a.second > b.second;
        }
    };
    
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        int n = nums.size();
        
        unordered_map<int,int> freq;
        
        multiset<pii, cmp> top, rest;
        long long sum = 0;
        
        auto add = [&](int val) {
            int f = freq[val];
            
            pii old = {f, val};
            pii nw = {f+1, val};
            
            if (f > 0) {
                if (top.count(old)) {
                    top.erase(top.find(old));
                    sum -= 1LL * f * val;
                } else {
                    rest.erase(rest.find(old));
                }
            }
            
            freq[val]++;
            
            rest.insert(nw);
        };
        
        auto remove = [&](int val) {
            int f = freq[val];
            pii old = {f, val};
            pii nw = {f-1, val};
            
            if (top.count(old)) {
                top.erase(top.find(old));
                sum -= 1LL * f * val;
            } else {
                rest.erase(rest.find(old));
            }
            
            freq[val]--;
            
            if (freq[val] > 0) {
                rest.insert(nw);
            }
        };
        
        auto rebalance = [&]() {
            while (top.size() < x && !rest.empty()) {
                auto it = rest.begin();
                pii p = *it;
                rest.erase(it);
                top.insert(p);
                sum += 1LL * p.first * p.second;
            }
            
            while (!top.empty() && !rest.empty()) {
                auto worstTop = prev(top.end());
                auto bestRest = rest.begin();
                
                if (*bestRest < *worstTop) break;
                
                pii t = *worstTop;
                pii r = *bestRest;
                
                top.erase(worstTop);
                rest.erase(bestRest);
                
                sum -= 1LL * t.first * t.second;
                
                top.insert(r);
                rest.insert(t);
                
                sum += 1LL * r.first * r.second;
            }
        };
        
        vector<long long> ans;
        
        for (int i = 0; i < n; i++) {
            add(nums[i]);
            
            if (i >= k) {
                remove(nums[i - k]);
            }
            
            rebalance();
            
            if (i >= k - 1) {
                ans.push_back(sum);
            }
        }
        
        return ans;
    }
};