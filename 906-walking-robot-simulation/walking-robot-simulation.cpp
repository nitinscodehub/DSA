class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_set<string> obs;
        
        // Store obstacles
        for (auto &o : obstacles) {
            obs.insert(to_string(o[0]) + "#" + to_string(o[1]));
        }

        // Directions: North, East, South, West
        vector<int> dx = {0, 1, 0, -1};
        vector<int> dy = {1, 0, -1, 0};

        int x = 0, y = 0;
        int dir = 0; // facing North
        int maxDist = 0;

        for (int cmd : commands) {
            if (cmd == -2) {
                dir = (dir + 3) % 4; // turn left
            } 
            else if (cmd == -1) {
                dir = (dir + 1) % 4; // turn right
            } 
            else {
                for (int i = 0; i < cmd; i++) {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];

                    // Check obstacle
                    if (obs.count(to_string(nx) + "#" + to_string(ny))) {
                        break;
                    }

                    x = nx;
                    y = ny;

                    maxDist = max(maxDist, x*x + y*y);
                }
            }
        }

        return maxDist;
    }
};