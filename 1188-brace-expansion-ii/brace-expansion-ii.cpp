class Solution {
public:
    set<string> unite(const set<string>& a, const set<string>& b) {
        set<string> res = a;
        res.insert(b.begin(), b.end());
        return res;
    }

    set<string> concat(const set<string>& a, const set<string>& b) {
        set<string> res;
        for (const string& x : a) {
            for (const string& y : b) {
                res.insert(x + y);
            }
        }
        return res;
    }

    int pos;

    set<string> parse(string& s) {
        set<string> res;
        set<string> cur = {""};

        while (pos < s.size() && s[pos] != '}') {
            if (s[pos] == '{') {
                pos++; // skip '{'
                set<string> inside = parse(s);
                pos++; // skip '}'

                cur = concat(cur, inside);
            }
            else if (s[pos] == ',') {
                pos++;

                res = unite(res, cur);
                cur = {""};
            }
            else {
                // lowercase letter
                set<string> letter = {string(1, s[pos])};
                cur = concat(cur, letter);
                pos++;
            }
        }

        res = unite(res, cur);
        return res;
    }

    vector<string> braceExpansionII(string expression) {
        pos = 0;

        set<string> ans = parse(expression);

        return vector<string>(ans.begin(), ans.end());
    }
};