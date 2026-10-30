class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int,int>>> adj(n);
        for (auto &e : edges) adj[e[0]].push_back({e[1], e[2]});

        const int INF = INT_MAX;
        vector<int> dist((size_t)n * (k + 1), INF);

        using T = tuple<int,int,int>;
        priority_queue<T, vector<T>, greater<T>> pq;

        dist[1] = 0;
        pq.push({0, 0, 1});

        while (!pq.empty()) {
            auto [d, u, r] = pq.top();
            pq.pop();
            if (d > dist[u * (k + 1) + r]) continue;
            if (u == n - 1) return d;

            for (auto &[v, w] : adj[u]) {
                int nr = (labels[v] == labels[u]) ? r + 1 : 1;
                if (nr > k) continue;
                int nd = d + w;
                int &cur = dist[v * (k + 1) + nr];
                if (nd < cur) {
                    cur = nd;
                    pq.push({nd, v, nr});
                }
            }
        }
        return -1;
    }
};