#include <iostream>
#include <vector>

using namespace std;



class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        unsigned long min_len = LONG_MAX;
        int num = int(strs.size());
        int min_len_index = -1;
        for (int i = 0; i < strs.size(); i++) {
            if (strs[i].length() < min_len) {
                min_len = strs[i].length();
                min_len_index = i;
            }
        }

        int index = -1;
        if (min_len_index != -1) {
            int i;
            for (i = 0; i < strs[min_len_index].length(); i++) {
                int flag = 0;
                for (int j = 0; j < strs.size(); j++) {
                    index = i;
                    if (strs[min_len_index][i] != strs[j][i]) {
                        index  = i - 1;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    break;
                }
            }

        }

        if (index == -1) {
            return "";
        } else{
            return strs[min_len_index].substr(0, index + 1);
        }

    }
};



int main() {
    vector<string> st;
    st.push_back("a");
    st.push_back("a");
    st.push_back("b");
    st.push_back("bbcbb");
    Solution* solution = new Solution();
    cout << solution->longestCommonPrefix(st) << endl;

    return 0;
}