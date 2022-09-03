#include "BigInt.h"
#include <string.h>

#define fromChar(a) (a-'0')
#define toChar(a) (a+'0')

constexpr const int BUFFER_STANDART_SIZE = 256;

BigInt::BigInt() {
	BigInt::value = new std::string("0");
};

BigInt::BigInt(int num) {
	char* buff = new char[BUFFER_STANDART_SIZE];
	snprintf(buff, BUFFER_STANDART_SIZE, "%d", num);
	BigInt::value = new std::string();
	delete[] buff;
}

BigInt::BigInt(std::string num) {
	for (auto elem : num) {
		if (elem < '0' || elem > '9') {
			throw std::invalid_argument("NAN: " + elem);
		}	
	}
	BigInt::value = new std::string(num);
}

BigInt::BigInt(const BigInt& num) {
	BigInt::value = new std::string(num.get_value());
}

BigInt::~BigInt() {
	clear_value();
}

BigInt& BigInt::operator=(const BigInt& new_value) { //TODO: rework copy algorith
	std::string str_buff(new_value.get_value());
	this->clear_value();
	this->value = new std::string(str_buff); 
	return *this;
}

BigInt operator+(const BigInt& first, const BigInt& second) {
	std::string fst_val;
	std::string snd_val;

	if (first.get_value().length() > second.get_value().length()) {
		fst_val = first.get_value();
		snd_val = second.get_value();
	}
	else {
		snd_val = first.get_value();
		fst_val = second.get_value();
	}

	std::reverse(fst_val.begin(), fst_val.end());
	std::reverse(snd_val.begin(), snd_val.end());

	std::string result(fst_val.length() + 1, 0);

	for (size_t fst_i = 0, snd_i = 0; snd_i < result.length(); fst_i++, snd_i++) { //TODO rework transfer char -> int | int -> char
		if (snd_i < snd_val.length()) {
			result[fst_i] += fromChar(snd_val[snd_i]);
		}
		if (fst_i < fst_val.length()) {
			result[fst_i] += fromChar(fst_val[fst_i]);
		}
		result[fst_i + 1] += result[fst_i] / 10;
		result[fst_i]     %= 10;
	}

	bool zero_remove_flag = true;
	int front_i = 0;
	int result_back_end = 0;
	for (int back_i = result.length() - 1; back_i >= result_back_end; back_i--) { //TODO: REWORK ZERO POP (ONLY ONE ZERO CAN APPEAR)
		if (zero_remove_flag && result[back_i] != 0) {
			zero_remove_flag = false;
			result_back_end = (back_i/2 + (back_i%2));
		}
		if (zero_remove_flag) {
			result.pop_back();
		}
		else {
			char cache = result[back_i] + '0';
			result[back_i] = result[front_i] + '0';
			result[front_i] = cache;
			front_i++;
		}
	}

	return BigInt(result);
}

std::string BigInt::get_value() const {
	if (value != NULL) {
		return *(new std::string(*value));
	}
	else {
		return "0";
	}
}

void BigInt::clear_value() {
	delete value;
}


