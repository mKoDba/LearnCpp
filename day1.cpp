/****************************************************************************
 * day1.cpp
 *
 *  Created on: 29. ruj 2019.
 *      Author: Mario
 *
 *	Day 1 puzzle of Advent of Code 2018
 ***************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>

//using namespace std;


bool prepare(std::vector<long int>& freqs);
void part_one(std::vector<long int>& freqs, long int& result);
void part_two(std::vector<long int>& freqs, long int& result);

int main(void){

	long int resulting_frequency = 0;
	std::vector<long int> freqs;

	if(!prepare(freqs)){
		return EXIT_FAILURE;
	}

	part_one(freqs, resulting_frequency);

	part_two(freqs, resulting_frequency);

	return 0;
}


bool prepare(std::vector<long int>& freqs){
	std::ifstream inFile;
	long int freq;
	inFile.open("C:\\Users\\Mario\\Desktop\\aoc2018\\day1.txt");
	if(inFile.is_open()){
		while(inFile>>freq){
			freqs.push_back(freq);
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

void part_one(std::vector<long int>& freqs, long int& result){
	result = 0;
	for(auto const &x: freqs){
		result += x;
	}
	std::cout<<"Resulting frequency is: "<<result<<std::endl;
}


void part_two(std::vector<long int>& freqs, long int& result_freq){
	result_freq = 0;
	std::vector<long int> tmp;
	bool done = false;

	while(!done){
		for(auto const& x: freqs){
			result_freq += x;
			if(std::find(tmp.begin(), tmp.end(), result_freq) == tmp.end()){
				tmp.push_back(result_freq);
			}
			else{
				done = true;
				std::cout<<"Repeating frequency is: "<<result_freq<<std::endl;
				break;
			}

		}
	}

}
