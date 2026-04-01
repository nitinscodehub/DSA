#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (s.empty() || words.empty()) return result;

        int wordLen = words[0].size();
        int wordCount = words.size();
        int totalLen = wordLen * wordCount;

        unordered_map<string, int> wordMap;
        for (auto &w : words) wordMap[w]++;

        // Try all possible starting offsets
        for (int i = 0; i < wordLen; i++) {
            unordered_map<string, int> windowMap;
            int left = i, count = 0;

            for (int j = i; j + wordLen <= s.size(); j += wordLen) {
                string word = s.substr(j, wordLen);

                if (wordMap.count(word)) {
                    windowMap[word]++;
                    count++;

                    // If freq exceeds → shrink window
                    while (windowMap[word] > wordMap[word]) {
                        string leftWord = s.substr(left, wordLen);
                        windowMap[leftWord]--;
                        left += wordLen;
                        count--;
                    }

                    // Valid window
                    if (count == wordCount) {
                        result.push_back(left);
                    }
                } else {
                    // Reset window
                    windowMap.clear();
                    count = 0;
                    left = j + wordLen;
                }
            }
        }

        return result;
    }
};