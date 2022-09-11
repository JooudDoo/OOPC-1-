#include "BigInt.h"
#include <utility>
#include <sstream>

constexpr int fromChar(char a) { return a - '0'; }
constexpr char toChar(int a) { return a + '0'; }
constexpr int BUFFER_STANDART_SIZE = 256;

/// <summary>
/// Adds two strings as numbers and returns result as string with number
/// </summary>
/// <param name="fst_val"> - first num</param>
/// <param name="snd_val"> - second num</param>
/// <returns>sum of two nums</returns>
std::string add_two_nums(const std::string&, const std::string&, const bool);
/// <summary>
/// Subs two strings as numbers and returns result as string with number
/// </summary>
/// <param name="fst_val"> - first num</param>
/// <param name="snd_val"> - second num</param>
/// <returns>sub of two nums</returns>
std::string sub_two_nums(const std::string&, const std::string&, const bool);

void to_char_reverse(std::string&);

/*Ｃｏｎｓｔｒｕｃｔｏｒｓ*/

BigInt::BigInt() {
	BigInt::value = std::string("0");
};

BigInt::BigInt(int num) {
	std::stringstream num_s;
	num_s << num;
	BigInt::value = num_s.str();
}

BigInt::BigInt(long long num) {
	std::stringstream num_s;
	num_s << num;
	BigInt::value = num_s.str();
}

BigInt::BigInt(std::string num) {
	if (num.length() == 0) {
		BigInt::value = "0";
		return;
	}
	std::string::iterator elem = num.begin();
	if (*elem == '-' || *elem == '+') {
		elem++;
		if (*(elem - 1) == '+') {
			num.erase(num.begin());
			elem--;
		}
	}
	for (elem; elem != num.end(); elem++) {
		if ((*elem < '0' || *elem > '9')) {
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

BigInt& BigInt::operator=(const BigInt& new_value) {
	this->value = new_value.data();
	return *this;
}

/*Ｏｐｅｒａｔｉｏｎｓ*/

BigInt& BigInt::operator++() {
	*this = *this + BigInt{ 1 };
	return *this;
}

const BigInt BigInt::operator++(int) const {
	return (*this) + BigInt{ 1 };
}

BigInt& BigInt::operator--() {
	*this = *this - BigInt{ 1 };
	return *this;
}

const BigInt BigInt::operator--(int) const {
	return (*this) - BigInt{ 1 };
}

BigInt& BigInt::operator+=(const BigInt& num) {
	*this = *this + num;
	return *this;
}

BigInt& BigInt::operator-=(const BigInt& num) {
	*this = *this - num;
	return *this;
}

BigInt& BigInt::operator*=(const BigInt& num) {
	*this = *this * num;
	return *this;
}

BigInt& BigInt::operator/=(const BigInt& num) {
	*this = *this / num;
	return *this;
}

BigInt abs(const BigInt& num) {
	if (num.data()[0] == '-') {
		BigInt newNum = BigInt(num.data().erase(0, 1));
		return newNum;
	}
	return num;
}

BigInt BigInt::operator+() const {
	return *this;
}

BigInt BigInt::operator-() const {
	if (this->is_neg())
		return abs(*this);
	return this->data().insert(0, "-");
}

std::string add_two_nums(const std::string& fst_val, const std::string& snd_val, const bool is_neg = false) {
	std::string result(std::max(fst_val.size(), snd_val.size()) + 1, 0);

	for (int i = 0, fst_c = fst_val.size() - 1, snd_c = snd_val.size() - 1;
		i < result.length();
		i++, fst_c--, snd_c--) {
		if (snd_c >= 0 && snd_val[snd_c] != '-') {
			result[i] += fromChar(snd_val[snd_c]);
		}
		if (fst_c >= 0 && fst_val[fst_c] != '-') {
			result[i] += fromChar(fst_val[fst_c]);
		}
		result[i + 1] += result[i] / 10;
		result[i] %= 10;
	}

	while (result.rbegin() != result.rend() && *result.rbegin() == 0) {
		result.pop_back();
	}

	if (is_neg) {
		result.push_back(fromChar('-'));
	}

	to_char_reverse(result);

	return result;
}

std::string sub_two_nums(const std::string& fst_val, const std::string& snd_val, const bool is_neg = false) {

	std::string result(std::max(fst_val.size(), snd_val.size()) + 1, 0);

	for (int i = 0, fst_c = fst_val.size() - 1, snd_c = snd_val.size() - 1;
		i < result.length();
		i++, fst_c--, snd_c--) {
		if (fst_c >= 0 && fst_val[fst_c] != '-') {
			result[i] += fromChar(fst_val[fst_c]);
		}
		if (snd_c >= 0 && snd_val[snd_c] != '-') {
			if (result[i] < fromChar(snd_val[snd_c])) {
				result[i] += 10;
				result[i + 1] -= 1;
			}
			result[i] -= fromChar(snd_val[snd_c]);
		}
		if (result[i] < 0) {
			result[i + 1] += result[i];
			result[i] += 10;
		}
	}

	while (result.rbegin() != result.rend() && *result.rbegin() == 0) {
		result.pop_back();
	}

	if (is_neg) {
		result.push_back(fromChar('-'));
	}

	to_char_reverse(result);

	return result;
}

void to_char_reverse(std::string& num) {

	for (int front_i = 0, back_i = (int)num.length() - 1;
		front_i < num.length() / 2 + num.length() % 2;
		front_i++, back_i--) {
		char cache = toChar(num[back_i]);
		num[back_i] = toChar(num[front_i]);
		num[front_i] = cache;
	}

}

BigInt operator+(const BigInt& first, const BigInt& second) {
	bool is_neg_res = false;

	if (first.is_neg() && second.is_neg()) {
		is_neg_res = true;
	}
	else if (first.is_neg()) {
		return second - -first;
	}
	else if (second.is_neg()) {
		return first - -second;
	}

	std::string result = add_two_nums(first.data(), second.data(), is_neg_res);

	return BigInt{ result };
}

BigInt operator-(const BigInt& reduce, const BigInt& deduct) {
	std::string fst_val;
	std::string snd_val;

	if (reduce.is_neg() && deduct.is_neg()) { //(substraction of two negatives [swap their positions like: -1 - -2 = 2 - 1])
		return -deduct - -reduce;
	}

	if (deduct.is_neg()) { //(addition of two possitives)
		return reduce + -deduct;
	}

	if (reduce.is_neg()) { //(addition of two negative)
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

	std::string result = sub_two_nums(fst_val, snd_val, is_neg_res);

	return BigInt{ result };
}

BigInt operator*(const BigInt& first, const BigInt& second) {
	std::string fst_val = first.data();
	std::string snd_val = second.data();

	bool is_neg_res = false;

	if (first.is_neg() && second.is_neg()) {
		is_neg_res = false;
	}
	else if (first.is_neg() || second.is_neg()) {
		is_neg_res = true;
	}

	size_t max_lenght = fst_val.size() + snd_val.size();

	std::string result(max_lenght, '0');
	size_t shift = 1;

	using revS = std::string::reverse_iterator;

	for (revS fst = fst_val.rbegin(); fst != fst_val.rend() && *fst != '-'; fst++) {
		std::string temp(max_lenght, '0');
		size_t temp_c = max_lenght - shift;
		for (revS snd = snd_val.rbegin(); snd != snd_val.rend() && *snd != '-'; snd++) {
			temp[temp_c] = fromChar(temp[temp_c]) + fromChar(*snd) * fromChar(*fst);
			temp[temp_c - 1] = toChar(temp[temp_c] / 10);
			temp[temp_c] = toChar(temp[temp_c] % 10);
			temp_c--;
		}
		result = add_two_nums(result, temp);
		shift += 1;
	}

	std::string::iterator result_c = result.begin(); //TODO : MAKE UNITE REMOVE LEADING ZERO ALGO
	while (result_c != result.end() && *result_c == '0') {
		result_c++;
	}
	result.erase(result.begin(), result_c);

	if (is_neg_res) {
		return -BigInt{ result };
	}
	return BigInt{ result };
}

BigInt operator/(const BigInt& divisible_raw, const BigInt& divider_raw) {
	if (divider_raw.is_zero()) {
		throw std::invalid_argument("division on zero");
	}
	if (abs(divisible_raw) < abs(divider_raw)) {
		return BigInt{ 0 };
	}
	if (divisible_raw == divider_raw) {
		return BigInt{ 1 };
	}

	BigInt inter_divisible, inter_divider, result;

	bool is_neg_res = false;

	if (divisible_raw.is_neg() && divider_raw.is_neg()) {
		is_neg_res = false;
	}
	else if (divisible_raw.is_neg() || divider_raw.is_neg()) {
		is_neg_res = true;
	}

	BigInt divisible = abs(divisible_raw), divider = abs(divider_raw);

	size_t divisible_c = 0;
	bool one_loop_complete = false;
	while (divisible_c < divisible.size()) {
		inter_divider = divider;
		for (divisible_c; divisible_c < divisible.size(); divisible_c++) {
			inter_divisible.insert(divisible.data()[divisible_c]);
			if (inter_divisible >= inter_divider) {
				divisible_c++;
				break;
			}
			if (one_loop_complete) {
				result.insert('0');
			}
		}

		if (inter_divider > inter_divisible) {
			break;
		}

		int oper_cnt = 1;
		while (inter_divisible >= inter_divider + divider) {
			inter_divider += divider;
			oper_cnt++;
		}

		one_loop_complete = true;
		inter_divisible -= inter_divider;
		result.insert(oper_cnt);
	}

	if (is_neg_res)
		return -result;
	return result;
}

/*Ｃｏｍｐａｒｉｓｏｎｓ*/

bool BigInt::operator==(const BigInt& num) const {
	return this->data() == num.data();
};
bool BigInt::operator!=(const BigInt& num) const {
	return this->data() != num.data();
};
bool BigInt::operator<(const BigInt& num) const { //TODO: REWORK COMPARSIONS
	if ((is_neg() && num.is_neg()) || (!is_neg() && !num.is_neg())) {
		bool is_neg_oper = (is_neg() && num.is_neg());
		if (this->value.length() > num.value.length()) {
			return false + is_neg_oper;
		}
		else if (this->value.length() < num.value.length()) {
			return true - is_neg_oper;
		}
		else {
			return (abs(*this).data() < abs(num).data()) - is_neg_oper;
		}
	}
	if (is_neg()) {
		return true;
	}
	return false;
};
bool BigInt::operator>(const BigInt& num) const { //TODO: REWORK COMPARSIONS
	if (*this < num || *this == num) {
		return false;
	}
	return true;
};
bool BigInt::operator<=(const BigInt& num) const {
	if (*this < num || *this == num)
		return true;
	return false;
};
bool BigInt::operator>=(const BigInt& num) const {
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

size_t BigInt::size() const {
	return value.size();
}

std::ostream& operator<<(std::ostream& o, const BigInt& i) {
	for (char elem : i.data()) {
		o << elem;
	}
	return o;
}

void BigInt::insert(const std::string& val) {
	if (this->is_zero())
		value = val;
	else
		value += val;
}

void BigInt::insert(const char& val) {
	if (this->is_zero())
		value = val;
	else
		value += val;
}

void BigInt::insert(const int& val) {
	std::stringstream o;
	o << val;
	if (this->is_zero())
		value = o.str();
	else
		value += o.str();

}

bool BigInt::is_zero() const {
	if (value.length() == 1 && value[0] == '0')
		return true;
	return false;
}

bool BigInt::is_neg() const {
	return (*value.begin() == '-');
}

//void BigInt::clear_value() {
//	delete value;
//}