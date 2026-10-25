class Solution {
public:
    int m, n;
    void dfs(vector<vector<int>>& g, int i, int j) {
        if (i < 0 || j < 0 || i >= m || j >= n || g[i][j] == 1) return;
        g[i][j] = 1;
        dfs(g, i + 1, j); dfs(g, i - 1, j);
        dfs(g, i, j + 1); dfs(g, i, j - 1);
    }
    int closedIsland(vector<vector<int>>& grid) {
        m = grid.size(); n = grid[0].size();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if ((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 0)
                    dfs(grid, i, j);
        int count = 0;
        for (int i = 1; i < m - 1; i++)
            for (int j = 1; j < n - 1; j++)
                if (grid[i][j] == 0) {
                    dfs(grid, i, j);
                    count++;
                }
        return count;
    }
};