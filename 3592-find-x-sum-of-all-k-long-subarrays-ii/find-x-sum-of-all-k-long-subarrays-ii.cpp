class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        unordered_map<int,int> freq;

        auto cmp = [](pair<int,int>& a, pair<int,int>& b){
            if(a.first != b.first) return a.first < b.first; // freq small first
            return a.second < b.second; // value small first
        };

        set<pair<int,int>> top, rest;
        long long sum = 0;

        auto add = [&](int val){
            int f = freq[val];
            pair<int,int> old = {f, val};
            pair<int,int> now = {f+1, val};

            if(f > 0){
                if(top.count(old)){
                    top.erase(old);
                    sum -= 1LL * f * val;
                } else {
                    rest.erase(old);
                }
            }

            freq[val]++;

            rest.insert(now);
        };

        auto remove = [&](int val){
            int f = freq[val];
            pair<int,int> old = {f, val};
            pair<int,int> now = {f-1, val};

            if(top.count(old)){
                top.erase(old);
                sum -= 1LL * f * val;
            } else {
                rest.erase(old);
            }

            freq[val]--;
            if(freq[val] > 0){
                rest.insert(now);
            }
        };

        auto rebalance = [&](){
            while(top.size() < x && !rest.empty()){
                auto it = prev(rest.end());
                auto p = *it;
                rest.erase(it);
                top.insert(p);
                sum += 1LL * p.first * p.second;
            }

            while(top.size() > x){
                auto it = top.begin();
                auto p = *it;
                top.erase(it);
                sum -= 1LL * p.first * p.second;
                rest.insert(p);
            }

            if(!top.empty() && !rest.empty()){
                auto t = *top.begin();
                auto r = *prev(rest.end());

                if(r.first > t.first || (r.first == t.first && r.second > t.second)){
                    top.erase(top.begin());
                    rest.erase(prev(rest.end()));

                    sum -= 1LL * t.first * t.second;
                    sum += 1LL * r.first * r.second;

                    top.insert(r);
                    rest.insert(t);
                }
            }
        };

        vector<long long> ans;

        for(int i=0;i<nums.size();i++){
            add(nums[i]);
            if(i >= k) remove(nums[i-k]);

            rebalance();

            if(i >= k-1){
                ans.push_back(sum);
            }
        }

        return ans;
    }
};