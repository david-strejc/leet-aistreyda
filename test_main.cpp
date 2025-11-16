#include <bits/stdc++.h>
using namespace std;
#include "word_ladder_ii.cpp"

int main() {
    Solution s;
    vector<string> wordList1 = {"hit","hot","dot","dog","lot","log","cog"}; // beginWord included
    auto r1 = s.findLadders("hit", "cog", wordList1);
    cerr << "case1 paths: " << r1.size() << '\n';

    vector<string> wordList2 = {"hot","dot","dog","lot","log","cog"};
    auto r2 = s.findLadders("hit", "cog", wordList2);
    cerr << "case2 paths: " << r2.size() << '\n';
}
