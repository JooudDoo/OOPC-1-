#include "BigInt.h"
#include <utility>

BigBin::BigBin(BigInt& num) {
	BigInt mod_res, dnum = num;
	while (dnum > BigInt{ 0 }) {
		dnum = div_two_nums(dnum, 2, false, false, &mod_res);
		this->insert(mod_res);
	}
	std::reverse(this->value.begin(), this->value.end());
}

void BigBin::insert(const BigInt& val) {
	this->insert(val.data());
}
