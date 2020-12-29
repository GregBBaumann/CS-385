/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Gregory Baumann and Roma Razdan
 * Date        : 10/20/20
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void printJug(State Jug){
	if(Jug.a == -100){
		cout << "No solution." << endl;
	} else{
		vector<string> outString;
		string s;
		State* Jugptr = &Jug;
		while(Jugptr !=  nullptr){
			s = Jugptr->to_string();
			outString.push_back(s);
			Jugptr = Jugptr->parent;
		}
		while(!outString.empty()){
			cout << outString.back() << endl;
			outString.pop_back();
		}
	}
}

int bfs(int a,int b, int c ,int cA, int cB, int cC, int gA,int gB, int gC){
	State iState = {a,b,c,"Initial state. "};
	State *cState;
	State nextState = {0,0,0,""};
	ostringstream oss;
	vector<vector<State*>> arr;
	queue<State> *queues =  new queue<State>;
	queues->push(iState);
	for (int i = 0; i <= cA; i++){
		arr.push_back({NULL});
		for (int j = 0; j < cB; j++){
			arr[i].push_back(NULL);
		}
	}
	while (!queues->empty()){
		cState = new State(queues->front());
		queues->pop();
		int cSA = cState->a;
		int cSB = cState->b;
		int cSC = cState->c;
		if ((cSA == gA) && (cSB == gB) && (cSC == gC)){
			printJug(*cState);
			for(int i = 0; i <= cA; i++){
				for(int j = 0; j<= cB; j++){
					delete arr[i][j];
				}
			}
			delete queues;
			return 1;
		}
		if (arr[cSA][cSB] == NULL){
			arr[cSA][cSB] = cState;
			// C to A
			if(cSA != cA && cSC != 0){
				if((cSC - (cA - cSA)) >= 0){
					a = cA;
					b = cSB;
					c = cSC - (cA - cSA);
					if ((cA-cSA) > 1){
						oss << "Pour " << (cA-cSA) << " gallons from C to A. ";
					}else{
						oss << "Pour " << (cA-cSA) << " gallon from C to A. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = cSA + cSC;
					b = cSB;
					c = 0;
					if ((cSC) > 1){
						oss << "Pour " << cSC << " gallons from C to A. ";
					}else{
						oss << "Pour " << cSC << " gallon from C to A. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
			// B to A
			if(cSA != cA && cSB != 0){
				if((cSB - (cA - cSA)) >= 0){
					a = cA;
					b = cSB - (cA - cSA);
					c = cSC;
					if ((cA-cSA) > 1){
						oss << "Pour " << (cA-cSA) << " gallons from B to A. ";
					}else{
						oss << "Pour " << (cA-cSA) << " gallon from B to A. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = cSA + cSB;
					b = 0;
					c = cSC;
					if ((cSB) > 1){
						oss << "Pour " << cSB << " gallons from B to A. ";
					}else{
						oss << "Pour " << cSB << " gallon from B to A. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
			// C to B
			if(cSB != cB && cSC != 0){
				if((cSC - (cB - cSB)) >= 0){
					a = cSA;
					b = cB;
					c = cSC - (cB - cSB);
					if ((cB-cSB) > 1){
						oss << "Pour " << (cB-cSB) << " gallons from C to B. ";
					}else{
						oss << "Pour " << (cB-cSB) << " gallon from C to B. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = cSA;
					b = cSB + cSC;
					c = 0;
					if ((cSC) > 1){
						oss << "Pour " << cSC << " gallons from C to B. ";
					}else{
						oss << "Pour " << cSC << " gallon from C to B. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
			// A to B
			if(cSB != cB && cSA != 0){
				if((cSA - (cB - cSB)) >= 0){
					a = cSA - (cB - cSB);
					b = cB;
					c = cSC;
					if ((cB-cSB) > 1){
						oss << "Pour " << (cB-cSB) << " gallons from A to B. ";
					}else{
						oss << "Pour " << (cB-cSB) << " gallon from A to B. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = 0;
					b = cSB + cSA;
					c = cSC;
					if ((cSA) > 1){
						oss << "Pour " << cSA << " gallons from A to B. ";
					}else{
						oss << "Pour " << cSA << " gallon from A to B. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
			// B to C
			if(cSC != cC && cSB != 0){
				if((cSB - (cC - cSC)) >= 0){
					a = cSA;
					b = cSB - (cC - cSC);
					c = cC;
					if ((cC-cSC) > 1){
						oss << "Pour " << (cC-cSC) << " gallons from B to C. ";
					}else{
						oss << "Pour " << (cC-cSC) << " gallon from B to C. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = cSA;
					b = 0;
					c = cSC + cSB;
					if ((cSB) > 1){
						oss << "Pour " << cSB << " gallons from B to C. ";
					}else{
						oss << "Pour " << cSB << " gallon from B to C. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
			// A to C
			if(cSC != cC && cSA != 0){
				if((cSA - (cC - cSC)) >= 0){
					a = cSA - (cC - cSC);
					b = cSB;
					c = cC;
					if ((cC-cSC) > 1){
						oss << "Pour " << (cC-cSC) << " gallons from A to C. ";
					}else{
						oss << "Pour " << (cC-cSC) << " gallon from A to C. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}else{
					a = 0;
					b = cSB;
					c = cSC + cSA;
					if ((cSA) > 1){
						oss << "Pour " << cSA << " gallons from A to C. ";
					}else{
						oss << "Pour " << cSA << " gallon from A to C. ";
					}
					nextState = {a, b, c, oss.str()};
					nextState.parent = cState;
					queues->push(nextState);
					oss.str("");
				}
			}
		}else{
			delete cState;
		}
	}
	State failState = {-100,0,0,""};
	printJug(failState);
	for(int i = 0; i <= cA; i++){
		for(int j = 0; j<= cB; j++){
			delete arr[i][j];
		}
	}
	delete queues;
	return 1;
}





int main(int argc, char * const argv[]) {
	int cA, cB, cC, gA, gB, gC;
	istringstream iss;
	if(argc > 7 || argc < 7){
		cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
		return 1;
	}
	iss.str(argv[1]);
	if ( !(iss >> cA || cA < 0) ){
		cout << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[2]);
	if ( !(iss >> cB) || cB < 0){
		cout << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[3]);
	if ( !(iss >> cC) || cC <= 0){
		cout << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[4]);
	if ( !(iss >> gA) || gA < 0){
		cout << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[5]);
	if ( !(iss >> gB) || gB < 0){
		cout << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
		return 1;
	}
	iss.clear();
	iss.str(argv[6]);
	if ( !(iss >> gC) || gC < 0 ){
		cout << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
		return 1;
	}
	iss.clear();
	if (cA < gA){
		cout << "Error: Goal cannot exceed capacity of jug A." << endl;
		return 1;
	}
	if (cB < gB){
		cout << "Error: Goal cannot exceed capacity of jug B." << endl;
		return 1;
	}
	if (cC < gC){
		cout << "Error: Goal cannot exceed capacity of jug C." << endl;
		return 1;
	}
	if ((gA + gB + gC) != cC){
		cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
		return 1;
	}
	bfs(0,0,cC,cA,cB,cC,gA,gB,gC);
}
