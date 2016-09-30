#include <iostream>
#include <sstream>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        long res;

        stringstream ss;
        ss << x;
        string str = ss.str();
        string tmp = "";
        if (x < 0) {
            tmp += "-";
        }
        for (int i = str.length() - 1; i >= 0; i--) {
            tmp += str[i];
        }

        stringstream ss2;
        ss2 << tmp;
        ss2 >> res;
        // 注意超过整数表示范围的时候输出0
        if (res > INT_MAX || res < INT_MIN) {
            res = 0;
        }

        return int(res);
    }
};


int main() {
    Solution* solution = new Solution();
    int input = -1534236469;
    cout << solution->reverse(input) << endl;
    return 0;
}