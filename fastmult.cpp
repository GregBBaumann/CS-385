/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Gregory Baumann
 * Date        : 10/20/20
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>

long long int stringtoint(const std::string& s){
	std::istringstream iss;
	long long int n;
	iss.str(s);
	iss >> n;
	iss.clear();
	return n;
}

std::string inttostring(const long long int n){
	std::ostringstream oss;
	std::string s;
	oss << n;
	s = oss.str();
	oss.clear();
	return s;
}

//int chartoint(const char& c){
//	return (int)c;
//}

//std::string add(const std::string& a, const std::string& b){
//	long long int n1, n2;
//	n1 = stringtoint(a);
//	n2 = stringtoint(b);
//	return inttostring(n1 + n2);
//}

std::string add(const std::string& a,const std::string& b){
	std::string ac,bc;
	ac = a;
	bc = b;
	int n = a.length() - b.length();
	int len;
	if (n > 0){
		std::string n1(n,'0');
		bc.insert(0,n1);
	}else if(n < 0){
		n = n*-1;
		std::string n2(n,'0');
		ac.insert(0,n2);
	}
	len = ac.length();
	bool rem = false;
	std::string ans;
	int num1, num2, num3;
	for(long int i = len - 1; i >= 0; i--){
		num1 = stringtoint(ac.substr(i,1));
		num2 = stringtoint(bc.substr(i,1));
		if(rem == true){
			num3 = num1 + num2 + 1;
		}else{
			num3 = num1 + num2;
		}
		ans = ans.insert(0,inttostring(num3 % 10));
		if(num3 >= 10){
			rem = true;
		}else{
			rem = false;
		}
	}
	if(rem == true){
		ans.insert(0,"1");
	}
	return ans;
}

std::string subtract(const std::string& a, const std::string& b){
	long long int n1, n2;
	n1 = stringtoint(a);
	n2 = stringtoint(b);
	return inttostring(n1 - n2);
}
std::string multiply(const std::string& a, const std::string& b){
	long long int n1, n2;
	n1 = stringtoint(a);
	n2 = stringtoint(b);
	return inttostring(n1 * n2);
}
std::string fastmulti(const std::string& a, const std::string& b){
	long int alen = a.length();
	long int blen = b.length();
	long int n;
	std::string aLeft,aRight,bLeft,bRight,c2,c1,c0;
	if(alen == 1 || blen == 1){
		return multiply(a,b);
	}else{
		if(alen > blen){
			n = alen;
		}else{
			n = blen;
		}
		aLeft = a.substr(0,alen/2);
		aRight = a.substr(alen/2);
		bLeft = b.substr(0,blen/2);
		bRight = b.substr(blen/2);
		c2 = fastmulti(aLeft,bLeft);
		c0 = fastmulti(aRight,bRight);
		c1 = subtract(subtract(fastmulti(add(aLeft,aRight),add(bLeft,bRight)),c2),c0);
		std::string n2(n,'0');
		n2.insert(0,c2);
		std::string n1((long int)n/2,'0');
		n1.insert(0,c1);
		return add(add(n2,n1),c0);
	}
}

int main(int argc, char *argv[]) {
	std::istringstream iss;
	std::string n1,n2;
	iss.str(argv[1]);
	if(!(iss >> n1)){
		std::cerr << "Input 1 not string of int" << std::endl;
		return 0;
	}
	iss.clear();
	iss.str(argv[2]);
	if(!(iss >> n2)){
		std::cerr << "Input 2 not string of int" << std::endl;
		return 0;
	}
	iss.clear();
	std::string nt1(1000,'1');
	std::string nt2(1000,'2');
	std::cout << "Fast multiply of " << n1 << " and " << n2 << " is :" << std::endl << fastmulti(n1,n2) << std::endl;
	return 0;
}

