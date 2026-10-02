class Solution {
public:
    vector<string> ans;

    void generate(string cur, int open, int close, int n) {
        if (cur.size() == 2 * n) {
            ans.push_back(cur);
            return;
        }

        if (open < n) {
            generate(cur + '(', open + 1, close, n);
        }

        if (close < open) {
            generate(cur + ')', open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        generate("", 0, 0, n);
        return ans;
    }
};