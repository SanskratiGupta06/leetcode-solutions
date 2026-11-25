class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<int> sa(n), rank(n), temp(n);

        for (int i = 0; i < n; i++) {
            sa[i] = i;
            rank[i] = nums[i];
        }

        for (int len = 1; len < n; len *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int ra = (a + len < n) ? rank[a + len] : -1;
                int rb = (b + len < n) ? rank[b + len] : -1;

                return ra < rb;
            });

            temp[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                bool different =
                    rank[a] != rank[b] ||
                    (a + len < n ? rank[a + len] : -1) !=
                    (b + len < n ? rank[b + len] : -1);

                temp[b] = temp[a] + different;
            }

            rank = temp;

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        vector<int> pos(n);

        for (int i = 0; i < n; i++) {
            pos[sa[i]] = i;
        }

        vector<int> lcp(n, 0);
        int k = 0;

        for (int i = 0; i < n; i++) {
            int r = pos[i];

            if (r == 0) {
                k = 0;
                continue;
            }

            int j = sa[r - 1];

            while (i + k < n && j + k < n &&
                   nums[i + k] == nums[j + k]) {
                k++;
            }

            lcp[r] = k;

            if (k > 0)
                k--;
        }

        int ans = n;

        for (int r = 0; r < n; r++) {
            int best = lcp[r];

            if (r + 1 < n) {
                best = max(best, lcp[r + 1]);
            }

            int remaining = n - sa[r];

            if (best < remaining) {
                ans = min(ans, best + 1);
            }
        }

        return ans;
    }
};