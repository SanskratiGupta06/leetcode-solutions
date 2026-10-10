class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = 1LL * k1 + k2;
        int n = nums1.size();
        vector<int> diff(n);

        long long total = 0;
        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            total += diff[i];
        }

        if (k >= total) return 0;

        sort(diff.begin(), diff.end(), greater<int>());
        diff.push_back(0);

        for (int i = 0; i < n; i++) {
            long long cost = 1LL * (diff[i] - diff[i + 1]) * (i + 1);

            if (cost <= k) {
                k -= cost;
            } else {
                long long level = diff[i] - k / (i + 1);
                long long rem = k % (i + 1);
                long long ans = 0;

                for (int j = 0; j <= i; j++) {
                    ans += level * level;
                    if (j < rem) ans -= 2 * level - 1;
                }

                for (int j = i + 1; j < n; j++) {
                    ans += 1LL * diff[j] * diff[j];
                }

                return ans;
            }
        }

        return 0;
    }
};