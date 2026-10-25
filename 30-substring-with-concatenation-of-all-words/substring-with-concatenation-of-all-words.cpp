class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int n = s.size(), k = words.size(), w = words[0].size();
        if (n < k * w) return res;

        unordered_map<string, int> need;
        for (auto& x : words) need[x]++;

        for (int off = 0; off < w; off++) {
            int left = off, cnt = 0;
            unordered_map<string, int> seen;

            for (int right = off; right + w <= n; right += w) {
                string cur = s.substr(right, w);

                if (need.count(cur)) {
                    seen[cur]++;
                    cnt++;

                    while (seen[cur] > need[cur]) {
                        seen[s.substr(left, w)]--;
                        left += w;
                        cnt--;
                    }

                    if (cnt == k) {
                        res.push_back(left);
                        seen[s.substr(left, w)]--;
                        left += w;
                        cnt--;
                    }
                } else {
                    seen.clear();
                    cnt = 0;
                    left = right + w;
                }
            }
        }
        return res;
    }
};