#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    string convert(string s, int numRows) {
        int len = int(s.length());
        int rows = min(len, numRows);
        // 用vector实现string数组,当数组数是变量的时候
        vector<string> vec;
        for (int i = 0; i < rows; i++) {
            string str = "";
            vec.push_back(str);
        }


        int index = 0;
        int flag = 0;
        while (index < len) {
            for (int j = 0; j < rows; j++) {
                if (index < len) {
                    string tmp = "";
                     vec[j] += s[index];
                    index++;
                } else {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1) {
                break;
            }

            for (int p = 0; p < rows - 2; p++) {
                if (index < len) {
                    vec[rows - 1 - p - 1] += s[index];
                    index++;
                } else {
                    break;
                }

            }
        }

        string res = "";
        for (int n = 0; n < rows; n++) {
            res += vec[n];
        }
        return res;
    }
};

int main() {
    Solution* solution = new Solution();
    int a = 1;
    string str = "PAYPALISHIRING";
    cout << solution->convert(str, a) << endl;
    return 0;
}