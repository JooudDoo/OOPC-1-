#include "BigInt.h"
#include <iostream>

using namespace std;

int main() {

	BigInt value("999");
	BigInt value2("1");

	value = value + value2;

	return 0;
}