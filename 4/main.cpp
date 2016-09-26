#include <iostream>
#include <vector>

using namespace std;

//二路归并排序算法
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
       vector<int> res;
        int n = int(nums1.size());
        int m = int(nums2.size());
        int i = 0;
        int j = 0;
        while (i < n && j < m) {
            if (nums1[i] < nums2[j]) {
                res.push_back(nums1[i++]);
            }else {
                res.push_back(nums2[j++]);
            }
        }
        while (i < n) {
            res.push_back(nums1[i++]);
        }
        while (j < m) {
            res.push_back(nums2[j++]);
        }
        if (res.size() % 2 == 0) {
            double tmp = (res[res.size() / 2 - 1] + res[res.size() / 2]) / 2.0;
            return tmp;
        }else {
            return res[res.size() / 2];
        }
    }
};


int main() {
    Solution* solu = new Solution();
    vector<int>nums1{1, 3};
    vector<int>nums2{2};
    cout << solu->findMedianSortedArrays(nums1, nums2);
    return 0;
}