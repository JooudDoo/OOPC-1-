#pragma once

#include<iostream>


class BigInt {
	friend BigInt operator+(const BigInt&, const BigInt&);
	friend BigInt operator-(const BigInt&, const BigInt&);
	friend BigInt operator*(const BigInt&, const BigInt&);
	friend BigInt operator/(const BigInt&, const BigInt&);
	friend BigInt operator%(const BigInt&, const BigInt&);
	friend BigInt operator|(const BigInt&, const BigInt&);
	friend BigInt operator&(const BigInt&, const BigInt&);
	friend BigInt operator^(const BigInt&, const BigInt&);

	friend BigInt div_two_nums(const BigInt&, const BigInt&, const bool, const bool, BigInt*);
public:
	class BigBin;
	BigInt();
	BigInt(int);
	BigInt(long long);
	BigInt(std::string); // ??????? ?????????? std::invalid_argument ??? ??????
	BigInt(const BigInt&);
	BigInt(const BigBin&);
	~BigInt();

	BigBin binary();

	BigInt& operator=(const BigInt&);  //???????? ???????????? ?????? ????!

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

	class BigBin {
		friend BigInt::BigBin operator|(const BigInt::BigBin&, const BigInt::BigBin&);
		friend BigInt::BigBin operator&(const BigInt::BigBin&, const BigInt::BigBin&);
		friend BigInt::BigBin operator^(const BigInt::BigBin&, const BigInt::BigBin&);
	public:
		BigBin();
		BigBin(const BigInt&);
		~BigBin() = default;

		bool is_neg() const;
		std::string data() const;
	private:
		void insert(const BigInt&);
		int len() const;
		bool is_zero() const;

		bool _is_neg;
		std::string value;
	};

private:

	//inserts string value into end of the num
	void insert(const std::string&);
	void insert(const char&);
	void insert(const int&);

	bool is_zero() const;
	bool is_neg() const;
	
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

BigInt::BigBin operator|(const BigInt::BigBin&, const BigInt::BigBin&);
BigInt::BigBin operator&(const BigInt::BigBin&, const BigInt::BigBin&);
BigInt::BigBin operator^(const BigInt::BigBin&, const BigInt::BigBin&);

std::ostream& operator<<(std::ostream& o, const BigInt& i);