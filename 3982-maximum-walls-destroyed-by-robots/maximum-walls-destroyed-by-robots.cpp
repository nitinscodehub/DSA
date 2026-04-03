class Solution {
public:
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        int n = robots.size();

        vector<pair<int,int>> r;
        for(int i = 0; i < n; i++)
            r.push_back({robots[i], distance[i]});

        sort(r.begin(), r.end());
        sort(walls.begin(), walls.end());

        // helper: count walls in [l, r]
        auto countWalls = [&](int l, int r) {
            if(l > r) return 0;
            return (int)(upper_bound(walls.begin(), walls.end(), r) -
                         lower_bound(walls.begin(), walls.end(), l));
        };

        vector<int> L(n), R(n);
        vector<int> leftCnt(n), rightCnt(n);

        for(int i = 0; i < n; i++) {
            int pos = r[i].first, d = r[i].second;

            // LEFT range
            L[i] = pos - d;
            if(i > 0) L[i] = max(L[i], r[i-1].first + 1);

            leftCnt[i] = countWalls(L[i], pos);

            // RIGHT range
            R[i] = pos + d;
            if(i < n-1) R[i] = min(R[i], r[i+1].first - 1);

            rightCnt[i] = countWalls(pos, R[i]);
        }

        // overlap between (i-1 RIGHT) and (i LEFT)
        auto getOverlap = [&](int i) {
            if(i <= 0) return 0;
            int l = max(r[i-1].first, L[i]);
            int rr = min(R[i-1], r[i].first);
            return countWalls(l, rr);
        };

        vector<vector<int>> dp(n, vector<int>(2, 0));

        dp[0][0] = leftCnt[0];
        dp[0][1] = rightCnt[0];

        for(int i = 1; i < n; i++) {
            // RIGHT → always safe
            dp[i][1] = max(dp[i-1][0], dp[i-1][1]) + rightCnt[i];

            // LEFT
            // case 1: prev LEFT
            dp[i][0] = dp[i-1][0] + leftCnt[i];

            // case 2: prev RIGHT (subtract overlap)
            int overlap = getOverlap(i);
            dp[i][0] = max(dp[i][0],
                           dp[i-1][1] + leftCnt[i] - overlap);

            // case 3: skip previous
            int bestPrev2 = (i >= 2 ? max(dp[i-2][0], dp[i-2][1]) : 0);
            dp[i][0] = max(dp[i][0], bestPrev2 + leftCnt[i]);
        }

        return max(dp[n-1][0], dp[n-1][1]);
    }
};