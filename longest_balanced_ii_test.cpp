#include <bits/stdc++.h>
using namespace std;

int longestBalanced_fast(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    const int MAXV = 100000; // per constraints
    const int INF = 1e9;

    vector<int> first(MAXV + 1, n + 1), last(MAXV + 1, 0);
    for (int i = 0; i < n; ++i) {
        int v = nums[i];
        if (first[v] == n + 1) first[v] = i + 1; // 1-based
        last[v] = i + 1;
    }

    int C = 0;
    vector<int> evL(n + 2, 0), evR(n + 2, 0);

    for (int v = 1; v <= MAXV; ++v) {
        if (last[v] == 0) continue;
        int p = (v % 2 == 0) ? 1 : -1;
        C += p;
        int l = first[v], r = last[v];
        if (r + 1 <= n + 1) evL[r + 1] += p;   // contributes to U from L = r+1 onward
        if (l - 1 >= 1) evR[l - 1] += p;       // contributes to W for R <= l-1 (processed backwards)
    }

    vector<int> U(n + 1), W(n + 1);
    int curr = 0;
    for (int L = 1; L <= n; ++L) {
        curr += evL[L];
        U[L] = curr;
    }

    curr = 0;
    for (int R = n; R >= 1; --R) {
        curr += evR[R];
        W[R] = curr;
    }

    const int SHIFT = n;
    int size = 2 * n + 5;
    vector<int> Lmin(size, INF), Rmax(size, -INF);

    for (int L = 1; L <= n; ++L) {
        int idx = U[L] + SHIFT;
        Lmin[idx] = min(Lmin[idx], L);
    }
    for (int R = 1; R <= n; ++R) {
        int idx = W[R] + SHIFT;
        Rmax[idx] = max(Rmax[idx], R);
    }

    int ans = 0;
    for (int idxX = 0; idxX < size; ++idxX) {
        if (Lmin[idxX] == INF) continue;
        int x = idxX - SHIFT;
        int y = C - x;
        int idxY = y + SHIFT;
        if (idxY < 0 || idxY >= size) continue;
        if (Rmax[idxY] == -INF) continue;
        int L = Lmin[idxX];
        int R = Rmax[idxY];
        if (R >= L) ans = max(ans, R - L + 1);
    }

    return ans;
}

int longestBalanced_bruteforce(vector<int>& nums) {
    int n = nums.size();
    int best = 0;
    for (int L = 0; L < n; ++L) {
        unordered_set<int> ev, od;
        for (int R = L; R < n; ++R) {
            if (nums[R] % 2 == 0) ev.insert(nums[R]);
            else od.insert(nums[R]);
            if (ev.size() == od.size()) best = max(best, R - L + 1);
        }
    }
    return best;
}

int main() {
    // Fixed samples
    {
        vector<int> a = {2,5,4,3};
        cout << "sample1: " << longestBalanced_fast(a) << "\n";
    }
    {
        vector<int> a = {3,2,2,5,4};
        cout << "sample2: " << longestBalanced_fast(a) << "\n";
    }
    {
        vector<int> a = {1,2,3,2};
        cout << "sample3: " << longestBalanced_fast(a) << "\n";
    }

    std::mt19937 rng(123456);
    for (int n = 1; n <= 50; ++n) {
        for (int iter = 0; iter < 200; ++iter) {
            int maxV = 10;
            vector<int> v(n);
            for (int i = 0; i < n; ++i) v[i] = rng() % maxV + 1;
            int b = longestBalanced_bruteforce(v);
            int f = longestBalanced_fast(v);
            if (b != f) {
                cerr << "Mismatch! n=" << n << " iter=" << iter << "\n";
                cerr << "Array: ";
                for (int x : v) cerr << x << ' ';
                cerr << "\nBrute=" << b << " fast=" << f << "\n";
                return 0;
            }
        }
    }
    cerr << "All random tests passed" << "\n";
    return 0;
}
