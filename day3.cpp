/*
 * day3.cpp
 *
 *  Created on: 22. lis 2019.
 *      Author: ekdbmrx
 */


#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\ekdbmrx\\Desktop\\aoc2018\\day3.txt"

bool prepare(std::vector<std::string>& claims);
void overlapping_fabric_inches(std::vector<std::string>& claims);
void get_starting_coords(std::string& claim, int& x, int& y);
void get_width_height(std::string& claim, int& w, int& h);


int main(void){
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::string> claims;

	if(!prepare(claims)){
		return EXIT_FAILURE;
	}

	overlapping_fabric_inches(claims);


	auto end = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
	std::cout<<"Program execution time: "<<time.count()<<" ms"<<std::endl;

	return 0;
}


bool prepare(std::vector<std::string>& claims){
	std::ifstream inFile;
	std::string claim;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		while(inFile>>claim){
			claims.push_back(claim);
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

void overlapping_fabric_inches(std::vector<std::string>& claims){
	std::map<int, int> pairs;
	unsigned overlaps = 0;

	// make a map with {x,y} pairs that behave like coordinates made in claim
	for(std::string& claim: claims){
		int start_x,start_y,w,h = 0;
		get_starting_coords(claim,start_x,start_y);
		get_width_height(claim,w,h);
		for(auto y = start_y; y != start_y+h-1; y++){
			for(auto x = start_x; x != start_x+w-1; x++){
				auto ret = pairs.insert(std::pair<int, int>(x,y));
				if(ret.second == false){
					overlaps++;
				}
			}
		}
	}
	std::cout<<"Number of overlaps: "<<overlaps<<std::endl;
}

void get_starting_coords(std::string& claim, int& x, int& y){
	int first = claim.find("@ ");
	int second = claim.find(",");
	x = std::atoi(claim.substr(first+2, second-first-2).c_str());

	first = claim.find(",");
	second = claim.find(":");
	y = std::atoi(claim.substr(first+1, second-first-1).c_str());
}

void get_width_height(std::string& claim, int& w, int& h){
	int first = claim.find(": ");
	int second = claim.find("x");
	w = std::atoi(claim.substr(first+2, second-first-2).c_str());

	first = claim.find("x");
	second = claim.find("\n");
	h = std::atoi(claim.substr(first+1, second-first-1).c_str());
}
