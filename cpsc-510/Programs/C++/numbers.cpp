#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv) {
	int *input;
	int numvalues;
	int average;
	int sum = 0;

	cout << "Array Size?" << endl;
	cin >> numvalues;
	input = new int[numvalues];
	for(int x=0; x<numvalues; x++) {
		cin >> input[x];
		sum += input[x];
	}
	
	/* find average */
	average = sum/numvalues;
	cout << "Average: " << average << endl;

	/* find above average */
	int above = 0;
	for(int x=0;x<numvalues;x++) {
		if(input[x] > average) {
			above++;
		}
	}
	cout << "There are " << above << " numbers above average." << endl;
	exit(0);
}
