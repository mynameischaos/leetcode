#include <iostream>
#include <cmath>

using namespace std;



class Solution {
public:
    bool isPalindrome(int x) {
        // 所有小于0的数都不是回文!!!
        if (x < 0) {
            return false;
        }
        x = abs(x);
        int value = x;
        double num = 0;
        if (x < 10) {
            return true;
        }
        int i = 1;
        //注意等于10的情况
        while (x >= pow(10, i)) {
            i += 1;
        }
        i -= 1;
        for (int j = i; j >= 0; j--) {
            int tmp = x / pow(10, j);
            int tmp2 = pow(10, i - j) * tmp;
            num += tmp2;
            x -= tmp * pow(10, j);
        }
        if (num > INT_MAX) {
            return false;
        }
        if (int(num) == value) {
            return true;
        } else{
            return false;
        }
    }
};


int main() {
    Solution* solution = new Solution();
    int i = 10;
    cout << solution->isPalindrome(i) << endl;
    return 0;
}