#include "BigInt.h"

#define fromChar(a) (a-'0')
#define toChar(a) (a+'0')

constexpr const int BUFFER_STANDART_SIZE = 256;

BigInt::BigInt() {
	BigInt::value = new std::string("0");
};

BigInt::BigInt(int num) {
	char* buff = new char[BUFFER_STANDART_SIZE];
	snprintf(buff, BUFFER_STANDART_SIZE, "%d", num);
	BigInt::value = new std::string(buff);
	delete[] buff;
}

BigInt::BigInt(std::string num) {
	for (auto elem : num) {
		if ((elem < '0' || elem > '9') && elem != '-') {
			throw std::invalid_argument("NAN: " + elem);
		}
	}
	BigInt::value = new std::string(num);
}

BigInt::BigInt(const BigInt& num) {
	BigInt::value = new std::string(num.data());
}

BigInt::~BigInt() {
	clear_value();
}

BigInt& BigInt::operator=(const BigInt& new_value) { //TODO: rework copy algorith
	std::string str_buff(new_value.data());
	this->clear_value();
	this->value = new std::string(str_buff); 
	return *this;
}

BigInt operator+(const BigInt& first, const BigInt& second) {
	std::string fst_val;
	std::string snd_val;

	if (first.data().length() > second.data().length()) {
		fst_val = first.data();
		snd_val = second.data();
	}
	else {
		snd_val = first.data();
		fst_val = second.data();
	}

	std::reverse(fst_val.begin(), fst_val.end()); //TODO: REMOVE RESERVE (TRY TO USE PURE DATA)
	std::reverse(snd_val.begin(), snd_val.end());

	std::string result(fst_val.length() + 1, 0);

	for (size_t fst_i = 0, snd_i = 0; snd_i < result.length(); fst_i++, snd_i++) {
		if (snd_i < snd_val.length()) {
			result[fst_i] += fromChar(snd_val[snd_i]);
		}
		if (fst_i < fst_val.length()) {
			result[fst_i] += fromChar(fst_val[fst_i]);
		}
		result[fst_i + 1] += result[fst_i] / 10;
		result[fst_i]     %= 10;
	}

	if (*result.rbegin() == 0) {
		result.pop_back();
	}

	for (int front_i = 0, back_i = result.length() - 1; front_i < result.length()/2 + result.length()%2; front_i++, back_i--) {
		char cache = toChar(result[back_i]);
		result[back_i] = toChar(result[front_i]);
		result[front_i] = cache;
	}

	return BigInt(result);
}

std::string BigInt::data() const {
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


