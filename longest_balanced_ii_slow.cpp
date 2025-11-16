#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        int maxVal = 0;
        for (int x : nums) maxVal = max(maxVal, x);

        vector<char> seen(maxVal + 1, 0);
        int de = 0, od = 0;
        for (int x : nums) {
            if (!seen[x]) {
                seen[x] = 1;
                if (x % 2 == 0) ++de; else ++od;
            }
        }
        int kMax = min(de, od);
        if (kMax == 0) return 0;

        int ans = 0;
        for (int k = 1; k <= kMax; ++k) {
            vector<int> c1(maxVal + 1), c2(maxVal + 1), c3(maxVal + 1);
            int L1 = 0, L2 = 0, L3 = 0;
            int e1 = 0, o1 = 0;
            int e2 = 0, o2 = 0;
            int e3 = 0, o3 = 0;

            for (int R = 0; R < n; ++R) {
                int v = nums[R];
                bool isEven = (v % 2 == 0);

                if (c1[v]++ == 0) {
                    if (isEven) ++e1; else ++o1;
                }
                while ((e1 > k || o1 > k) && L1 <= R) {
                    int x = nums[L1++];
                    if (--c1[x] == 0) {
                        if (x % 2 == 0) --e1; else --o1;
                    }
                }

                if (c2[v]++ == 0) {
                    if (isEven) ++e2; else ++o2;
                }
                while ((e2 > k - 1 || o2 > k) && L2 <= R) {
                    int x = nums[L2++];
                    if (--c2[x] == 0) {
                        if (x % 2 == 0) --e2; else --o2;
                    }
                }

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

int brute(vector<int> nums){
    int n = nums.size();
    int best=0;
    for(int L=0;L<n;++L){
        unordered_set<int> ev,od;
        for(int R=L;R<n;++R){
            int v=nums[R];
            if(v%2==0) ev.insert(v); else od.insert(v);
            if(ev.size()==od.size()) best=max(best,R-L+1);
        }
    }
    return best;
}

int main(){
    Solution sol;
    vector<int> a1={2,5,4,3};
    cout<<"sample1 fast="<<sol.longestBalanced(a1)<<" brute="<<brute(a1)<<"\n";
    vector<int> a2={3,2,2,5,4};
    cout<<"sample2 fast="<<sol.longestBalanced(a2)<<" brute="<<brute(a2)<<"\n";
    vector<int> a3={1,2,3,2};
    cout<<"sample3 fast="<<sol.longestBalanced(a3)<<" brute="<<brute(a3)<<"\n";

    mt19937 rng(123);
    for(int n=1;n<=12;++n){
        for(int it=0;it<200;++it){
            int maxV=6;
            vector<int> v(n);
            for(int i=0;i<n;++i) v[i]=rng()%maxV+1;
            int b=brute(v);
            int f=sol.longestBalanced(v);
            if(b!=f){
                cerr<<"Mismatch n="<<n<<" it="<<it<<"\n";
                cerr<<"Array: ";
                for(int x: v) cerr<<x<<' ';
                cerr<<"\n";
                cerr<<"brute="<<b<<" fast="<<f<<"\n";
                return 0;
            }
        }
    }
    cerr<<"Random tests passed (small n)"<<"\n";
}
