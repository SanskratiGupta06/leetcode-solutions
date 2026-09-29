class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int L = m + n - 1;

        if (L % 2 != 0) return false;

        vector<vector<vector<bool>>> dp(
            m, vector<vector<bool>>(n, vector<bool>(L + 1, false))
        );

        dp[0][0][1] = (grid[0][0] == '(');

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                int change = (grid[i][j] == '(' ? 1 : -1);

                for (int bal = 0; bal <= L; bal++) {
                    int prevBal = bal - change;

                    if (prevBal < 0) continue;

                    if (i > 0 && dp[i - 1][j][prevBal])
                        dp[i][j][bal] = true;

                    if (j > 0 && dp[i][j - 1][prevBal])
                        dp[i][j][bal] = true;
                }
            }
        }

        return dp[m - 1][n - 1][0];
    }
};