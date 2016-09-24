/*************************************************************************
*     File Name: test.cpp
*     Author: zhonghuasong
*     Mail: zhonghsuestc@163.com
*     Create Time: 五  9/23 08:27:43 2016
*************************************************************************/

#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> res;
		for (size_t i = 0; i < nums.size() - 1; i++) {
			for (size_t j = i + 1; j < nums.size(); j++) {
				if (nums[i] + nums[j] == target) {
					res.push_back(i);
					res.push_back(j);
					cout<<i<<","<<j<<endl;
					return res;
				}
			}
		}
		return res;
	}
};

int main() {
	Solution* solu = new Solution();
	int array[] = {2, 7, 11, 15};
	int target = 13;
	size_t count = sizeof(array) / sizeof(int);
	vector<int> nums(array, array + count);

	solu->twoSum(nums, target);

	return 0;
}
