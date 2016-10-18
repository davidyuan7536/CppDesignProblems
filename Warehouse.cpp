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

struct Warehouse{
	string m_id;
	int m_capacity;
	int m_price;
	int m_originalCapacity;


	Warehouse(string id, int capacity, int price = 30){
		m_id = id;
		m_capacity = capacity;
		m_originalCapacity = capacity;
		m_price = price;
	}
};

struct Store{
	string m_id;

	Store(string id){
		m_id = id;
	}
};

void printUnorderedMap(unordered_map<string, int> temp){

	for (auto it : temp){

		cout << it.first << ": " << it.second;
		cout << "   ";
	}
}

void printUnorderedSet(unordered_set<string> temp){

	for (auto it : temp){

		cout << it << ", ";
	}
}

void wareHouseStoreProblemHelper(vector<unordered_set<string>> & retVec, vector<unordered_set<string>> & bestRetVec, int &costOfOperation, int &totalCost, int & bestCost, vector<Store> &storeMap, vector<Warehouse> &warehouseMap, unordered_map<string, unordered_map<string, int>> &costMap, int index){

	if (index >= storeMap.size()){
		if (totalCost + costOfOperation < bestCost){
			bestCost = totalCost + costOfOperation;
			bestRetVec = retVec;
		}
		return;
	}

	auto storeIt = costMap.find(storeMap[index].m_id);

	for (int x = 0; x != warehouseMap.size(); x++){

		if (warehouseMap[x].m_capacity <= 0){
			continue;
		}


		int cost = storeIt->second.find(warehouseMap[x].m_id)->second;

		totalCost += cost;
		retVec[x].insert(storeMap[index].m_id);
		if (warehouseMap[x].m_originalCapacity == warehouseMap[x].m_capacity)
			costOfOperation += warehouseMap[x].m_price;
		warehouseMap[x].m_capacity--;
		wareHouseStoreProblemHelper(retVec, bestRetVec, costOfOperation, totalCost, bestCost, storeMap, warehouseMap, costMap, index + 1);
		retVec[x].erase(storeMap[index].m_id);
		totalCost -= cost;
		warehouseMap[x].m_capacity++;
		if (warehouseMap[x].m_originalCapacity == warehouseMap[x].m_capacity)
			costOfOperation -= warehouseMap[x].m_price;

	}

}

vector<unordered_set<string>> wareHouseStoreProblem(vector<Store> &storeMap, vector<Warehouse> &warehouseMap, unordered_map<string, unordered_map<string, int>> &costMap){

	vector<unordered_set<string>> retVec;
	retVec.resize(warehouseMap.size());
	vector<unordered_set<string>> bestRetVec;
	int costOfOperation = 0;
	int totalCost = 0;
	int bestCost = INT_MAX;
	int index = 0;


	wareHouseStoreProblemHelper(retVec, bestRetVec, costOfOperation, totalCost, bestCost, storeMap, warehouseMap, costMap, index);
	return bestRetVec;
}

/*
int main() {

	Store store1("store1");
	Store store2("store2");
	Store store3("store3");
	Store store4("store4");
	Store store5("store5");
	Store store6("store6");
	Store store7("store7");
	Store store8("store8");
	Store store9("store9");
	Store store10("store10");
	vector<Store> storeMap{ store1, store2, store3, store4, store5, store6, store7, store8, store9, store10 };


	Warehouse Bonn("Bonn", 1);
	Warehouse Bordeaux("Bordeaux", 4);
	Warehouse London("London", 2);
	Warehouse Paris("Paris", 1);
	Warehouse Rome("Rome", 3);
	vector<Warehouse> warehouseMap{ Bonn, Bordeaux, London, Paris, Rome };

	unordered_map<string, unordered_map<string, int>> supplyCostMap;

	vector<vector<int>> supplyCost{
		{ 20, 24, 11, 25, 30 },
		{ 28, 27, 82, 83, 74 },
		{ 74, 97, 71, 96, 70 },
		{ 2, 55, 73, 69, 61 },
		{ 46, 96, 59, 83, 4 },
		{ 42, 22, 29, 67, 59 },
		{ 1, 5, 73, 59, 56 },
		{ 10, 73, 13, 43, 96 },
		{ 93, 35, 63, 85, 46 },
		{ 47, 65, 55, 71, 95 }
	};


	for (int x = 0; x != supplyCost.size(); x++){
		unordered_map<string, int> temp;
		for (int y = 0; y != supplyCost[x].size(); y++){
			temp.insert(make_pair(warehouseMap[y].m_id, supplyCost[x][y]));
		}
		supplyCostMap.insert(make_pair(storeMap[x].m_id, temp));
		temp.clear();
	}

	vector<unordered_set<string>> returnVec = wareHouseStoreProblem(storeMap, warehouseMap, supplyCostMap);

	for (auto it : returnVec){
		printUnorderedSet(it);
		cout << endl;
	}

	return 0;


}
*/
