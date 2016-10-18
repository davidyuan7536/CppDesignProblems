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
class Heap{
private:
	vector<int> m_heap;

	void rotateUp(int pos){
		while (pos > 0){
			int parent = (pos - 1) / 2;
			if (m_heap[parent] > m_heap[pos]){
				int temp = m_heap[parent];
				m_heap[parent] = m_heap[pos];
				m_heap[pos] = temp;
				pos = parent;
			}
			else{
				return;
			}
		}
	}

	void rotateDown(int pos){

		while (2 * pos + 1 < m_heap.size()){
			int left = pos * 2 + 1;
			int right = pos * 2 + 2;
			if (right < m_heap.size())
				left = m_heap[left] < m_heap[right] ? left : right;

			if (m_heap[pos] > m_heap[left]){
				int temp = m_heap[pos];
				m_heap[pos] = m_heap[left];
				m_heap[left] = temp;
			}
			else{
				return;
			}
			pos = left;

		}

	}

public:

	void addNum(int num) {
		m_heap.push_back(num);
		rotateUp(m_heap.size() - 1);
	}

	int pop(){
		int ret = m_heap[0];
		m_heap[0] = m_heap[m_heap.size() - 1];
		m_heap.pop_back();
		rotateDown(0);
		return ret;
	}

	void print(){
		for (auto it : m_heap){
			cout << it << " ";
		}
		cout << endl;
	}

	bool empty(){
		return m_heap.empty();
	}

};