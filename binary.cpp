#include<iostream>
#include <bitset>

using namespace std;

int main() {
	int num;
	cout << "Enter a decimal number:\n";
	cin >> num;
	std::string binary = std::bitset<8>(num).to_string(); 
	std::cout << "The number in binary is " + binary << "\n";

	unsigned long decimal = std::bitset<8>(binary).to_ulong();
	std::cout<< decimal <<" is the decimal conversion of the binary value \n";
	return 0;
}

