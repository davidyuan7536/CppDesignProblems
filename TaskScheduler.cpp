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
#include "leetcode.h"

/*
bool anagrams(string s1, string s2){

	if (s1.length() != s2.length()){
		return false;
	}
	vector<int> hash(256, 0);
	for (int i = 0; i < s1.length(); i++){
		int t = s1[i];
		hash[t]++;
	}
	for (int i = 0; i < s2.length(); i++){
		int t = s2[i];
		if (hash[t] == 0){
			return false;
		}
		hash[t]--;
	}
	return true;
}



struct comparer{
	bool operator() (std::pair<int, int> a, std::pair<int, int> b){
		return a.first < b.first;
	}
};
std::string smartAssigning(std::vector<std::string> names, std::vector<bool> statuses, std::vector<int> projects, std::vector<int> tasks) {

	std::vector<std::pair<int, int>> task;
	for (int i = 0; i < tasks.size(); i++){
		task.push_back(std::make_pair(tasks[i], i));
	}
	comparer mycomp;
	std::sort(task.begin(), task.end(), mycomp);

	int min = INT_MAX;
	int ind = 0;
	int previous = INT_MIN;
	for (int i = 0; i < task.size(); i++){
		if (previous != INT_MIN && task[i].first != previous){
			break;
		}

		if (!statuses[task[i].second]){
			previous = task[i].first;
			if (projects[task[i].second] < min){
				min = projects[task[i].second];
				ind = task[i].second;
			}

		}
	}
	return names[ind];
}


int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

std::vector<std::string> recurringTask(std::string firstDate, int k, std::vector<std::string> daysOfTheWeek, int n) {


	vector<string> weekDays{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	vector<int> numberOfDays{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	string day;
	string month;
	string year;
	int counter = 0;
	for (int i = 0; i < firstDate.length(); i++){
		if (firstDate[i] == '/'){
			counter++;
			continue;
		}
		if (counter == 0)
			day += firstDate[i];
		if (counter == 1)
			month += firstDate[i];
		if (counter == 2)
			year += firstDate[i];
	}

	bool gapYear = false;

	deque<int> dow;
	for (int i = 0; i < daysOfTheWeek.size(); i++){
		for (int j = 0; j < weekDays.size(); j++){
			if (daysOfTheWeek[i] == weekDays[j]){
				dow.push_back(j);
				break;
			}
		}
	}

	int startDow = dayofweek(stoi(day), stoi(month), stoi(year));
	while (dow.front() != startDow){
		dow.push_back(dow.front());
		dow.pop_front();
	}
	dow.pop_front();

	vector<string> ret;

	while (n > 0){

		string newStart = day + '/' + month + '/' + year;
		ret.push_back(newStart);
		n--;
		if (n == 0){
			break;
		}
		int tempStartDow = startDow;
		int dayInt = stoi(day);
		int monInt = stoi(month);
		int yearInt = stoi(year);

		if ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0){
			gapYear = true;
		}
		else{
			gapYear = false;
		}

		for (int j = 0; j < dow.size(); j++){
			if (dow[j] > tempStartDow){
				dayInt += dow[j] - tempStartDow;
				tempStartDow = dow[j];
			}
			else{
				dayInt += 7 + dow[j] - tempStartDow;
				tempStartDow = dow[j];
			}

			if (dayInt > numberOfDays[monInt - 1] && !(gapYear && monInt == 2 && dayInt == 29)){
				if (gapYear && monInt == 2){
					dayInt -= 29;
				}
				else{
					dayInt -= numberOfDays[monInt - 1];
				}

				monInt++;
				if (monInt > 12){
					monInt = 1;
					yearInt++;
					if ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0){
						gapYear = true;
					}
					else{
						gapYear = false;
					}
				}
			}
			newStart = "";
			if (dayInt < 10){
				newStart += '0' + to_string(dayInt);
			}
			else{
				newStart += to_string(dayInt);
			}
			newStart += '/';
			if (monInt < 10){
				newStart += '0' + to_string(monInt);
			}
			else{
				newStart += to_string(monInt);
			}
			newStart += '/';
			newStart += to_string(yearInt);
			ret.push_back(newStart);
			n--;
			if (n == 0){
				break;
			}
		}

		dayInt = stoi(day);
		monInt = stoi(month);
		yearInt = stoi(year);

		if ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0){
			gapYear = true;
		}
		else{
			gapYear = false;
		}


		int nextRepeat = k * 7;
		dayInt += nextRepeat;
		while (dayInt > numberOfDays[monInt - 1] && !(gapYear && monInt == 2 && dayInt == 29)){
			if (gapYear && monInt == 2){
				dayInt -= 29;
				monInt++;
				if (monInt > 12){
					monInt = 1;
					yearInt++;
					if ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0){
						gapYear = true;
					}
					else{
						gapYear = false;
					}

				}
			}
			else{
				dayInt -= numberOfDays[monInt - 1];
				monInt++;
				if (monInt > 12){
					monInt = 1;
					yearInt++;
					if ((yearInt % 4 == 0 && yearInt % 100 != 0) || yearInt % 400 == 0){
						gapYear = true;
					}
					else{
						gapYear = false;
					}
				}
			}
		}

		if (dayInt < 10){
			day = '0' + to_string(dayInt);
		}
		else{
			day = to_string(dayInt);
		}
		if (monInt < 10){
			month = '0' + to_string(monInt);
		}
		else{
			month = to_string(monInt);
		}
		year = to_string(yearInt);

	}

	return ret;
}


int main(){



	string firstDate = "23/2/2016";
	int k = 4;
	vector<string> daysOfTheWeek{ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	int n = 21;
	vector<string> temp = recurringTask(firstDate, k, daysOfTheWeek, n);
	for (auto it : temp){
		cout << it << endl;
	}
}
*/