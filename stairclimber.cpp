/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Gregory Baumann
 * Date        : 10/1/20
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > set_first_num(vector< vector<int> > &vector, int num){
	for (auto &vectors: vector){
		vectors.insert(vectors.begin(),num);
	}
	return vector;
}
vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector< vector<int> > num_stairs_v;
	if(num_stairs == 0){
		return {{}};
	} else if(num_stairs == 1){
		return {{1}};
	} else if (num_stairs == 2){
		return {{1,1},{2}};
	} else if (num_stairs >= 3){
		vector< vector<int> > v1 = get_ways(num_stairs - 1);
		vector< vector<int> > v2 = get_ways(num_stairs - 2);
		vector< vector<int> > v3 = get_ways(num_stairs - 3);
		v1 = set_first_num(v1,1);
		v2 = set_first_num(v2,2);
		v3 = set_first_num(v3,3);
		v1.insert( v1.end(), v2.begin(), v2.end() );
		v1.insert( v1.end(), v3.begin(), v3.end() );
		return v1;
	}
	return {{}};
}



void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	int steps,ns,digits,num_of_ways,num;
	num_of_ways = ways.size();
	num = ways.size();
	steps = ways[0].size();
	digits = 0;
	while(num != 0){
		digits += 1;
		num = num / 10;
	}
	int n = 1;
	if(num_of_ways == 1){
		cout << num_of_ways << " way to climb " << steps << " stair." << endl;
	}else {
		cout << num_of_ways << " ways to climb " << steps << " stairs." << endl;
	}

	for(auto &wayss: ways){
		cout << setw(digits) << n << ". [" << wayss[0];
		ns = wayss.size();
		for(int i = 1; i < ns ; i++){
			  cout<< ", " << wayss[i];
		}
		cout << "]" << endl;
		n += 1;
	}
}

int num_of_digits(int num){
	int digits = 0;
	while(num != 0){
		digits += 1;
		num = num / 10;
	}
	return digits;
}

int main(int argc, char * const argv[]) {
	int n;
	istringstream iss;
	if (argc >= 3 || argc == 1){
		cout << "Usage: ./stairclimber <number of stairs>" << endl;
	}else{
		iss.str(argv[1]);
		if (!(iss >> n) || n <= 0){
			cout << "Error: Number of stairs must be a positive integer." << endl;
		} else {
			display_ways(get_ways(n));
		}
	}

}
