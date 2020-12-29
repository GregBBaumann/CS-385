/*******************************************************************************
 * Name        : powergrid.cpp
 * Author      : Gregory Baumann
 * Date        : 12/16/20
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

vector< vector<int>> vertArr;
vector< vector<int>> solution_path;
string** streetName;
long** weight;
int num_Verticies;
long length;

void fallout_76(){
	for(int i = 0; i < num_Verticies; i++){
		delete[] streetName[i];
		delete[] weight[i];
	}
	delete weight;
	delete streetName;
	vertArr.clear();
	solution_path.clear();
}

bool been_to(int vec, vector<int> visited){
	for(int i = 0; i < (int)visited.size(); i++){
		if(vec == visited[i]){
			return true;
		}
	}
	return false;
}

bool cycle(vector <vector<int>> arr,int from, vector<int> visited){
	 int found = 0;
	 vector <vector<int>> temp;
	 vector<int> tmp;
	 vector<bool> next;
	 for(int i = 0; i < (int)arr.size(); i++){
		 if(from == arr[i][0]){
			 if(been_to(arr[i][1],visited)){
				 return true;
			 }else{
				 found++;
				 temp = arr;
				 temp.erase(temp.begin()+i);
				 tmp = visited;
				 tmp.push_back(from);
				 next.push_back(cycle(temp,arr[i][1],tmp));
			 }
		 }else if(from == arr[i][1]){
			 if(been_to(arr[i][0],visited)){
			 	return true;
			 }else{
				 found++;
				 temp = arr;
				 temp.erase(temp.begin()+i);
				 tmp = visited;
				 tmp.push_back(from);
				 next.push_back(cycle(temp,arr[i][0],tmp));
			 }
		 }
	 }
	 if(found == 0){
		 return false;
	 }
	 for(int i = 0; i < (int)next.size(); i++){
		 if(next[i] == true){
			 return true;
		 }
	 }
	 return false;
}

bool findSolution(vector<vector<int>> arr){
	vector<bool> vect_check;
	vector<vector<int>> tarr;
	bool iscycle;
	length = 0;
	int found = 0;
	for (int i = 0; i < num_Verticies; i++){
		vect_check.push_back(false);
	}
	while(found != num_Verticies - 1){
		if(arr.empty()){
			return false;
		}
		if(vect_check[arr[0][0]-1] == false || vect_check[arr[0][1]-1] == false){
			vect_check[arr[0][0]-1] = true;
			vect_check[arr[0][1]-1] = true;
			length = length + weight[arr[0][0]-1][arr[0][1]-1];
			solution_path.push_back(arr[0]);
			found++;
		}else{
			tarr = solution_path;
			tarr.push_back(arr[0]);
			iscycle = false;
			for(int i = 0; i < num_Verticies; i++){
				if(cycle(tarr,i+1,{})){
					iscycle = true;
				}
			}
			if(!iscycle){
				length = length + weight[arr[0][0]-1][arr[0][1]-1];
				solution_path.push_back(arr[0]);
				found++;
			}
			tarr.clear();
		}
		arr.erase(arr.begin());
	}
	return true;
}

vector< vector<int>> sortEdge(vector<vector<int>> arr){
	int min_pos;
	for (int i = 0; i < (int)arr.size(); i++){
		min_pos = i;
		for (int j = i; j < (int)arr.size(); j++){
			if(weight[arr[min_pos][0]-1][arr[min_pos][1]-1] > weight[arr[j][0]-1][arr[j][1]-1]){
				min_pos = j;
			}
		}
		swap(arr[i],arr[min_pos]);
	}
	return arr;
}


vector<vector<int>> sortStreet(vector<vector<int>> arr){
	int min_pos;
	for (int i = 0; i < (int)arr.size(); i++){
		min_pos = i;
		for (int j = i; j < (int)arr.size(); j++){
			if(streetName[arr[min_pos][0]-1][arr[min_pos][1]-1] > streetName[arr[j][0]-1][arr[j][1]-1]){
				min_pos = j;
			}
		}
		swap(arr[i],arr[min_pos]);
	}
	return arr;
}

void print_vector(vector<vector<int>> arr){
		cout << "Total wire length (meters): " << length << endl;
		for(int i = 0; i < (int)arr.size(); i++){
			cout << streetName[arr[i][0]-1][arr[i][1]-1] << " [" << weight[arr[i][0]-1][arr[i][1]-1] << "]" << endl;
		}
}

int main(int argc, char *argv[]) {
	int lineNum = 1;
	istringstream iss;
	if(argc != 2){
		cerr << "Usage: ./powergrid <input file>" << endl;
		fallout_76();
		return 0;
	}
	ifstream txtfile(argv[1]);
	string line;
	if(txtfile.fail()){
		cerr << "Error: Cannot open file '" << argv[1] <<  "'." << endl;
		fallout_76();
		return 0;
	}
	while (getline(txtfile, line)){
		if(lineNum == 1){
			iss.str(line);
			if(!(iss >> num_Verticies) || num_Verticies < 1 || num_Verticies > 1000){
				cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
				fallout_76();
				return 0;
			}
			if(num_Verticies == 1){
				cout << "No solution." << endl;
				fallout_76();
				return 0;
			}
			iss.clear();
			streetName = new string*[num_Verticies];
			weight = new long*[num_Verticies];
			for(int i = 0; i < num_Verticies; i++){
				streetName[i] = new string[num_Verticies];
				weight[i] = new long[num_Verticies];
			}
		}else{
			string word,stringIn,street,num;
			int vertto,vertfrom,edgeW;
			size_t found;
			vector<int> in;
			queue<string> in_queue;
			stringstream ss(line);
			while (ss >> word){
				stringIn = stringIn + " " + word;
			}
			found = stringIn.find(",");
			while(found!=string::npos){
				in_queue.push(stringIn.substr(0,found));
				stringIn = stringIn.substr(found+1);
				found = stringIn.find(",");
			}
			in_queue.push(stringIn);
			ss.clear();
			if(in_queue.size() != 4){
				cerr << "Error: Invalid edge data '" << line <<"' on line "<< lineNum << "."<< endl;
				fallout_76();
				return 0;
			}
			num = in_queue.front();
			in_queue.pop();
			ss.str(num);
			if(!(ss >> vertto) || vertto <= 0 || vertto > num_Verticies){
				cerr << "Error: Starting vertex '"<< num.substr(1) << "' on line " << lineNum << " is not among valid values 1-" << num_Verticies << "." << endl;
				fallout_76();
				return 0;
			}
			ss.clear();
			num = in_queue.front();
			in_queue.pop();
			ss.str(num);
			if(!(ss >> vertfrom) || vertfrom <= 0 || vertfrom > num_Verticies){
				cerr << "Error: Ending vertex '"<< num << "' on line " << lineNum << " is not among valid values 1-" << num_Verticies << "." << endl;
				fallout_76();
				return 0;
			}
			ss.clear();
			num = in_queue.front();
			in_queue.pop();
			ss.str(num);
			if(!(ss >> edgeW) || edgeW <= 0){
				cerr << "Error: Invalid edge weight '"<< num << "' on line " << lineNum << "." << endl;
				fallout_76();
				return 0;
			}
			ss.clear();
			street = in_queue.front();
			in_queue.pop();
			streetName[vertto-1][vertfrom-1] = street;
			weight[vertto-1][vertfrom-1] = edgeW;
			in.push_back(vertto);
			in.push_back(vertfrom);
			vertArr.push_back(in);
			in.clear();
		}
		lineNum++;
	}
	txtfile.close();
	if(!findSolution(sortEdge(vertArr))){
		cout << "No solution." << endl;
		fallout_76();
		return 0;
	}
	print_vector(sortStreet(solution_path));
	fallout_76();
}
