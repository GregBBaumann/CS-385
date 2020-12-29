//============================================================================
// Name        : sqrt.cpp
// Author      : Gregory Baumann
// Honor Pledge: I pledge my honor I have abided by the Stevens Honor System.
//============================================================================
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon){
	if (num < 0){
		return numeric_limits<double>::quiet_NaN();
	}else if(num == 0 || num == 1){
		return num;
	}
	double next_guess = num;
	double last_guess = num;
	double temp = num;
	bool endloop = false;
	while (endloop == false){
		temp = next_guess;
		next_guess = (last_guess + num/last_guess)/2;
		if (abs(last_guess-next_guess) <= epsilon) {
			endloop = true;
		}
		last_guess = temp;
	}
	return next_guess;
}

int main(int argc, char* const argv[]) {
	double n, e;
	istringstream iss;
	if (argc < 2 || argc > 3){
		cout << "Usage: ./sqrt <value> [epsilon]" << endl;
		return 1;
	}
	if (argc != 3){
		e = 0.0000001;
	}else{
		iss.str(argv[2]);
		if ( !(iss >> e) ){
			cout << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
	}
	if (e <= 0){
		cout << "Error: Epsilon argument must be a positive double." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[1]);
	if ( !(iss >> n) ){
		cout << "Error: Value argument must be a double." << endl;
		return 1;
	}

	cout << fixed << setprecision(8) << sqrt(n,e) << endl;
	return 0;
}
