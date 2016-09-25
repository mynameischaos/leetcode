#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

//straightforward approach.
//O(n^3)
/*
class Solution {
private:
    vector<char> vec;
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 0) {
            return 0;
        }
        int res = 1;
        int endFlag = 0;
        for (int i = 0; i < s.length() - 1; i++) {
            int max_length = 1;
            vec.push_back(s[i]);
            for (int j = i + 1; j < s.length(); j++) {
                int temp = findChar(s[j]);
                if (temp == -1) {
                    vec.push_back(s[j]);
                    max_length++;
                    if (max_length > res) {
                        res = max_length;
                    }
                }else {
                    vec.clear();
                    i += temp;
                    if (max_length > res) {
                        res = max_length;
                    }
                    if (res >= s.length() - 1 - i) {
                        endFlag = 1;
                    }
                    break;
                }
            }
            if (endFlag == 1) {
                break;
            }
        }
        return res;
    }
    int findChar(char c) {
        for (size_t i = 0; i < vec.size(); i++) {
            if (vec[i] == c)
                return int(i);
        }
        return -1;
    }
};
*/

// slide window
// O(2n)

class Solution {

public:
    int lengthOfLongestSubstring(string s) {
        set<char>* tempSet = new set<char>;
        int max_res = 0;
        int i = 0, j = 0;
        int n = int(s.length());
        while(i < n && j < n) {
            if(tempSet->find(s[j]) == tempSet->end()) {
                tempSet->insert(s[j++]);
            }else {
                tempSet->erase(s[i++]);
            }
            max_res = max(max_res, j - i);
        }
        return max_res;
    }

};

//bug
/* 结合了以上两个程序的思想:1)跳过已经包含的 2)使用slide window
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        map<char , int>* tempMap = new map<char, int>;
        int n = int(s.length());
        int max_len = 0;

        for (int j = 0, i = 0; j < n; j++) {
            if (tempMap->find(s[j]) != tempMap->end()) {
                i = max(tempMap->find(s[j])->second, i);
            }
            max_len = max(max_len, j - i + 1);
            tempMap->insert(map<char, int>::value_type(s[j], j + 1));

        }
        return max_len;
    }
};
*/

int main() {
    Solution* solu = new Solution();
    string str = "abcabcbb";
    cout << solu->lengthOfLongestSubstring(str);
    return 0;
}