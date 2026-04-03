#include <vector>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

struct Robot {
    int pos;
    int health;
    char dir;
    int idx;
};

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        vector<Robot> robots(n);
        for (int i = 0; i < n; i++)
            robots[i] = {positions[i], healths[i], directions[i], i};

        // Sort by position
        sort(robots.begin(), robots.end(), [](const Robot &a, const Robot &b) {
            return a.pos < b.pos;
        });

        stack<Robot> stk; // store 'R' robots
        vector<int> result(n, 0); // 0 means dead

        for (auto &r : robots) {
            if (r.dir == 'R') {
                stk.push(r);
            } else { // r.dir == 'L'
                while (!stk.empty() && r.health > 0) {
                    Robot top = stk.top();
                    stk.pop();
                    if (top.health == r.health) {
                        // both die
                        r.health = 0;
                    } else if (top.health > r.health) {
                        // 'R' survives, lose 1 health
                        top.health -= 1;
                        r.health = 0;
                        stk.push(top);
                    } else {
                        // 'L' survives, lose 1 health
                        r.health -= 1;
                        // continue with next 'R' in stack
                    }
                }
            }
        }

        // Remaining 'R' robots in stack survive
        while (!stk.empty()) {
            Robot r = stk.top();
            stk.pop();
            result[r.idx] = r.health;
        }

        // Remaining 'L' robots that survived
        for (auto &r : robots) {
            if (r.dir == 'L' && r.health > 0)
                result[r.idx] = r.health;
        }

        // Remove zeros
        vector<int> ans;
        for (int h : result)
            if (h > 0) ans.push_back(h);

        return ans;
    }
};