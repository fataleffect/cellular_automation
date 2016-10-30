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
	cout << "\n";
	cout << "combining the ruleset with the parent generation...\n";
	cout << "\n";
	

	child[0] = 0;

	for (int a = 0; a < 30; a++) {
		if(parent[a] == 1) {
			cout << "█";
		}
		if(parent[a] == 0) {
			cout << "░";
		}
	}
	cout << "\n";

	for(int size = 0; size < 10; size++) {
		int x = 0;
		int y = 1;
		while(y < 29) {
			next[0] = parent[x];
			x++;
			next[1] = parent[x];
			x++;
			next[2] = parent[x];

			/*cout << "next array:\n";
			for (int a = 0; a < 3; a++) {
			    cout << next[a];
			}*/

			if(next[0] == 1 && next[1] == 1 && next[2] == 1) {
				child[y] = ruleset[0];
			}
			if(next[0] == 1 && next[1] == 1 && next[2] == 0) {
				child[y] = ruleset[1];
			}
			if(next[0] == 1 && next[1] == 0 && next[2] == 1) {
				child[y] = ruleset[2];
			}
			if(next[0] == 1 && next[1] == 0 && next[2] == 0) {
				child[y] = ruleset[3];
			}
			if(next[0] == 0 && next[1] == 1 && next[2] == 1) {
				child[y] = ruleset[4];
			}
			if(next[0] == 0 && next[1] == 1 && next[2] == 0) {
				child[y] = ruleset[5];
			}
			if(next[0] == 0 && next[1] == 0 && next[2] == 1) {
				child[y] = ruleset[6];
			}
			if(next[0] == 0 && next[1] == 0 && next[2] == 0) {
				child[y] = ruleset[7];
			}
			x--;
			y++;
		}
		
		for (int a = 0; a < 30; a++) {
			if(child[a] == 1) {
			cout << "█";
			}
			if(child[a] == 0) {
				cout << "░";
			}
		}
		cout << "\n";

		for (int a = 0; a < 30; a++) {
			parent[a] = child[a];
		}
	}

	return 0;
}

/*for (int b = 29; b >= 0; b--) {
	child[b] = parent[b];
}*/

/*for (int a = 0; a < 30; a++) {
				child[a] = 0;
			}*/