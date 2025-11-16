#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> res;
        if (!dict.count(endWord)) return res;

        dict.insert(beginWord);

        unordered_map<string, int> distBegin, distEnd;
        bfs(beginWord, dict, distBegin);
        if (!distBegin.count(endWord)) return res;
        bfs(endWord, dict, distEnd);

        int shortest = distBegin[endWord];
        vector<string> path{beginWord};
        dfs(beginWord, endWord, distBegin, distEnd, shortest, path, res);
        return res;
    }

private:
    void bfs(const string& start,
             const unordered_set<string>& dict,
             unordered_map<string, int>& dist) {
        queue<string> q;
        q.push(start);
        dist[start] = 0;
        int L = start.size();

        while (!q.empty()) {
            string word = q.front();
            q.pop();
            int d = dist[word];
            string cur = word;
            for (int i = 0; i < L; ++i) {
                char old = cur[i];
                for (char c = 'a'; c <= 'z'; ++c) {
                    if (c == old) continue;
                    cur[i] = c;
                    if (dict.count(cur) && !dist.count(cur)) {
                        dist[cur] = d + 1;
                        q.push(cur);
                    }
                }
                cur[i] = old;
            }
        }
    }

    void dfs(const string& word,
             const string& endWord,
             const unordered_map<string, int>& distBegin,
             const unordered_map<string, int>& distEnd,
             int shortest,
             vector<string>& path,
             vector<vector<string>>& res) {
        if (word == endWord) {
            res.push_back(path);
            return;
        }

        auto itCur = distBegin.find(word);
        if (itCur == distBegin.end()) return;
        int d = itCur->second;
        if (d >= shortest) return;

        int L = word.size();
        string cur = word;
        for (int i = 0; i < L; ++i) {
            char old = cur[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == old) continue;
                cur[i] = c;
                auto itNextBegin = distBegin.find(cur);
                auto itNextEnd = distEnd.find(cur);
                if (itNextBegin != distBegin.end() &&
                    itNextEnd != distEnd.end() &&
                    itNextBegin->second == d + 1 &&
                    d + 1 + itNextEnd->second == shortest) {
                    path.push_back(cur);
                    dfs(cur, endWord, distBegin, distEnd, shortest, path, res);
                    path.pop_back();
                }
            }
            cur[i] = old;
        }
    }
};
