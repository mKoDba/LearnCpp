/****************************************************************************
 * day2.cpp
 *
 *  Created on: 3. lis 2019.
 *      Author: Mario
 *
 ***************************************************************************/


#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

//using namespace std;


bool prepare(std::vector<std::string>& ids);
void checksum_ids(std::vector<std::string>& ids);


int main(void){

	std::vector<std::string> ids;

	if(!prepare(ids)){
		return EXIT_FAILURE;
	}

	checksum_ids(ids);

	return 0;
}


bool prepare(std::vector<std::string>& ids){
	std::ifstream inFile;
	std::string id;

	inFile.open("C:\\Users\\Mario\\Desktop\\aoc2018\\day2.txt");
	if(inFile.is_open()){
		while(inFile>>id){
			ids.push_back(id);
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

void checksum_ids(std::vector<std::string>& ids){
	std::map<char, int> duplicates;
	int two_letters = 0, three_letters = 0;
	bool flag_two = false, flag_three = false;


	for(auto const& box_id: ids){
		for(auto c: box_id){
			++duplicates[c];
		}
		for(auto const& dup: duplicates){
			if(dup.second == 2 && !flag_two){
				two_letters++;
				flag_two = true;
			}
			if(dup.second == 3 && !flag_three){
				three_letters++;
				flag_three = true;
			}
		}
		flag_two = false;
		flag_three = false;
		duplicates.clear();
	}
	double res = three_letters*two_letters;

	std::cout<<"Resulting checksum is: "<<res<<std::endl;

}

void find_correct_box_ids(std::vector<std::string>& ids){
	std::map<char, int> m;
	std::vector<std::map<char, int>> letters;

	for(auto const& box_id : ids){
		for(auto const& c : box_id){
			auto i = &c - &box_id[0]; 	//current index
			m[c] = i;
			letters.push_back(m);				// do {char, index} map for each box_id
		}
	}
}

