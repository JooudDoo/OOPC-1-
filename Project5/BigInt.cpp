#include "BigInt.h"

#define fromChar(a) (a-'0')
#define toChar(a) (a+'0')

constexpr const int BUFFER_STANDART_SIZE = 256;

/*Ｃｏｎｓｔｒｕｃｔｏｒｓ*/

BigInt::BigInt() {
	BigInt::value = std::string("0");
};

BigInt::BigInt(int num) {
	char* buff = new char[BUFFER_STANDART_SIZE];
	snprintf(buff, BUFFER_STANDART_SIZE, "%d", num);
	BigInt::value = std::string(buff);
	delete[] buff;
}

BigInt::BigInt(std::string num) {
	for (std::string::iterator elem = num.begin(); elem != num.end(); elem++) {
		if ((*elem < '0' || *elem > '9') &&
			(*elem == '-' && elem != num.begin())) {
			throw std::invalid_argument("NAN: " + *elem);
		}
	}
	BigInt::value = std::string(num);
}

BigInt::BigInt(const BigInt& num) {
	BigInt::value = std::string(num.data());
}

/*Ｄｅｃｏｎｓｔｒｕｃｔｏｒｓ*/

BigInt::~BigInt() {
	//clear_value();
}

/*Ｔｒａｎｓｆｏｒｍｓ*/

BigInt::operator int() const {
	return atoi(this->data().c_str());
}

BigInt::operator std::string() const {
	std::string str = this->value;
	return str;
}

/*Ａｓｓｉｇｎｍｅｎｔ*/

BigInt& BigInt::operator=(const BigInt& new_value) { //TODO: rework copy algorith
	std::string str_buff(new_value.data());
	//this->clear_value();
	this->value = std::string(str_buff);
	return *this;
}

/*Ｏｐｅｒａｔｉｏｎｓ*/

BigInt& BigInt::operator++() {
	*this = *this + (BigInt)1;
	return *this;
}

const BigInt BigInt::operator++(int) const {
	return (*this) + (BigInt)1;
}

BigInt& BigInt::operator--() {
	*this = *this - (BigInt)1;
	return *this;
}

const BigInt BigInt::operator--(int) const {
	return (*this) - (BigInt)1;
}

BigInt& BigInt::operator+=(const BigInt& num) {
	*this = *this + num;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
	*this = *this - num;
	return *this;
}

BigInt abs(const BigInt& num) {
	if (num.data()[0] == '-') {
		BigInt newNum = BigInt(num.data().erase(0,1));
		return newNum;
	}
	return num;
}

BigInt BigInt::operator-() const {
	if (*this < (BigInt)0)
		return abs(*this);
	return this->data().insert(0, (std::string)"-");
}

BigInt operator+(const BigInt& first, const BigInt& second) {
	std::string fst_val;
	std::string snd_val;
	bool is_neg_res = false;

	if (first < (BigInt)0 && second < (BigInt)0) {
		is_neg_res = true;
	}
	else if (first < (BigInt)0) {
		return second - -first;
	}
	else if (second < (BigInt)0) {
		return first - -second;
	}

	if (first.data().length() > second.data().length()) {
		fst_val = first.data();
		snd_val = second.data();
	}
	else {
		snd_val = first.data();
		fst_val = second.data();
	}

	std::reverse(fst_val.begin(), fst_val.end()); //TODO: REMOVE REVERSE (TRY TO USE PURE DATA)
	std::reverse(snd_val.begin(), snd_val.end());

	std::string result(fst_val.length() + 1, 0);

	for (size_t i = 0; i < result.length(); i++) {
		if (i < snd_val.length() && snd_val[i] != '-') {
			result[i] += fromChar(snd_val[i]);
		}
		if (i < fst_val.length() && fst_val[i] != '-') {
			result[i] += fromChar(fst_val[i]);
		}
		result[i + 1] += result[i] / 10;
		result[i]     %= 10;
	}

	if (*result.rbegin() == 0) {
		result.pop_back();
	}

	if (is_neg_res) {
		result.push_back(fromChar('-'));
	}

	for (int front_i = 0, back_i = (int)result.length() - 1; front_i < result.length()/2 + result.length()%2; front_i++, back_i--) {
		char cache = toChar(result[back_i]);
		result[back_i] = toChar(result[front_i]);
		result[front_i] = cache;
	}

	return BigInt(result);
}

BigInt operator-(const BigInt& reduce, const BigInt& deduct) {
	std::string fst_val;
	std::string snd_val;

	if (reduce < (BigInt)0 && deduct < (BigInt)0) { //TODO: REWORK THIS IFs (substraction of two negatives [swap their positions like: -1 - -2 = 2 - 1])
		return -deduct - -reduce;
	}

	if (deduct < (BigInt)0) { //TODO: REWORK THIS IFs (addition of two possitives)
		return reduce + -deduct;
	}

	if (reduce < (BigInt)0) { //TODO: REWORK THIS IFs (addition of two negative)
		return reduce + -deduct;
	}

	bool is_neg_res = false;

	if (reduce < deduct) {
		is_neg_res = true;
		fst_val = deduct.data(); 
		snd_val = reduce.data();
	}
	else {
		fst_val = reduce.data();
		snd_val = deduct.data();
	}
	

	std::reverse(fst_val.begin(), fst_val.end()); //TODO: REMOVE REVERSE (TRY TO USE PURE DATA)
	std::reverse(snd_val.begin(), snd_val.end());

	std::string result(fst_val.length() + 1, 0);

	for (size_t i = 0; i < result.length(); i++) {
		if (i < fst_val.length() && fst_val[i] != '-') {
			result[i] += fromChar(fst_val[i]);
		}
		if (i < snd_val.length() && snd_val[i] != '-') {
			if (result[i] < fromChar(snd_val[i])) {
				result[i] += 10;
				result[i + 1] -= 1;
			}
			result[i] -= fromChar(snd_val[i]);
		}
		if (result[i] < 0) {
			result[i + 1] += result[i];
			result[i] += 10;
		}
	}

	while (result.rbegin() != result.rend() && *result.rbegin() == 0) {
		result.pop_back();
	}

	if (is_neg_res) {
		result.push_back(fromChar('-'));
	}

	for (int front_i = 0, back_i = (int)result.length() - 1; front_i < result.length() / 2 + result.length() % 2; front_i++, back_i--) {
		char cache = toChar(result[back_i]);
		result[back_i] = toChar(result[front_i]);
		result[front_i] = cache;
	}

	return BigInt(result);
}

/*Ｃｏｍｐａｒｉｓｏｎｓ*/

bool BigInt::operator==(const BigInt& num) const{
	return this->data() == num.data();
};
bool BigInt::operator!=(const BigInt& num) const{
	return this->data() != num.data();
};
bool BigInt::operator<(const BigInt& num) const{ //TODO: REWORK COMPARSIONS
	if ((is_neg() && num.is_neg()) || (!is_neg() && !num.is_neg())) {
		bool is_neg_oper = (is_neg() && num.is_neg());
		if (this->value.length() > num.value.length()) {
			return false + is_neg_oper;
		}
		else if (this->value.length() < num.value.length()) {
			return true - is_neg_oper;
		}
		else {
			return (this->data() < num.data()) - is_neg_oper;
		}
	}
	if (is_neg()) {
		return true;
	}
	return false;
};
bool BigInt::operator>(const BigInt& num) const{ //TODO: REWORK COMPARSIONS
	if (*this < num || *this == num) {
		return false;
	}
	return true;
};
bool BigInt::operator<=(const BigInt& num) const{
	if (*this < num || *this == num)
		return true;
	return false;
};
bool BigInt::operator>=(const BigInt& num) const{
	if (*this > num || *this == num)
		return true;
	return false;
};

std::string BigInt::data() const {
	if (value.size() > 0) {
		return (std::string(value));
	}
	else {
		return "0";
	}
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	for (auto elem : i.data()) {
		o << elem;
	}
	return o;
}

bool BigInt::is_neg() const {
	return (*this->data().begin() == '-');
}

//void BigInt::clear_value() {
//	delete value;
//}
