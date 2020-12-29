/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Gregory Baumann
 * Version     : 1.0
 * Date        : 10/26/20
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);
/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
	long count = 0;
	for (int i = 0; i < length; i++){
		for(int j = i + 1; j < length; j++){
			if(array[i] > array[j]){
				++count;
			}
		}
	}
	return count;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
	int *scratch = new int[length];
	return mergesort(array,scratch,0,length-1);
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
	long count = 0;
	if(low < high){
		int mid = low + (high-low) / 2;
		count += mergesort(array,scratch,low,mid);
		count += mergesort(array,scratch,mid+1,high);
		int l = low;
		int h = mid + 1;
		for(int k = low; k <= high;k++){
			if(l <= mid && (h > high || array[l] <= array[h])){
				scratch[k] = array[l];
				++l;
			}else{
				count += mid - l + 1;
				scratch[k] = array[h];
				++h;
			}
		}
		for(int i = low; i <= high; i++){
			array[i] = scratch[i];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
	istringstream iss;
	string slow = "";
    if(argc == 1){
    	slow = "";
    }else if (argc > 2){
    	cerr << "Usage: ./inversioncounter [slow]" << endl;
    	return 0;
    }else{
    	iss.str(argv[1]);
    	if(!(iss >> slow) || ((slow != "slow") && (slow != ""))){
    		cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
    		return 0;
    	}
    }
	iss.clear();

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    int length = values.size();
    if(length == 0){
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 0;
    }
    if(slow == "slow"){
    	cout << "Number of inversions: " << count_inversions_slow(&values[0],length) << endl;
    }else{
    	cout << "Number of inversions: " << count_inversions_fast(&values[0],length) << endl;
    }
    return 0;
}
