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

using namespace std;

/*
class MyHeap{

	vector<pair<int, char>> heap;
	unordered_map<char, int> heapMap;

	void propagateDown(int pos){


		while (2 * pos + 1 < heap.size()){

			int firstChild = 2 * pos + 1;
			int secondChild = 2 * pos + 2;

			if (2 * pos + 2 < heap.size()){


				bool firstChildSmaller = heap[2 * pos + 1].first < heap[2 * pos + 2].first ? true : false;
				if (firstChildSmaller){
					if (heap[pos].first > heap[firstChild].first){

						heapMap[heap[pos].second] = firstChild;
						heapMap[heap[firstChild].second] = pos;

						pair<int, char> temp = heap[pos];
						heap[pos] = heap[firstChild];
						heap[firstChild] = temp;
						pos = firstChild;
						continue;
					}
					else{
						break;
					}
				}
				else{
					if (heap[pos].first > heap[secondChild].first){

						heapMap[heap[pos].second] = secondChild;
						heapMap[heap[secondChild].second] = pos;

						pair<int, char> temp = heap[pos];
						heap[pos] = heap[secondChild];
						heap[secondChild] = temp;
						pos = secondChild;
						continue;
					}
					else{
						break;
					}

				}

			}
			else{

				if (heap[pos].first > heap[firstChild].first){

					heapMap[heap[pos].second] = firstChild;
					heapMap[heap[firstChild].second] = pos;

					pair<int, char> temp = heap[pos];
					heap[pos] = heap[firstChild];
					heap[firstChild] = temp;
					pos = firstChild;
					continue;
				}
				else{
					break;
				}

			}
		}

	}


	void propagateUp(int pos){

		while (pos > 0){

			int parent = (pos - 1) / 2;

			if (heap[parent].first > heap[pos].first){

				heapMap[heap[pos].second] = parent;
				heapMap[heap[parent].second] = pos;

				pair<int, char> temp = heap[parent];
				heap[parent] = heap[pos];
				heap[pos] = temp;
			}

			pos = parent;
		}
	}

public:

	MyHeap(){
	}

	MyHeap(vector<pair<int, char>> inputHeap){

		heap.reserve(inputHeap.size());

		for (int x = 0; x != inputHeap.size(); x++){

			heap.push_back(inputHeap[x]);
			heapMap.insert(make_pair(inputHeap[x].second, heap.size() - 1));
		}

		for (int x = (heap.size() - 1) / 2; x >= 0; x--){
			propagateDown(x);
		}
	}

	void insert(pair<int, char> vertex){

		heap.push_back(vertex);
		heapMap.insert(make_pair(vertex.second, heap.size() - 1));

		propagateUp(heap.size() - 1);
	}

	void popTop(){
		auto it = heapMap.find(heap[0].second);
		cout << heap[0].second << endl;
		heapMap.erase(it);



		heap[0] = heap[heap.size() - 1];
		heapMap[heap[0].second] = 0;
		heap.pop_back();
		propagateDown(0);
	}

	pair<int, char> top(){
		return heap[0];
	}

	void decrementVal(int pos, int val){
		heap[pos].first = val;
		propagateUp(pos);
	}

	int find(char vertex){

		return heapMap.find(vertex)->second;
	}

	bool empty(){
		return heap.empty() ? true : false;
	}

	int size(){
		return heap.size();
	}

	pair<int, char> operator[](int x){
		return heap[x];
	}

	bool inHeap(char vertex){

		return heapMap.find(vertex) == heapMap.end() ? false : true;
	}
};

void Dijkastras(vector<vector<int>> &graph, vector<char> & verticies, char vertex, map<char, int> &ret){


	vector<pair<int, char>> temp;

	for (int x = 0; x != verticies.size(); x++){
		if (verticies[x] == vertex){
			temp.push_back(make_pair(0, verticies[x]));
		}
		else{
			temp.push_back(make_pair(INT_MAX, verticies[x]));
		}
	}

	MyHeap mHeap(temp);


	while (!mHeap.empty()){


		ret.insert(make_pair(mHeap.top().second, mHeap.top().first));

		char nextNode = mHeap.top().second;
		mHeap.popTop();
		int index = find(verticies.begin(), verticies.end(), nextNode) - verticies.begin();

		for (int x = 0; x != graph.size(); x++){
			if (mHeap.inHeap(verticies[x])){
				int pos = mHeap.find(verticies[x]);
				if (graph[index][x] != 0 && mHeap[pos].first > graph[index][x] + ret.find(nextNode)->second){
					mHeap.decrementVal(pos, graph[index][x] + ret.find(nextNode)->second);
				}
			}
		}


	}



}



int main() {

	vector<char> verticies{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };

	vector<vector<int>> graph{ { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};

	map<char, int> ret;
	Dijkastras(graph, verticies, 'a', ret);

	return 0;
}

*/