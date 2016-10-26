#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <deque>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <math.h> 
#include <time.h>
#include <cstdio> 
#include <time.h>

using namespace std;

pair<pair<int, int>, int> segmentTree(vector<int> & nums, vector<pair<pair<int, int>, int>> &st, int left, int right, int pos){

	if (right < left){
		return make_pair(make_pair(0, 0), 0);
	}

	if (right == left){
		st[pos] = make_pair(make_pair(nums[left], nums[left]), 1);
		return st[pos];
	}

	int mid = left + (right - left) / 2;
	pair<pair<int, int>, int> l = segmentTree(nums, st, left, mid, pos * 2 + 1);
	pair<pair<int, int>, int> r = segmentTree(nums, st, mid + 1, right, pos * 2 + 2);
	st[pos] = make_pair(make_pair(max(l.first.first, r.first.first), min(l.first.second, r.first.second)), l.second + r.second);
	return st[pos];
}

int queryCountSmaller(vector<int>&nums, int it, vector<pair<pair<int, int>, int>> &st, int left, int right, int pos, int l, int r){

	if (l <= left && right <= r){
		if (nums[it] <= st[pos].first.first){

			if (nums[it] <= st[pos].first.second || st[pos].second <= 1){
				return 0;
			}

			int mid = left + (right - left) / 2;
			int resL = queryCountSmaller(nums, it, st, left, mid, pos * 2 + 1, l, r);
			int resR = queryCountSmaller(nums, it, st, mid + 1, right, pos * 2 + 2, l, r);
			return resL + resR;
		}
		else{
			return st[pos].second;
		}
	}
	else if (r < left || right < l){
		return 0;
	}
	else{
		int mid = left + (right - left) / 2;
		int resL = queryCountSmaller(nums, it, st, left, mid, pos * 2 + 1, l, r);
		int resR = queryCountSmaller(nums, it, st, mid + 1, right, pos * 2 + 2, l, r);
		return resL + resR;
	}
}
