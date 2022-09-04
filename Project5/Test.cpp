#include "BigInt.h"
#include <iostream>

using namespace std;

int main() {

	BigInt value("-999");
	BigInt value2("1");

	value = value + value2;

	value = -123;
	value2 = 123;

	value = value + value2;

	value = 1;
	value2 = 0;

	value = value + value2;

	return 0;
}