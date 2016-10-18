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

class MedianFinder {
private:
	list<int> m_list;
	list<int>::iterator midIt;
	int balance = 0;
	map<int, list<int>::iterator> m_map;

public:

	// Adds a number into the data structure.
	void addNum(int num) {

		if (m_list.size() == 0){
			m_list.push_back(num);
			m_map.insert(make_pair(num, --m_list.end()));
			midIt = --m_list.end();
			return;
		}

		auto it = m_map.lower_bound(num);
		if (it == m_map.end()){
			m_list.push_back(num);
			if (m_map.find(num) == m_map.end()){
				m_map.insert(make_pair(num, --m_list.end()));
			}
			else{
				m_map[num] = --m_list.end();
			}

			balance++;
			if (balance > 1){
				midIt++;
				balance = 0;
			}

		}
		else{
			auto temp = m_list.insert(it->second, num);

			if (m_map.find(num) == m_map.end()){
				m_map.insert(make_pair(num, temp));
			}
			else{
				m_map[num] = temp;
			}

			if (*midIt < num){
				balance++;
				if (balance > 1){
					midIt++;
					balance = 0;
				}
			}
			else{
				balance--;
				if (balance < -1){
					midIt--;
					balance = 0;
				}

			}

		}
	}

	// Returns the median of current data stream
	double findMedian() {
		if (m_list.size() % 2 == 0){
			if (balance == 1){
				double first = *midIt;
				midIt++;
				double second = *midIt;
				midIt--;
				return (first + second) / 2;
			}
			else{
				double second = *midIt;
				midIt--;
				int first = *midIt;
				midIt++;
				return (first + second) / 2;
			}

		}
		else{
			int first = *midIt;
			return first;
		}
	}
};
