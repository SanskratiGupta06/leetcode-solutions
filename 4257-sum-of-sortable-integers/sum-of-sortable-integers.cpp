class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;
            int prevMax = 0;

            for (int i = 0; i < n; i += k) {
                int mn = nums[i], mx = nums[i];
                int drops = 0;

                for (int j = i; j < i + k; j++) {
                    mn = min(mn, nums[j]);
                    mx = max(mx, nums[j]);

                    int next = (j + 1 == i + k) ? i : j + 1;
                    if (nums[j] > nums[next]) {
                        drops++;
                    }
                }

                if (drops > 1 || (i > 0 && prevMax > mn)) {
                    ok = false;
                    break;
                }

                prevMax = mx;
            }

            if (ok) ans += k;
        }

        return ans;
    }
};