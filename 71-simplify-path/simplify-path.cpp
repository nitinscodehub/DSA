#include <string>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stk;           // Stack to store valid directories
        stringstream ss(path);        // Split the path by '/'
        string token;

        while (getline(ss, token, '/')) {
            if (token.empty() || token == ".") continue; // Ignore empty or '.'
            if (token == "..") {
                if (!stk.empty()) stk.pop_back();        // Go up one directory
            } else {
                stk.push_back(token);                    // Valid directory
            }
        }

        // Reconstruct the simplified path
        string result = "";
        for (const string &dir : stk) {
            result += "/" + dir;
        }

        return result.empty() ? "/" : result;            // Root case
    }
};