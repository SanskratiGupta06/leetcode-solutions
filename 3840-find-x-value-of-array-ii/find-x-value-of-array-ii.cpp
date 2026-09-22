class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node(int k = 1) {
            prod = 1 % k;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;
    vector<Node> seg;

    Node mergeNode(const Node& a, const Node& b) {
        Node res(k);

        res.prod = (a.prod * b.prod) % k;

        for (int r = 0; r < k; r++) {
            res.cnt[r] += a.cnt[r];
        }

        for (int r = 0; r < k; r++) {
            int rem = (a.prod * r) % k;
            res.cnt[rem] += b.cnt[r];
        }

        return res;
    }

    void update(int pos, int val) {
        int p = pos + seg.size() / 2;

        seg[p] = Node(k);

        int rem = val % k;
        seg[p].prod = rem;
        seg[p].cnt[rem] = 1;

        p >>= 1;

        while (p) {
            seg[p] = mergeNode(seg[p << 1], seg[p << 1 | 1]);
            p >>= 1;
        }
    }

    Node query(int l, int r, int n) {
        int size = n;

        Node left(k), right(k);

        l += size;
        r += size;

        while (l <= r) {
            if (l & 1) {
                left = mergeNode(left, seg[l]);
                l++;
            }

            if (!(r & 1)) {
                right = mergeNode(seg[r], right);
                r--;
            }

            l >>= 1;
            r >>= 1;
        }

        return mergeNode(left, right);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {

        this->k = k;

        int n = nums.size();

        if (k == 1) {
            vector<int> ans;

            for (auto &q : queries) {
                int start = q[2];
                int x = q[3];

                ans.push_back(x == 0 ? n - start : 0);
            }

            return ans;
        }

        seg.assign(2 * n, Node(k));

        for (int i = 0; i < n; i++) {
            int rem = nums[i] % k;

            seg[n + i].prod = rem;
            seg[n + i].cnt[rem] = 1;
        }

        for (int i = n - 1; i >= 1; i--) {
            seg[i] = mergeNode(seg[i << 1], seg[i << 1 | 1]);
        }

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(index, value);

            Node res = query(start, n - 1, n);

            ans.push_back(res.cnt[x]);
        }

        return ans;
    }
};