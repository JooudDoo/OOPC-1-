#pragma once

#include<iostream>
class BigInt {
	friend BigInt operator+(const BigInt&, const BigInt&);
	friend BigInt operator-(const BigInt&, const BigInt&);
	friend BigInt operator*(const BigInt&, const BigInt&);
	friend BigInt operator/(const BigInt&, const BigInt&);
	friend BigInt operator%(const BigInt&, const BigInt&);
	friend BigInt operator^(const BigInt&, const BigInt&);

	friend BigInt div_two_nums(const BigInt&, const BigInt&, const bool, const bool, BigInt*);

public:
	BigInt();
	BigInt(int);
	BigInt(long long);
	BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt&);
	BigInt(const BigBin&);
	~BigInt();

	BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

	BigInt operator~() const; //??

	BigInt& operator++(); //PreIncrement (Increase our value in memory, return x+1)
	const BigInt operator++(int) const; //PostIncrement (Does not increase our value in memory, return x+1)
	BigInt& operator--();
	const BigInt operator--(int) const;

	BigInt& operator+=(const BigInt&);
	BigInt& operator*=(const BigInt&);
	BigInt& operator-=(const BigInt&);
	BigInt& operator/=(const BigInt&);
	BigInt& operator^=(const BigInt&);
	BigInt& operator%=(const BigInt&);
	BigInt& operator&=(const BigInt&);
	BigInt& operator|=(const BigInt&);

	BigInt operator+() const;  // unary +
	BigInt operator-() const;  // unary -

	bool operator==(const BigInt&) const;
	bool operator!=(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator<=(const BigInt&) const;
	bool operator>=(const BigInt&) const;

	operator int() const;
	operator std::string() const;

	std::string data() const;
	size_t size() const;  // size in bytes
private:

	void clear_value();
	//inserts string value into end of the num
	void insert(const std::string&); //TODO : Make template for several types (?) [Unite this two functions in one]
	void insert(const char&); //TODO : REWORK THIS OPERATIONS (REMOVE COPY/PASTE)
	void insert(const int&);

	bool is_zero() const;
	bool is_neg() const;
	
	std::string value;
};

class BigBin {

public:
	BigBin(BigInt&);
	~BigBin() = default;

private:
	void insert(const BigInt&);

	std::string value;
};

BigInt abs(const BigInt&);

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
BigInt operator*(const BigInt&, const BigInt&);
BigInt operator/(const BigInt&, const BigInt&);
BigInt operator^(const BigInt&, const BigInt&);
BigInt operator%(const BigInt&, const BigInt&);
BigInt operator&(const BigInt&, const BigInt&);
BigInt operator|(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);