/****************************************************************************
 * day6.cpp
 *
 *  Created on: 2. stu 2019.
 *      Author: Mario
 *
 ***************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <boost/algorithm/string.hpp>

//using namespace std;
#define FILE_LOCATION "C:\\Users\\Mario\\Desktop\\aoc2018\\day6.txt"

struct Coord {
	int x;
	int y;

	//defined as a class member function - only one argument needed
	bool operator< (const Coord& crd) const{
		return (x < crd.x || (x==crd.x && y<crd.y));
	}
	bool operator== (const Coord& crd) const{
		return (x == crd.x && y == crd.y);
	}
};

bool comp_fn(const std::pair<Coord, int>& lhs, const std::pair<Coord, int>& rhs){
	return lhs.second < rhs.second;
}

bool prepare(std::vector<Coord>& loc, int& max_x, int& max_y);
int dist(Coord A, Coord B);
int find_largest_area(std::vector<Coord>& loc, int& max_x, int& max_y);

int main(void){
    clock_t start = clock();

    std::vector<Coord> loc;
    int max_x = 0,max_y = 0;

	if(!prepare(loc, max_x, max_y)){
		return EXIT_FAILURE;
	}

	int area = find_largest_area(loc, max_x, max_y);
	//std::cout<<"try abs:"<<dist(Coord{9,9}, Coord{8,9})<<std::endl;

    std::cout<<"\nduration: "<<float( clock () - start ) * 1000.0 /  CLOCKS_PER_SEC <<" ms"<<std::endl;
    std::cout<<"Part 1: size of the largest (finite) area: "<<area<<std::endl;
	return 0;
}

bool prepare(std::vector<Coord>& loc, int& max_x, int& max_y){
	std::ifstream inFile;
	std::vector<std::string> tokens;
	std::string input;
	char ch;

	inFile.open(FILE_LOCATION);
	if(inFile.is_open()){
		while(std::getline(inFile, input)){
			std::stringstream ss(input);
			Coord c;
			ss>>c.x>>ch>>c.y;
			if(c.x > max_x) {
				max_x = c.x;
			}
			if(c.y > max_y) {
				max_y = c.y;
			}
			loc.push_back(c);
		}
	}
	else{
		std::cout<<"Error while opening input file!"<<std::endl;
		return false;
	}
	return true;
}

int dist(Coord A, Coord B){
	return (std::abs(A.x-B.x)+std::abs(A.y-B.y));
}


int find_largest_area(std::vector<Coord>& loc, int& max_x, int& max_y){
	std::map<Coord, int> area;
	std::vector<Coord> edge;
	Coord None = {-1,-1};

	for(int i=0; i<=max_x; ++i){
		for(int j=0; j<=max_y; ++j){
			Coord C = {i,j};
			Coord P_closest = {-1,-1};
			int min = 10000;

			for(Coord P: loc){
				int m_dist = dist(C,P);
				//std::cout<<"("<<P.x<<", "<<P.y<<")"<<"\n";
				if(m_dist < min){
					min = m_dist;
					P_closest = P;
				}
				else if(m_dist == min){
					//min = -1;
					P_closest = None;
				}
			}

			if(i==0 || i==max_x || j==0 || j==max_y){
				if(std::find(edge.begin(), edge.end(), P_closest) == edge.end()){
					edge.push_back(P_closest);
				}
			}
			area[P_closest]++;
		}
	}
	/* remove coordinates tied with others and points
	 * that have edge coordinates since they extend
	 * to infinity */
	for(auto P: edge){
		//std::cout<<P.x<<" "<<P.y<<std::endl;
		area.erase(P);
	}

	for(auto it = area.cbegin(); it != area.cend(); ++it){
		std::cout<<"("<<it->first.x<<", "<<it->first.y<<") "<<it->second<<std::endl;
	}
	std::cout<<"-------"<<std::endl;
	int res = std::max_element(area.begin(), area.end(), comp_fn)->second;

	return res;
}
