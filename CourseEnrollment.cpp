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

vector < long > getSessions(long launchDate, int repeatFrequency, long enrollmentDate) {

	vector<long> res;
	res.resize(3);
	long weekMillis = 604800L * 1000;
	long dayMillis = 86400L * 1000;

	int day = launchDate % weekMillis % 7;
	if (day != 4){
		int i = 1;
		for (; i < 7; i++) {
			if ((day + i) % 7 == 4) {
				break;
			}

		}
		launchDate += i * dayMillis;
	}

	day = enrollmentDate % weekMillis % 7;
	if (day != 4){
		int i = 1;
		for (; i < 7; i++) {
			if ((day + i) % 7 == 4) {
				break;
			}

		}
		enrollmentDate += i * dayMillis;
		while (launchDate < enrollmentDate){
			launchDate += repeatFrequency * weekMillis;
		}
	}
	launchDate = max(launchDate, enrollmentDate);
	for (int i = 0; i < 3; i++) {
		res[i] = launchDate;

		launchDate += repeatFrequency * weekMillis;

	}
	return res;

}


vector < vector < long > > getSessionSchedule(vector < vector < long > > specializationCourses, long enrollmentDate) {

	int n = specializationCourses.size();
	vector<vector<long>> res(n, vector<long>(2, 0));
	long weekMillis = 604800L * 1000;
	long dayMillis = 86400L * 1000;

	long lastEnd = 0;
	for (int i = 0; i < specializationCourses.size(); i++) {
		vector<long> top = specializationCourses[i];

		long launchDate = top[0];
		long repeatFrequency = top[1];
		long duration = top[2];

		int day = launchDate % weekMillis % 7;
		if (day != 4){
			if (day > 4){
				launchDate += (4 + 7 - day) * dayMillis;
			}
			else{
				launchDate += (4 - day) * dayMillis;
			}
		}


		while (launchDate < lastEnd){
			launchDate += repeatFrequency * weekMillis;
		}


		day = enrollmentDate % weekMillis % 7;
		if (day != 4){

			if (day > 4){
				enrollmentDate += (4 + 7 - day) * dayMillis;
			}
			else{
				enrollmentDate += (4 - day) * dayMillis;
			}

			while (launchDate < enrollmentDate){
				launchDate += repeatFrequency * weekMillis;
			}


		}
		launchDate = max(launchDate, enrollmentDate);
		res[i][0] = launchDate;
		launchDate += duration * weekMillis;
		lastEnd = launchDate;
		res[i][1] = launchDate;
	}
	return res;
}