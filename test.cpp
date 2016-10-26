#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int num;
	cout << "Enter a ruleset decimal number:\n";
	cin >> num;	
	string binary = std::bitset<8>(num).to_string();
	cout << "The ruleset in binary is " + binary << "\n";

	int ruleset[8];

	for (int i = 0; i < 8; i++)
	{
		ruleset[i] = binary[i] - '0';
		/*ruleset[i] = 5;*/
	}

	cout << "This is the ruleset array:\n";
	for (int i = 0; i < 8; i++) {
    	cout << ruleset[i];
	}
	cout << "\n";


	int parent[30];
	int child[30];
	int next[3];

	for(int i = 29; i >= 0; i--) {
		parent[i] = 0;
	}

	parent[15] = 1;

	cout << "This is the parent array:\n";
	for (int i = 29; i >= 0; i--) {
    	cout << parent[i];
	}
	cout << "\n";

	cout << "combining the ruleset with the parent generation...\n";
	cout << "\n";
	while(true) {
		int i = 0;
		next[0] = parent[i];
		i++;
		next[1] = parent[i];
		i++;
		next[2] = parent[i];

		if(next[0] == 1 && next[1] == 1 && next[2] == 1) {
			child[] = ruleset[];
		}
		if(next[0] == 1 && next[1] == 1 && next[2] == 0) {
			
		}
		if(next[0] == 1 && next[1] == 0 && next[2] == 1) {
			
		}
		if(next[0] == 1 && next[1] == 0 && next[2] == 0) {
			
		}
		if(next[0] == 0 && next[1] == 1 && next[2] == 1) {
			
		}
		if(next[0] == 0 && next[1] == 1 && next[2] == 0) {
			
		}
		if(next[0] == 0 && next[1] == 0 && next[2] == 0) {
			
		}
	}

	return 0;
}
