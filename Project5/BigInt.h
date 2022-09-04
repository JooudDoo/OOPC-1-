#pragma once

#include<iostream>
class BigInt {
public:
	BigInt();
	BigInt(int);
	BigInt(std::string); // бросать исключение std::invalid_argument при ошибке
	BigInt(const BigInt&);
	~BigInt();

	BigInt& operator=(const BigInt&);  //возможно присваивание самому себе!

	BigInt operator~() const; //??

	BigInt& operator++();
	const BigInt operator++(int) const;
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
	std::string reverse_value(std::string);
	
	std::string* value;
};

BigInt operator+(const BigInt&, const BigInt&);
