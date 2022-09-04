#include "BigInt.h"
#include <iostream>

using namespace std;

int main() {

	BigInt value("-99");
	BigInt value2("1");

	cout << (value != value2);

	return 0;
}