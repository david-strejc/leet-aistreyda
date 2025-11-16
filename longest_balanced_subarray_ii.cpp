#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int maxVal = 0;
        for (int x : nums) maxVal = max(maxVal, x);

        // Count distinct evens / odds overall.
        vector<char> seen(maxVal + 1, 0);
        int totalEven = 0, totalOdd = 0;
        for (int x : nums) {
            if (!seen[x]) {
                seen[x] = 1;
                if (x % 2 == 0) {
                    ++totalEven;
                } else {
                    ++totalOdd;
                }
            }
        }

        int kMax = min(totalEven, totalOdd);
        if (kMax == 0) return 0;

        int ans = 0;

        // For each possible k, use three sliding windows:
        // W1: at most (k, k)
        // W2: at most (k-1, k)
        // W3: at most (k, k-1)
        for (int k = 1; k <= kMax; ++k) {
            vector<int> c1(maxVal + 1), c2(maxVal + 1), c3(maxVal + 1);
            int L1 = 0, L2 = 0, L3 = 0;
            int e1 = 0, o1 = 0;
            int e2 = 0, o2 = 0;
            int e3 = 0, o3 = 0;

            for (int R = 0; R < n; ++R) {
                int v = nums[R];
                bool isEven = (v % 2 == 0);

                // Window 1: (k, k)
                if (c1[v]++ == 0) {
                    if (isEven) ++e1; else ++o1;
                }
                while ((e1 > k || o1 > k) && L1 <= R) {
                    int x = nums[L1++];
                    if (--c1[x] == 0) {
                        if (x % 2 == 0) --e1; else --o1;
                    }
                }

                // Window 2: (k-1, k)
                if (c2[v]++ == 0) {
                    if (isEven) ++e2; else ++o2;
                }
                while ((e2 > k - 1 || o2 > k) && L2 <= R) {
                    int x = nums[L2++];
                    if (--c2[x] == 0) {
                        if (x % 2 == 0) --e2; else --o2;
                    }
                }

                // Window 3: (k, k-1)
                if (c3[v]++ == 0) {
                    if (isEven) ++e3; else ++o3;
                }
                while ((e3 > k || o3 > k - 1) && L3 <= R) {
                    int x = nums[L3++];
                    if (--c3[x] == 0) {
                        if (x % 2 == 0) --e3; else --o3;
                    }
                }

                int LB = (L2 <= R ? L2 : R + 1);
                int LC = (L3 <= R ? L3 : R + 1);
                int L1b = (L1 <= R ? L1 : R + 1);

                int LmaxAllowed = min({LB - 1, LC - 1, R});
                if (L1b <= LmaxAllowed) {
                    ans = max(ans, R - L1b + 1);
                }
            }
        }

        return ans;
    }
};

// Simple local test harness.
int main() {
    Solution sol;

    vector<int> nums1{2, 5, 4, 3};
    vector<int> nums2{3, 2, 2, 5, 4};
    vector<int> nums3{1, 2, 3, 2};

    cout << sol.longestBalanced(nums1) << "\n"; // expected 4
    cout << sol.longestBalanced(nums2) << "\n"; // expected 5
    cout << sol.longestBalanced(nums3) << "\n"; // expected 3

    return 0;
}

