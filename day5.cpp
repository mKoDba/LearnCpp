/****************************************************************************
 * day5.cpp
 *
 *  Created on: 1. stu 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <cctype>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2018\\day5.txt"

bool prepare(std::string& input);
int part_one(std::string input);
int part_two(std::string input, int res);

int main(void){
    clock_t start = clock();

	std::string input;

	if(!prepare(input)){
		return EXIT_FAILURE;
	}
	int p1 = part_one(input);

    std::cout << "\nduration: " << float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;
    std::cout<<"Part 1: Units remaining: "<<p1<<std::endl;
    std::cout<<"Part 2: Shortest polymer: "<<part_two(input, p1)<<std::endl;
	return 0;
}


bool prepare(std::string& input){
	std::ifstream inFile;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		std::getline(inFile, input);
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

int part_one(std::string input){
	std::vector<char> poly;
	for(std::string::iterator it = input.begin(); it != input.end(); ++it){
		if(poly.size() == 0){
			poly.push_back(*it);
		}
		else{
			if((poly.back() == *it+32) || (poly.back() == *it-32)){
				poly.pop_back();
			}
			else{
				poly.push_back(*it);
			}
		}
	}
	return poly.size();
}

int part_two(std::string input, int res){
	int min = res;

	for(auto i = 'A'; i<'Z'; ++i){
		std::string copy = input;
		/*erase-remove - with std::remove elements to be 'removed' are just
		 * put on the end of the array, function return iterator to the first
		 * tail ('removed') element, with erase method this elements can
		 * be deleted for good
		 */
		copy.erase(std::remove(copy.begin(), copy.end(), i), copy.end());
		copy.erase(std::remove(copy.begin(), copy.end(), i+32), copy.end());
		int tmp = part_one(copy);
		if(tmp < min){
			min = tmp;
		}
	}
	return min;
}
