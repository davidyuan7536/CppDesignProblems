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
class Vertex{


	int m_vertex;
	set<int> m_vertexSet;

public:

	Vertex(){}

	Vertex(int vertex, set<int> vertexSet){
		m_vertex = vertex;
		m_vertexSet = vertexSet;
	}

	bool operator==(const Vertex &a) const{
		return m_vertex == a.m_vertex && m_vertexSet == a.m_vertexSet;
	}

	void setVertex(int val){
		m_vertex = val;
	}

	void insertIntoVertexSet(int val){
		m_vertexSet.insert(val);
	}

	void popBackVertexSet(int val){
		m_vertexSet.erase(val);
	}

	int getVertex() const{
		return m_vertex;
	}

	set<int> getVertexSet() const{
		return m_vertexSet;
	}

	set<int> vertexSetWithout(int val){
		set<int> ret = m_vertexSet;
		ret.erase(val);
		return ret;
	}

	bool isInSet(int val){
		return m_vertexSet.find(val) == m_vertexSet.end() ? false : true;
	}
};


struct MyHash
{
	size_t operator()(const Vertex& vertex) const
	{
		size_t h1 = hash<int>{}(vertex.getVertex());
		size_t h2;
		if (vertex.getVertexSet().size() != 0){
			h2 = hash<int>{}(*(vertex.getVertexSet().begin()));
		}
		else{
			h2 = hash<int>{}(71);
		}
		return h1 ^ (h2 << 1);
	}
};

struct VertexEqual{

	bool operator()(const Vertex &vertexA, const Vertex &vertexB) const{
		return vertexA == vertexB;
	}

};

void generateSetsHelper(vector<Vertex> &retVec, Vertex &vertexHolder, vector<int> &verticies, int left, int &current, int &index, int start){

	if (index == 0){
		retVec.push_back(vertexHolder);
		return;
	}

	if (index == start){
		for (int x = left; x < verticies.size(); x++){
			current = x;
			vertexHolder.setVertex(verticies[x]);
			generateSetsHelper(retVec, vertexHolder, verticies, left, current, --index, start);
			index++;
			continue;
		}
	}
	else{
		for (int x = left; x < verticies.size(); x++){

			if (x == current || vertexHolder.isInSet(verticies[x])){
				continue;
			}
			else{
				vertexHolder.insertIntoVertexSet(verticies[x]);
				int val = verticies[x];
				generateSetsHelper(retVec, vertexHolder, verticies, ++left, current, --index, start);

				vertexHolder.popBackVertexSet(val);
				index++;
			}

		}
	}



}



vector<vector<Vertex>> generateSets(vector<int> &verticies){

	vector<vector<Vertex>> retVec;

	for (int x = 1; x != verticies.size(); x++){

		vector<Vertex> vertexVector;
		Vertex vertexHolder;
		int left = 1;
		int current = 0;
		int start = x;
		int index = x;
		generateSetsHelper(vertexVector, vertexHolder, verticies, left, current, index, start);
		retVec.push_back(vertexVector);
	}

	return retVec;

}


int travelingSalesMan(vector<vector<int>> &graph, vector<int> &verticies){

	unordered_map<Vertex, int, MyHash, VertexEqual> dpMap;
	unordered_map<Vertex, Vertex, MyHash, VertexEqual> parent;

	vector<vector<Vertex>> vertexSets = generateSets(verticies);

	set<int> lastSet{ verticies.begin() + 1, verticies.end() };
	Vertex last(0, lastSet);
	vector<Vertex> lastVec{ last };
	vertexSets.push_back(lastVec);

	for (int i = 0; i != vertexSets.size(); i++){
		for (int j = 0; j != vertexSets[i].size(); j++){

			int distance;

			if (i == 0){
				distance = graph[0][vertexSets[i][j].getVertex()];
				dpMap.insert(make_pair(vertexSets[i][j], distance));
				continue;
			}

			int endIndex = vertexSets[i][j].getVertex();
			set<int> currentVertexSet = vertexSets[i][j].getVertexSet();
			int min = INT_MAX;

			for (auto it : currentVertexSet){

				int beginIndex = it;
				distance = graph[beginIndex][endIndex];
				Vertex temp(beginIndex, vertexSets[i][j].vertexSetWithout(beginIndex));
				distance += dpMap.find(temp)->second;
				if (distance < min){
					min = distance;
					parent[vertexSets[i][j]] = temp;
				}
			}

			dpMap.insert(make_pair(vertexSets[i][j], min));



		}
	}

	return 0;
}


int main() {

	vector<int> verticies{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

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


	vector<int> verticies2{ 0, 1, 2, 3 };

	vector<vector<int>> graph2{ { 0, 1, 15, 6 },
	{ 2, 0, 7, 3 },
	{ 9, 6, 0, 12 },
	{ 10, 4, 8, 0 }
	};



	clock_t t1, t2;
	t1 = clock();

	travelingSalesMan(graph, verticies);

	t2 = clock();
	float timeDiff = ((float)t2 - (float)t1);
	std::cout << timeDiff / CLOCKS_PER_SEC;

	return 0;
}
*/
