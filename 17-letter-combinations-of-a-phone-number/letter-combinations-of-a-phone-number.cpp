class Solution {
public:
    vector<string> ans;
    string path;

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};

        vector<string> mp = {
            "", "", "abc", "def", "ghi",
            "jkl", "mno", "pqrs", "tuv", "wxyz"
        };

        backtrack(digits, 0, mp);
        return ans;
    }

    void backtrack(string& digits, int index, vector<string>& mp) {
        if (index == digits.size()) {
            ans.push_back(path);
            return;
        }

        string letters = mp[digits[index] - '0'];

        for (char ch : letters) {
            path.push_back(ch);
            backtrack(digits, index + 1, mp);
            path.pop_back();
        }
    }
};