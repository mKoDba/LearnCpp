/*
 * day3.cpp
 *
 *  Created on: 22. lis 2019.
 *      Author: ekdbmrx
 */


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2018\\day3.txt"

bool prepare(std::vector<std::string>& claims);

int main(void){

	int area_claimed = 0;

	std::vector<std::string> input;
	std::cout<<"starting program..."<<std::endl;
	if(!prepare(input)){
		return EXIT_FAILURE;
	}

    std::map<std::pair<int,int>,int> dots;

    for (auto line : input) {
    	std::vector<std::string> tokens;
    	boost::algorithm::split(tokens, line, boost::algorithm::is_any_of("# @,:x"));
    	int start_x = std::stoi(tokens[4]);
    	int start_y = std::stoi(tokens[5]);
    	int width = std::stoi(tokens[7]);
    	int height = std::stoi(tokens[8]);
        for (int x = start_x; x < start_x+width; x++) {
            for (int y = start_y; y < start_y+height; y++) {
            	++dots[std::make_pair(x,y)];
            	if(dots[{x,y}] == 2){
            		area_claimed++;
            	}
            }
        }
    }
    int unique = 0;
    for (auto line : input) {
    	bool overlap = false;
    	std::vector<std::string> tokens;
    	boost::algorithm::split(tokens, line, boost::algorithm::is_any_of("# @,:x"));
    	int claim_no = std::stoi(tokens[1]);
    	int start_x = std::stoi(tokens[4]);
    	int start_y = std::stoi(tokens[5]);
    	int width = std::stoi(tokens[7]);
    	int height = std::stoi(tokens[8]);
        for (int x = start_x; x < start_x+width; x++) {
            for (int y = start_y; y < start_y+height; y++) {
            	if(dots[{x,y}] > 1){
            		overlap = true;
            	}
            }
        }
        if(!overlap){
        	unique = claim_no;
        }
    }
    std::cout<<"Part 1: Overlapping area: "<<area_claimed<<std::endl;
    std::cout<<"Part 2: Unique claim ID: "<<unique<<std::endl;
	return 0;
}

//split by new line, put each line in vector
bool prepare(std::vector<std::string>& claims){
	std::ifstream inFile;
	std::string claim;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		while(std::getline(inFile,claim)){
			claims.push_back(claim);
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}
