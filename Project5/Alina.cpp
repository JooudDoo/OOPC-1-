#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <bitset>
#include <malloc.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream> // string stream 
#include "BigInt.h"

int main1(){
	//---INC and DEC---//
	std::cout << "------INC and DEC-------- " << '\n';

	BigInt inc0(0), inc1("8999999999999999"), dec0("5000000000000000"), dec1(-3001), di(-432);

	std::cout << "++0: " << ++inc0 << '\n';
	std::cout << "8999999999999999++: " << inc1++ << '\n';
	std::cout << "--1: " << --inc0 << '\n';
	std::cout << "5000000000000000--: " << dec0-- << '\n';
	std::cout << "++(-3001): " << ++dec1 << '\n';
	std::cout << "++(--(-432)): " << ++(--di) << '\n';


	//---SUM and SUB---//
	std::cout << "------SUM and SUB-------- " << '\n';

	BigInt a("10000000000"), b("-10000000001"), c(0), d(5), e(-9);

	a += b;
	std::cout << "10000000000 +=  -10000000001: " << a << '\n';
	
	a -= b;
	std::cout << "-1 -=  -10000000001: " << a << '\n';

	a += c;
	std::cout << "10000000000 +=  0: " << a << '\n';
	
	a -= c;
	std::cout << "10000000000 -=  0: " << a << '\n';

	a += d;
	std::cout << "10000000000 +=  5: " << a << '\n';

	a -= d;
	std::cout << "10000000005 -=  5: " << a << '\n';

	b += a;
	std::cout << "-10000000001 +=  10000000000: " << b << '\n';
	
	b -= a;
	std::cout << "-1 -=  10000000000: " << b << '\n';

	b += e;
	std::cout << "-1000000001 +=  -9: " << b << '\n';
	
	b -= e;
	std::cout << "-1000000010 -=  -9: " << b << '\n';

	c += e;
	std::cout << "0 +=  -9: " << c << '\n';
	
	c -= e;
	std::cout << "-9 -=  -9: " << c << '\n';

	//---MULT and DIV---//
	std::cout << "------MULT and DIV-------- " << '\n';

	BigInt z(0), f("1"), ll("-666666666666666666"), n(-5555), dd(1000000), y(-2);

	z *= n;
	std::cout << "0 *=  -5555: " << z << '\n';

	f *= n;
	std::cout << "1 *=  -5555: " << f << '\n';


	ll *= dd;
	std::cout << "-666666666666666666 *= 1000000: " << ll << '\n';

	ll /= dd;
	std::cout << "-666666666666666666000000 /= 1000000: " << ll << '\n';

	n /= ll;
	std::cout << "-5555 /= -666666666666666666: " << n << '\n';

	dd /= y;
	std::cout << "1000000 /= -2: " << dd << '\n';

	//---POWER---//
	std::cout << "------POWER-------- " << '\n';
	BigInt p1(-2), p2(2), p3(101), p4(3), p5(0), p6(-109), p7(1), res;
	res = p1 ^ p2;
	std::cout << "-2 ^= 2 : "  << res << '\n';

	res = p3 ^ p4;
	std::cout << "101 ^= 3 : "  << res << '\n';

	res = p4 ^ p5;
	std::cout << "3 ^= 0 : "  << res  << '\n';

	res = p6 ^ BigInt(10);
	std::cout << "-109 ^= 10 : "  << res << '\n';

	res = p1 ^ p7;
	std::cout << "-2 ^= 1 : " << res << '\n';

	res = p5 ^ p3;
	std::cout << "0 ^= 101 : " << res << '\n';


	//---LOGIC---//
	std::cout << "------LOGIC-------- " << '\n';
	std::cout << "BigInt(5) | BigInt(2):" << (BigInt(5) | BigInt(2)) << std::endl;
	std::cout << "BigInt(4747474747474747) | BigInt(-959595):" << (BigInt("4747474747474747") | BigInt(-959595)) << std::endl;
	std::cout << "BigInt(6) & BigInt(2):" << (BigInt(6) & BigInt(2)) << std::endl;

	//---UNARY---//
	std::cout << "------UNARY-------- " << '\n';
	std::cout << "-(BigInt(-5)):" << -BigInt(-5) << std::endl;
	std::cout << "-(-(+BigInt(47474))):" << -(-(+BigInt("47474"))) << std::endl;
	std::cout << "-(-(+(-BigInt(6)))):" <<-(-(+(-BigInt(6)))) << std::endl;


	//---BOOL OPERATIONS---//
	std::cout << "------BOOL OPERATIONS-------- " << '\n';

	bool t = BigInt(532232) > BigInt(103);
	std::cout << "532232 > 103 : ";
	std::cout << t << '\n';
	
	t = BigInt("-38474586858585") > BigInt(103);
	std::cout << "-38474586858585 > 103 : ";
	std::cout << t << '\n';

	t = BigInt(-532232) <= BigInt(-103);
	std::cout << "-532232 <= -103 : ";
	std::cout << t << '\n';

	t = BigInt(-0) >= BigInt(0);
	std::cout << "-0 >= 0 : ";
	std::cout << t << '\n';

	t = BigInt(532232) != BigInt(-532232);
	std::cout << "532232 != -532232 : ";
	std::cout << t << '\n';

	t = BigInt("5747474747532232") == BigInt("5747474747532232");
	std::cout << "5747474747532232 == 5747474747532232 : ";
	std::cout << t << '\n';

	//---FROM BIGINT---//
	std::cout << "------FROM BIGINT-------- " << '\n';
	BigInt toi1(39392), toi2("-723728"), tos1(-328233333), tos2("88888888888888888");

	std::cout << "BigInt(39392) to int: " << int(toi1) << '\n';
	std::cout << "BigInt(-723728) to int: " << int(toi2) << '\n';
	std::cout << "BigInt(-328233333) to str: " << std::string(tos1) << '\n';
	std::cout << "BigInt(88888888888888888) to str: " << std::string(tos2) << '\n';

	//---SIZE()---//
	std::cout << "------SIZE()-------- " << '\n';
	std::cout << "BigInt(39392) size: " << toi1.size() << '\n';
	std::cout << "BigInt(-723728) size: " << toi2.size() << '\n';
	std::cout << "BigInt(-328233333) size: " << tos1.size() << '\n';
	std::cout << "BigInt(88888888888888888) size: " << tos2.size() << '\n';

	return 0;
}