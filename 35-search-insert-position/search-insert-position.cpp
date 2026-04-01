#include <vector>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int ans = nums.size(); // default (insert at end)

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] >= target) {
                ans = mid;
                right = mid - 1;  // move left
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
};