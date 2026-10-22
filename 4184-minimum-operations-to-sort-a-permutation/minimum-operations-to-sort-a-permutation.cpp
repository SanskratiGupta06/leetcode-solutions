class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        int k = nums[0];

        bool inc = true, dec = true;
        for (int i = 0; i < n; i++) {
            if (nums[i] != (i + k) % n) inc = false;
            if (nums[i] != ((k - i) % n + n) % n) dec = false;
            if (!inc && !dec) return -1;
        }

        int ans = INT_MAX;
        if (inc) {
            ans = min(ans, (n - k) % n);
            if (k != 0) ans = min(ans, k + 2);
        }
        if (dec) {
            int kp = (k + 1) % n;
            ans = min(ans, kp + 1);
            ans = min(ans, 1 + (n - kp) % n);
        }
        return ans;
    }
};