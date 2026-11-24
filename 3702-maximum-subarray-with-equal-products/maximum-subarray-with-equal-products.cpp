class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long l = 1;
            int g = 0;

            for (int j = i; j < n; j++) {
                int x = nums[j];

                prod *= x;
                g = gcd(g, x);
                l = lcm(l, (long long)x);

                if (prod == g * l) {
                    ans = max(ans, j - i + 1);
                }
                
                if (prod > 100LL * 100) {
                    break;
                }
            }
        }

        return ans;
    }
};