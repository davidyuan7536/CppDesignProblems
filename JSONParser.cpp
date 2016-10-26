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

class Value{

public:
	virtual bool isDict() = 0;

};

class StringValue : virtual public Value{

private:
	string m_string;
public:
	StringValue(){

	}

	StringValue(string & value){
		m_string = value;
	}

	string getString(){
		return m_string;
	}

	bool isDict(){
		return false;
	}
};

class DictValue : virtual public Value{
private:
	map<string, Value*> m_map;
public:
	DictValue(){

	}

	DictValue(map<string, Value*> &map){
		m_map = map;
	}

	map<string, Value*> getMap(){
		return m_map;
	}

	bool isDict(){
		return true;
	}

	void insert(pair<string, Value*> newMapping){
		m_map.insert(newMapping);
	}
};


void helper(string & retString, map<string, Value*> myMap){

	retString += "{";
	for (auto it = myMap.begin(); it != myMap.end(); it++){
		if (it->second->isDict()){
			retString += it->first + " : ";
			DictValue *temp = dynamic_cast<DictValue*>(it->second);
			helper(retString, temp->getMap());

		}
		else{
			StringValue *temp = dynamic_cast<StringValue*>(it->second);
			retString += it->first + " : " + temp->getString();
			if (it != --myMap.end())
				retString += +" , ";
		}
	}

	retString += "}";

}

string dictionaryToJson(DictValue * dictionary){
	string retString = "";
	map<string, Value*> myMap = dictionary->getMap();
	helper(retString, myMap);

	return retString;
}

void helper2(DictValue &myDict, string json){

	string keyString = "";
	string valueString = "";

	bool key = false;
	bool value = false;
	bool previousDict = false;

	for (int i = 0; i < json.length(); i++){

		if (!value && json[i] == '{'){
			key = true;
			continue;
		}
		else if (json[i] == ','){
			key = true;
			value = false;

			if (previousDict){
				i++;
				keyString = "";
				valueString = "";
				continue;
			}

			previousDict = false;

			valueString.pop_back();
			StringValue * temp = new StringValue(valueString);
			myDict.insert(make_pair(keyString, temp));
			i++;
			keyString = "";
			valueString = "";
			continue;
		}
		else if (json[i] == ':'){
			key = false;
			value = true;
			keyString.pop_back();
			i++;
			continue;
		}
		else if (json[i] == '}'){
			if (previousDict)
				return;

			StringValue * temp = new StringValue(valueString);
			myDict.insert(make_pair(keyString, temp));
			i++;
			keyString = "";
			valueString = "";
			return;
		}
		else{
			if (key){
				keyString += json[i];
			}
			if (value){
				if (json[i] == '{'){

					previousDict = true;
					DictValue *temp = new DictValue;
					myDict.insert(make_pair(keyString, temp));
					int counter = 1;
					stack<char> myStack;
					myStack.push('{');
					while (!myStack.empty()){
						if (json[i + counter] == '}'){
							myStack.pop();
						}
						else if (json[i + counter] == '{'){
							myStack.push('{');
						}
						counter++;
					}

					helper2(*temp, json.substr(i, counter));
					i += counter;
					keyString = "";
					valueString = "";
					continue;

				}
				else{
					valueString += json[i];
					continue;
				}
			}

		}
	}

}

DictValue * jsonToDictionary(string json){

	DictValue *retDict = new DictValue;
	helper2(*retDict, json);
	return retDict;
}

/*
int main(){

	string s1("blueberry");
	string s2("rasberry");
	string s3("cranberry");
	StringValue temp1(s1);
	StringValue temp2(s2);
	StringValue temp3(s3);


	pair<string, Value*> tem = make_pair("a", &temp1);
	pair<string, Value*> tem1 = make_pair("c", &temp2);
	pair<string, Value*> tem2 = make_pair("d", &temp3);

	map<string, Value*> t1{ tem1, tem2 };

	DictValue tempDict{ t1 };

	pair<string, Value*> tem3 = make_pair("b", &tempDict);
	map<string, Value*> t2{ tem, tem3 };
	DictValue tempDict2{ t2 };


	string retString = dictionaryToJson(&tempDict2);
	cout << retString << endl;
	DictValue *tempDict3 = jsonToDictionary(retString);
	cout << dictionaryToJson(tempDict3) << endl;

}

*/