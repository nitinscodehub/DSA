#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for (char c : t) need[c]++;

        unordered_map<char, int> window;
        int have = 0; // number of chars fully matched
        int left = 0, min_len = INT_MAX, start = 0;

        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) have++;
            }

            // shrink window
            while (have == need.size()) {
                if (right - left + 1 < min_len) {
                    min_len = right - left + 1;
                    start = left;
                }

                char left_char = s[left];
                if (need.count(left_char)) {
                    window[left_char]--;
                    if (window[left_char] < need[left_char]) have--;
                }
                left++;
            }
        }

        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};