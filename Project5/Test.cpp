#define _CRT_SECURE_NO_WARNINGS

#include "BigInt.h"

#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

typedef BigInt B;

bool test_two(string expr) {
	cout << "TESTING this: " << expr;

	//
	char* pos = strtok((char*)expr.c_str(), " ");
	BigInt* a = new BigInt((string(pos)));
	pos = strtok(NULL, " ");
	char oper = *pos;
	pos = strtok(NULL, " ");
	BigInt* b = new BigInt((string(pos)));
	//

	bool is_correct = false;

	BigInt my_ans(0);
	long long correct_ans;

	switch (oper)
	{
	case('+'):
		correct_ans = (long long)*a + (long long)*b;
		my_ans = *a + *b;
		break;
	case('-'):
		correct_ans = (long long)*a - (long long)*b;
		my_ans = *a - *b;
		break;
	case('*'):
		correct_ans = (long long)*a * (long long)*b;
		my_ans = *a * *b;
		break;
	}

	is_correct = (BigInt)correct_ans == my_ans;
	cout << " = [" << my_ans << "] / {" << correct_ans << "} ";
	cout << (is_correct ? "CORRECT" : "!!WRONG!!");
	cout << endl;
	delete a;
	delete b;
	return is_correct;
}


int main() {

 
	srand(time(NULL));

	vector<char> oper_lst = {'+', '-', '*'};
	vector<int>  sign_list = { 1, -1 };

	bool is_correct = true;

	size_t test_num = 0;

#define RUN
#ifdef RUN
	do {
		cout << "(" << test_num << ") ";

		stringstream expr_s;

		int fst_num = ((int)rand()  + ((int)rand() << 16)) * (sign_list[rand() % 2]);
		int snd_num = ((int)rand()  + ((int)rand() << 16)) * (sign_list[rand() % 2]);

		char oper = oper_lst[rand() % oper_lst.size()];

		expr_s << fst_num << ' ' << oper << ' ' << snd_num;
		
		is_correct = test_two(expr_s.str());

		if (!is_correct) {
			getchar();

			is_correct = test_two(expr_s.str());

		}

		test_num++;

	} while (is_correct);
#endif


	return 0;
}