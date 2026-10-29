class Solution {
public:
    vector<int> tin, tout, depth;
    vector<vector<int>> up, adj;
    vector<int> bit;
    string s;
    int timer, LOG;

    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;

        for (int j = 1; j < LOG; j++) {
            up[j][u] = up[j - 1][up[j - 1][u]];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void updateBIT(int i, int val, int n) {
        for (; i <= n; i += i & -i) {
            bit[i] ^= val;
        }
    }

    int queryBIT(int i) {
        int res = 0;
        for (; i > 0; i -= i & -i) {
            res ^= bit[i];
        }
        return res;
    }

    int getLCA(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int j = 0; j < LOG; j++) {
            if (diff & (1 << j)) {
                u = up[j][u];
            }
        }

        if (u == v) return u;

        for (int j = LOG - 1; j >= 0; j--) {
            if (up[j][u] != up[j][v]) {
                u = up[j][u];
                v = up[j][v];
            }
        }

        return up[0][u];
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        this->s = s;
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        up.assign(LOG, vector<int>(n, 0));
        bit.assign(n + 2, 0);
        timer = 0;

        dfs(0, 0);

        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            updateBIT(tin[u], mask, n);
            updateBIT(tout[u] + 1, mask, n);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (this->s[u] - 'a');
                int newMask = 1 << (c - 'a');
                int change = oldMask ^ newMask;

                updateBIT(tin[u], change, n);
                updateBIT(tout[u] + 1, change, n);

                this->s[u] = c;
            } else {
                int v;
                ss >> v;

                int w = getLCA(u, v);
                int maskU = queryBIT(tin[u]);
                int maskV = queryBIT(tin[v]);

                int pathMask = maskU ^ maskV ^
                               (1 << (this->s[w] - 'a'));

                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};