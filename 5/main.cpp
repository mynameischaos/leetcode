#include <iostream>

using namespace std;


class Solution {
public:
    string longestPalindrome(string s) {
        //采用动态规划求解
        //主要是自底向上求解,记录求解过程
        int len = s.length();
        int longest_begin_index = 0;
        int max_len = 1;
        //table[i][j]表示i到j是否为回文
        bool table[1000][1000] = {false};

        //求解长度为1的情况
        for (int i = 0; i < len; i++) {
            table[i][i] = true;
        }
        //求解长度为2的情况
        for (int i = 0; i < len - 1; i++) {
            if (s[i] == s[i + 1]) {
                table[i][i + 1] = true;
                max_len = 2;
                longest_begin_index = i;
            }
        }
        //求解长度大于等于3的情况,当然是建立在前面两个基础之上
        for (int tmp_len = 3; tmp_len <= len; tmp_len++) {
            for (int i = 0; i <= len - tmp_len; i++) {
                int j = i + tmp_len - 1;
                if (s[i] == s[j] && table[i + 1][j - 1] == true) {
                    table[i][j] = true;
                    max_len = tmp_len;
                    longest_begin_index = i;
                    //不能退出循环,必需把所有情况考虑完,长度增加的时候可能用到这个table[i][j]
                    //break;
                }
            }
        }

        return s.substr(longest_begin_index, max_len);

    }
};

int main() {

    Solution* solu = new Solution();
    string str = "123454321";
    cout << solu->longestPalindrome(str);

    return 0;
}