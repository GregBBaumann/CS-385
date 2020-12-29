/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Gregory Baumann
 * Date        : September 18, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit): is_prime_{new bool[limit + 1]}, limit_{limit} {
       sieve(limit);
    }

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes(vector<int> nums, int limit) const;

    vector<int> sieve(int limit);
private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes(vector<int> nums) const;

    static int num_digits(int num);
};

//PrimesSieve::PrimesSieve(int limit) :
//       is_prime_{new bool[limit + 1]}, limit_{limit} {
//    sieve(limit);
//   }

void PrimesSieve::display_primes(vector<int> nums, int limit) const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
	int primes = nums[0];
	nums[0] = 2; // extracted the number of primes from nums[0] and set nums[0] back to 2
	int highest;
	int j = nums.size();
    while (nums[j] == 0){
		j -= 1;
	}
	highest = nums[j];
	const int max_prime_width = num_digits(highest),
	primes_per_row = 80 / (max_prime_width + 1);
	const int row_total = (primes * (max_prime_width + 1) / 80) + 1;
    cout << "Number of primes found: " << primes << endl;
	cout << "Primes up to " << limit << ":" << endl;
	int row_count = 0;
	for (auto i = nums.begin() ; i != nums.end(); i++){
		if(*i == 0){

		}else if (*i == 2){
			if (row_total == 1){
				cout << setw(1) << *i;
			}else {
			    cout << setw(max_prime_width) << *i;
			}
		}else if(row_total  == 1){
			cout << setw(num_digits(*i)+1) << *i;
		}else{
		    row_count += 1;
		    if(row_count >= primes_per_row){
			    cout << endl;
			    row_count = 0;
			    cout << setw(max_prime_width) << *i;
		    }else{
		    	cout << setw(max_prime_width+1) << *i;
		    }
		}
	}


}


int PrimesSieve::count_num_primes(vector<int> nums) const {
    // TODO: write code to count the number of primes found
    return nums.size();
}

vector<int> PrimesSieve::sieve(int limit) {
	// TODO: write sieve algorithm
	std::vector<int> nums;
	for(int i = 2; i <= limit; i++ ){
		nums.push_back(i);
	}
	int size = limit-1;
	int j = 0;
	int primes = size;
    while (nums[j]*nums[j] <= limit){
    	int step = nums[j];
    	int pos = (nums[j]*nums[j]) - 2;
    	bool small = true;
    	while (small == true){
    		if (pos > size){
    			small = false;
    		} else {
    			if (nums[pos] == 0){
    				pos += step;
    			}else{
    			    nums[pos] = 0;
    			    primes -= 1;
    			    pos += step;
    			}
    		}
    	}
    	j += 1;
    	   while(nums[j] == 0){
    			j += 1;
    	   }
    	}
    nums[0] = primes; //in order to save the number of primes, I set it equal to the 0 position which will always be 2
    return nums;
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int digits = 0;
	while(num != 0){
		digits += 1;
		num = num / 10;
	}
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    cout << endl;
    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve Primes = PrimesSieve(limit);
    Primes.display_primes(Primes.sieve(limit),limit);
    return 0;
}
