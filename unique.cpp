/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Gregory Baumann
 * Date        : 9/24/2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	for(auto &ss: s){
		if((ss & ~32) == ss || isdigit(ss)){
			return false;
		}
	}
	return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned vector = 0;
	for(auto &ss: s){
		if((vector & (1 << (ss - 'a'))) != 0){
			return false;
		}
		vector = vector | (1 << (ss - 'a'));
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if (argc == 1 || argc >= 3){
		cout << "Usage: ./unique <string>" << endl;
	} else if(is_all_lowercase(argv[1]) == false){
		cout << "Error: String must contain only lowercase letters." << endl;
	} else if(all_unique_letters(argv[1])) {
		cout << "All letters are unique." << endl;
	}else {
		cout << "Duplicate letters found." << endl;
	}
	return 1;
}
