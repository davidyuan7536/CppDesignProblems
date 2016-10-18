
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

/*
struct Request{

	std::string m_id;
	std::string m_location;
	int m_start;
	int m_end;

	Request(std::string id, std::string location, int start, int end) :
		m_id{ id },
		m_location{ location },
		m_start{ start },
		m_end{ end }
	{}


};
class Scheduling{

public:

	static int findLocationSlot(std::string locationID){
		if (locationID == "center-top"){
			return 0;
		}
		else if (locationID == "right-top"){
			return 1;
		}
		else if (locationID == "center-middle"){
			return 2;
		}
		else if (locationID == "center-bottom"){
			return 3;
		}
		else if (locationID == "right-middle"){
			return 4;
		}
		else if (locationID == "right-bottom"){
			return 5;
		}
		else{
			return -1;
		}
	}

	static void validSchedule(std::list<Request> &requestList, std::unordered_map<std::string, int> &contentScoreMap, std::unordered_map<std::string, double> &locationValueMap, std::vector<std::string> &acceptedRequest, std::vector<std::string> &rejectedRequest){

		std::vector<std::unordered_map<int, std::vector<std::string>>> validScheduleMap;
		validScheduleMap.resize(locationValueMap.size());

		for (auto requestListIterator : requestList){

			if (findLocationSlot(requestListIterator.m_location) == -1){
				throw std::exception();
			}
			if (checkTimeSlot(requestListIterator, validScheduleMap)){

				if (checkClashingContent(requestListIterator, validScheduleMap)){

					addRequestToMap(requestListIterator, validScheduleMap);
					acceptedRequest.push_back(requestListIterator.m_id);

				}
				else{
					rejectedRequest.push_back(requestListIterator.m_id);
				}
			}
			else{
				rejectedRequest.push_back(requestListIterator.m_id);
			}


		}

	}

	static bool checkLocation(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){

		if (findLocationSlot(request.m_location) == -1){
			return false;
		}
		else{

			int location = findLocationSlot(request.m_location);

		}
		return true;
	}

	static bool checkTimeSlot(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){

		int location = findLocationSlot(request.m_location);
		for (int i = request.m_start; i <= request.m_end; i++){

			auto iterator = validScheduleMap[location].find(i);

			if (iterator != validScheduleMap[location].end()){
				if (iterator->second.size() < 3){
					continue;
				}
				return false;
			}

		}
		return true;
	}

	static bool checkClashingContent(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){

		int location = findLocationSlot(request.m_location);
		for (int i = request.m_start; i <= request.m_end; i++){

			auto iterator = validScheduleMap[location].find(i);

			if (iterator != validScheduleMap[location].end()){
				if (std::find(iterator->second.begin(), iterator->second.end(), request.m_id) != iterator->second.end()){
					return false;
				}
			}

		}
		return true;

	}

	static void addRequestToMap(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){

		int location = findLocationSlot(request.m_location);
		for (int i = request.m_start; i <= request.m_end; i++){

			if (validScheduleMap[location].find(i) != validScheduleMap[location].end()){
				validScheduleMap[location].find(i)->second.push_back(request.m_id);
			}
			else{
				std::vector<std::string> contentIdContainer{ request.m_id };
				validScheduleMap[location].insert(std::make_pair(i, contentIdContainer));
			}

		}
	}

};

class Scheduling2{

public:

	static int findLocationSlot(std::string locationID){
		if (locationID == "center-top"){
			return 0;
		}
		else if (locationID == "right-top"){
			return 1;
		}
		else if (locationID == "center-middle"){
			return 2;
		}
		else if (locationID == "center-bottom"){
			return 3;
		}
		else if (locationID == "right-middle"){
			return 4;
		}
		else if (locationID == "right-bottom"){
			return 5;
		}
		else{
			return -1;
		}
	}

	static std::string findLocationID(int locationID){
		switch (locationID){
		case 0:
			return "center-top";
		case 1:
			return "right-top";
		case 2:
			return "center-middle";
		case 3:
			return "center-bottom";
		case 4:
			return "right-middle";
		case 5:
			return "right-bottom";
		default:
			return "unknown";
		}
	}

	static void validSchedule(std::list<Request> &requestList, std::unordered_map<std::string, int> &contentScoreMap, std::unordered_map<std::string, double> &locationValueMap, std::vector<std::string> &acceptedRequest, std::vector<std::string> &rejectedRequest){

		std::unordered_map<std::string, std::unordered_map<int, std::vector<std::string>>> validScheduleMap;
		for (int x = 0; x != 6; x++){
			std::unordered_map<int, std::vector<std::string>> timeSlotMap;
			validScheduleMap.insert(make_pair(findLocationID(x), timeSlotMap));
		}


		for (auto requestListIterator : requestList){

			if (findLocationSlot(requestListIterator.m_location) == -1){
				throw std::exception();
			}


			if (checkTimeSlot(requestListIterator, validScheduleMap)){

				if (checkClashingContent(requestListIterator, validScheduleMap)){

					addRequestToMap(requestListIterator, validScheduleMap);
					acceptedRequest.push_back(requestListIterator.m_id);

				}
				else{
					rejectedRequest.push_back(requestListIterator.m_id);
				}
			}
			else{
				rejectedRequest.push_back(requestListIterator.m_id);
			}


		}

	}

	static bool checkLocation(Request request, std::unordered_map<std::string, std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){

		if (validScheduleMap.find(request.m_location) == validScheduleMap.end()){
			std::unordered_map<int, std::vector<std::string>> timeSlotMap;
			validScheduleMap.insert(make_pair(request.m_location, timeSlotMap));
			addRequestToMap(request, validScheduleMap);
			return true;
		}
		else{
			return false;
		}

	}

	static bool checkTimeSlot(Request request, std::unordered_map<std::string, std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){


		for (int i = request.m_start; i <= request.m_end; i++){

			auto iterator = validScheduleMap.find(request.m_location)->second.find(i);

			if (iterator != validScheduleMap.find(request.m_location)->second.end()){
				if (iterator->second.size() < 3){
					continue;
				}
				return false;
			}

		}
		return true;
	}

	static bool checkClashingContent(Request request, std::unordered_map<std::string, std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){


		for (int i = request.m_start; i <= request.m_end; i++){

			auto iterator = validScheduleMap.find(request.m_location)->second.find(i);

			if (iterator != validScheduleMap.find(request.m_location)->second.end()){
				if (std::find(iterator->second.begin(), iterator->second.end(), request.m_id) != iterator->second.end()){
					return false;
				}
			}

		}
		return true;

	}

	static void addRequestToMap(Request request, std::unordered_map<std::string, std::unordered_map<int, std::vector<std::string>>> &validScheduleMap){


		for (int i = request.m_start; i <= request.m_end; i++){

			if (validScheduleMap.find(request.m_location)->second.find(i) != validScheduleMap.find(request.m_location)->second.end()){
				validScheduleMap.find(request.m_location)->second.find(i)->second.push_back(request.m_id);
			}
			else{
				std::vector<std::string> contentIdContainer{ request.m_id };
				validScheduleMap.find(request.m_location)->second.insert(std::make_pair(i, contentIdContainer));
			}

		}
	}

};




struct Range{
	std::unordered_set < std::string > contentIDs;
	std::string location; 
	int start;
	int end;

	void reset(){
		contentIDs.clear();
	}
};


class Optimization{

public:

	static const int numberOfLocations = 6;

	static int findLocationSlot(std::string locationID){
		if (locationID == "center-top"){
			return 0;
		}
		else if (locationID == "right-top"){
			return 1;
		}
		else if (locationID == "center-middle"){
			return 2;
		}
		else if (locationID == "center-bottom"){
			return 3;
		}
		else if (locationID == "right-middle"){
			return 4;
		}
		else if (locationID == "right-bottom"){
			return 5;
		}
		else{
			return -1;
		}
	}

	static std::string findLocationID(int locationID){
		switch (locationID){
		case 0:
			return "center-top";
		case 1:
			return "right-top";
		case 2:
			return "center-middle";
		case 3:
			return "center-bottom";
		case 4:
			return "right-middle";
		case 5:
			return "right-bottom";
		default:
			return "unknown";
		}
	}


	static void optimization(std::list<Request> &optimizationList, std::list<Request> &requestList, std::unordered_map<std::string, int> &contentScoreMap, std::unordered_map<std::string, double> &locationValueMap, std::vector<std::string> &acceptedOptimization, std::vector<std::string> &rejectedOptization){

		
		std::vector<std::unordered_map<int, std::vector<std::string>>> requestMap;
		requestMap.resize(numberOfLocations);
		std::vector<int> lastTimePerLocation; 
		lastTimePerLocation.resize(numberOfLocations);

		for (auto currentRequest : requestList){
			insertIntoRequestMap(currentRequest, requestMap, lastTimePerLocation);
		}

		std::unordered_map<int, std::vector<Range>> optimizationChecker;
		createOptimizationChecker(requestMap, optimizationChecker, lastTimePerLocation);
		

	}

	static void insertIntoRequestMap(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &requestMap, std::vector<int> &lastTimePerLocation){

		int location = findLocationSlot(request.m_location);
		for (int i = request.m_start; i <= request.m_end; i++){

			auto currentTimeSlot = requestMap[location].find(i);
			if (currentTimeSlot == requestMap[location].end()){
				std::vector < std::string> contentIDs{ request.m_id };
				requestMap[location].insert(std::make_pair(i, contentIDs));
			}
			else{
				currentTimeSlot->second.push_back(request.m_id);
			}

		}

		if (lastTimePerLocation[location] < request.m_end){
			lastTimePerLocation[location] = request.m_end;
		}

	}

	static void createOptimizationChecker(std::vector<std::unordered_map<int, std::vector<std::string>>> &requestMap, std::unordered_map<int, std::vector<Range>> &optimizationChecker, std::vector<int> &lastTimePerLocation){

		int j = 1;
		for (int i = 0; i != numberOfLocations; i++){
			int duration = 0; 
			Range range;
			range.location = findLocationID(i); 
			for (; j <= lastTimePerLocation[i]; j++){
				
				auto currentTimeSlot = requestMap[i].find(j);
				if (currentTimeSlot == requestMap[i].end()){
					if (duration == 0){
						range.start = j;
					}
					duration++;
					continue;
				}

				if (currentTimeSlot->second.size() < 3){
					
					if (duration == 0){
						range.start = j;
					}
					range.contentIDs.insert(currentTimeSlot->second.begin(), currentTimeSlot->second.end());
					duration++;
				}
				else{
					
					if (duration == 0){
						continue;
					}

					range.end = j - 1;
					if (optimizationChecker.find(duration) != optimizationChecker.end()){
						optimizationChecker.find(duration)->second.push_back(range);
					}
					else{
						std::vector<Range> rangeVec{ range };
						optimizationChecker[duration] = rangeVec; 
					}
					duration = 0; 
					range.reset();
					
				}

			}
			if (duration != 0){
				range.end = j-1;
				if (optimizationChecker.find(duration) != optimizationChecker.end()){
					optimizationChecker.find(duration)->second.push_back(range);
				}
				else{
					std::vector<Range> rangeVec{ range };
					optimizationChecker[duration] = rangeVec;
				}
			}
		}

	}

};



struct Range{
	std::unordered_set < std::string > contentIDs;
	std::string location;
	int start;
	int end;

	void reset(){
		contentIDs.clear();
	}
};


class Optimization{

public:

	static const int numberOfLocations = 6;

	static int findLocationSlot(std::string locationID){
		if (locationID == "center-top"){
			return 0;
		}
		else if (locationID == "right-top"){
			return 1;
		}
		else if (locationID == "center-middle"){
			return 2;
		}
		else if (locationID == "center-bottom"){
			return 3;
		}
		else if (locationID == "right-middle"){
			return 4;
		}
		else if (locationID == "right-bottom"){
			return 5;
		}
		else{
			return -1;
		}
	}

	static std::string findLocationID(int locationID){
		switch (locationID){
		case 0:
			return "center-top";
		case 1:
			return "right-top";
		case 2:
			return "center-middle";
		case 3:
			return "center-bottom";
		case 4:
			return "right-middle";
		case 5:
			return "right-bottom";
		default:
			return "unknown";
		}
	}


	static void optimization(std::list<Request> &optimizationList, std::list<Request> &requestList, std::unordered_map<std::string, int> &contentScoreMap, std::unordered_map<std::string, double> &locationValueMap, std::vector<std::string> &acceptedOptimization, std::vector<std::string> &rejectedOptization){


		std::vector<std::unordered_map<int, std::vector<std::string>>> requestMap;
		requestMap.resize(numberOfLocations);
		std::vector<int> lastTimePerLocation;
		lastTimePerLocation.resize(numberOfLocations);

		for (auto currentRequest : requestList){
			insertIntoRequestMap(currentRequest, requestMap, lastTimePerLocation);
		}

		std::unordered_map<int, std::vector<Range>> optimizationChecker;
		createOptimizationChecker(requestMap, optimizationChecker, lastTimePerLocation);


	}

	static void insertIntoRequestMap(Request request, std::vector<std::unordered_map<int, std::vector<std::string>>> &requestMap, std::vector<int> &lastTimePerLocation){

		int location = findLocationSlot(request.m_location);
		for (int i = request.m_start; i <= request.m_end; i++){

			auto currentTimeSlot = requestMap[location].find(i);
			if (currentTimeSlot == requestMap[location].end()){
				std::vector < std::string> contentIDs{ request.m_id };
				requestMap[location].insert(std::make_pair(i, contentIDs));
			}
			else{
				currentTimeSlot->second.push_back(request.m_id);
			}

		}

		if (lastTimePerLocation[location] < request.m_end){
			lastTimePerLocation[location] = request.m_end;
		}

	}

	static void createOptimizationChecker(std::vector<std::unordered_map<int, std::vector<std::string>>> &requestMap, std::unordered_map<int, std::vector<Range>> &optimizationChecker, std::vector<int> &lastTimePerLocation){

		int j = 1;
		for (int i = 0; i != numberOfLocations; i++){
			int duration = 0;
			Range range;
			range.location = findLocationID(i);
			for (; j <= lastTimePerLocation[i]; j++){

				auto currentTimeSlot = requestMap[i].find(j);
				if (currentTimeSlot == requestMap[i].end()){
					if (duration == 0){
						range.start = j;
					}
					duration++;
					continue;
				}

				if (currentTimeSlot->second.size() < 3){

					if (duration == 0){
						range.start = j;
					}
					range.contentIDs.insert(currentTimeSlot->second.begin(), currentTimeSlot->second.end());
					duration++;
				}
				else{

					if (duration == 0){
						continue;
					}

					range.end = j - 1;
					if (optimizationChecker.find(duration) != optimizationChecker.end()){
						optimizationChecker.find(duration)->second.push_back(range);
					}
					else{
						std::vector<Range> rangeVec{ range };
						optimizationChecker[duration] = rangeVec;
					}
					duration = 0;
					range.reset();

				}

			}
			if (duration != 0){
				range.end = j - 1;
				if (optimizationChecker.find(duration) != optimizationChecker.end()){
					optimizationChecker.find(duration)->second.push_back(range);
				}
				else{
					std::vector<Range> rangeVec{ range };
					optimizationChecker[duration] = rangeVec;
				}
			}
		}

	}

};
*/