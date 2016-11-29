#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0)
            return result;
        init();
        dfs(0, (int)digits.size(), digits, "");
        return result;
    }
private:
    vector<string> result;
    map<char, string> dict;
    void init() {
        dict['0'] = " ";
        dict['1'] = "";
        dict['2'] = "abc";
        dict['3'] = "def";
        dict['4'] = "ghi";
        dict['5'] = "jkl";
        dict['6'] = "mno";
        dict['7'] = "pqrs";
        dict['8'] = "tuv";
        dict['9'] = "wxyz";

    }
    void dfs(int dep, int max_dep, string digits, string tmp) {
        if (dep == max_dep) {
            result.push_back(tmp);
            return;
        }
        for (int i = 0; i < dict[digits[dep]].size(); i++) {
            dfs(dep + 1, max_dep, digits, tmp + dict[digits[dep]][i]);
        }
    }
};

int main() {
    string input = "23";
    Solution* solution = new Solution();
    vector<string> result = solution->letterCombinations(input);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
    return 0;
}