using namespace std;
#include <string>
#include <iostream>

using namespace std;

const string litterSizeMessage = "Define the size of one litter: ";
const string monthMessage = "How long in months: ";

static int NextGen( int childCount, int generation,int f_1 = 1, int f_2 = 1) {

	int fcurrent = f_1 + (f_2 * childCount);
	f_2 = f_1;
	if(generation>1)
	{
		NextGen(childCount, generation - 1,fcurrent, f_2);
	}
	else
		return fcurrent;
}
static class FibonacciRabbits {

	static int size, months;

public:
	static void Init() {
		cout << monthMessage;
		cin >> months;
		cout << litterSizeMessage;
		cin >> size;

		// remove the first generation as f1=f2=1 couple
		months -= 2;
		std::cout << NextGen(size, months);
	}
};
