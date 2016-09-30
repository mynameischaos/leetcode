#include <iostream>
#include <sstream>

using namespace std;


class Solution {
public:
    int myAtoi(string str) {
        stringstream ss;
        ss << str;
        // 字符串为空的时候输出0
        long res = 0;
        ss >> res;
        // 题目说的不是很清楚,并没有说越界的时候取最大值或者最小值
        if (res > INT_MAX) {
            res = INT_MAX;
        }
        if (res < INT_MIN) {
            res = INT_MIN;
        }

        return int(res);
    }
};


int main() {
    string str = "";
    Solution* solution = new Solution();
    cout << solution->myAtoi(str) << endl;

    return 0;
}