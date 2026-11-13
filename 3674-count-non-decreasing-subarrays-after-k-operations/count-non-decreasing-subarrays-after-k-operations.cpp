class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        deque<pair<long long, long long>> dq;
        long long cost = 0, ans = 0;
        int r = n - 1;
        for (int l = n - 1; l >= 0; --l) {
            long long x = nums[l];
            long long cnt = 1;
            while (!dq.empty() && dq.front().first <= x) {
                auto [v, c] = dq.front();
                dq.pop_front();
                cost += (x - v) * c;
                cnt += c;
            }
            dq.push_front({x, cnt});

            while (cost > k) {
                dq.back().second--;
                cost -= dq.back().first - nums[r];
                if (dq.back().second == 0) dq.pop_back();
                --r;
            }

            ans += r - l + 1;
        }
        return ans;
    }
};