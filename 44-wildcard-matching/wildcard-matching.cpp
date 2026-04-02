class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0;
        int star = -1, match = 0;
        
        while (i < s.size()) {
            
            // match or '?'
            if (j < p.size() && (p[j] == s[i] || p[j] == '?')) {
                i++;
                j++;
            }
            
            // '*'
            else if (j < p.size() && p[j] == '*') {
                star = j;
                match = i;
                j++;
            }
            
            // mismatch but we saw '*'
            else if (star != -1) {
                j = star + 1;
                match++;
                i = match;
            }
            
            else {
                return false;
            }
        }
        
        // remaining chars in pattern should all be '*'
        while (j < p.size() && p[j] == '*') j++;
        
        return j == p.size();
    }
};