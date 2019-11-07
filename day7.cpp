/****************************************************************************
 * day7.cpp
 *
 *  Created on: 5. stu 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2018\\day7.txt"

bool prepare(std::vector<std::pair<char,char>>& steps){
	std::ifstream inFile;
	std::string input, buf;
	char stepOne, stepTwo;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		while(std::getline(inFile, input)){
			std::stringstream ss(input);
			ss>>buf>>stepOne>>buf>>buf>>buf>>buf>>buf>>stepTwo;
			steps.push_back(std::make_pair(stepOne, stepTwo));
			}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

const char get_min(std::set<char>& letter){
	return *letter.begin();
}

void check_possible_next_steps(std::set<char>& possible, std::vector<char>& result, std::vector<std::pair<char,char>>& steps){
	std::vector<char> maybe;

	for(auto r: result){
		for(auto p: steps){
			if(p.first == r){
				maybe.push_back(p.second);
			}
		}
	}

	/* check for each possible next step if the given requirements are satisfied */
	for(auto m: maybe){
		bool pass = true;
		for(auto p: steps){
			if(p.second == m && std::find(result.begin(), result.end(), p.first) == result.end()){
				pass = false;
				break;
			}
		}
		if(pass && (std::find(result.begin(), result.end(), m) == result.end())) {
			possible.insert(m);
		}
	}
}

void correct_order(std::vector<std::pair<char,char>>& steps){
	std::set<char> all_letters, possible;
	std::vector<char> first, second, result;

	for(auto p: steps){
		first.push_back(p.first);
		second.push_back(p.second);
	}

	/* find all letters that are contained in instructions and find possible
	 * starting points (letters) */
	for(char ch = 'A'; ch <= 'Z'; ++ch){
		if(std::find(second.begin(), second.end(), ch) != second.end() || std::find(first.begin(), first.end(), ch) != first.end()){
			all_letters.insert(ch);
			if(std::find(second.begin(), second.end(), ch) == second.end() && std::find(first.begin(), first.end(), ch) != first.end()){
				possible.insert(ch);
			}
		}
	}

	while(!all_letters.empty()){
		check_possible_next_steps(possible, result, steps);
		const char ch = get_min(possible);
		result.push_back(ch);
		possible.erase(ch);
		all_letters.erase(ch);
	}

	std::cout<<"Order in which instruction steps should be completed: "<<std::endl;
	for(auto it = result.begin(); it != result.end(); ++it){
		std::cout<<*it;
	}
}





int main(void){

	std::vector<std::pair<char,char>> steps;

	if(!prepare(steps)){
		return EXIT_FAILURE;
	}

	correct_order(steps);


	return 0;
}
