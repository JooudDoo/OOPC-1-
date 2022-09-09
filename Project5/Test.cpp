#define _CRT_SECURE_NO_WARNINGS

#include "BigInt.h"

#include <iostream>
#include <vector>
#include <sstream>
#include<Windows.h>

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

	BigInt my_ans{0};
	long long correct_ans{0};

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
	case('/'):
		correct_ans = (long long)*a / (long long)*b;
		my_ans = *a / *b;
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

	vector<char> oper_lst = {'+', '-', '*', '/'};
	vector<int>  sign_list = { 1, -1 };

	bool is_correct = true;

	size_t test_num = 0;

#define CALCULATE
#ifdef CALCULATE
	SYSTEMTIME st, old;
	GetSystemTime(&st);

	vector<WORD> timers;
#endif

#define RUN
#ifdef RUN
	do {
#ifdef CALCULATE
		if (test_num % 1000 == 0) {
			GetSystemTime(&old);
			timers.push_back(st.wSecond*1000 + st.wMilliseconds - old.wMilliseconds - old.wSecond * 1000);
			st = old;
		}
		if (test_num == 10000) {
			break;
		}
#endif

		cout << "(" << test_num << ") ";

		stringstream expr_s;

		int fst_num = ((int)rand()  + ((int)rand() << 16)) * (sign_list[rand() % 2]);
		int snd_num = ((int)rand()  /*+ ((int)rand() << 16)*/) * (sign_list[rand() % 2]);

		char oper = '/';
		//char oper = oper_lst[rand() % oper_lst.size()];

		expr_s << fst_num << ' ' << oper << ' ' << snd_num;
		
		is_correct = test_two(expr_s.str());

		if (!is_correct) {
			getchar();
			is_correct = test_two(expr_s.str());
		}

		test_num++;

	} while (is_correct);

#ifdef CALCULATE

	WORD total_time = 0;
	for (auto i : timers) {
		total_time += i;
	}

	//Add (only positive)
	//38182ms total work time(10000 opers)
	//3471ms on 1000 opers
	//3ms on 1 oper

	//Sub (only positive)
	//38707ms total work time(10000 opers)
	//3518ms on 1000 opers
	//3ms on 1 oper

	//Multiplication (pos/neg)
	//28195ms total work time(10000 opers)
	//2563ms on 1000 opers
	//2ms on 1 oper

	//Division (pos/neg)
	//48117ms total work time(10000 opers)
	//4374ms on 1000 opers
	//4ms on 1 oper

	cout << total_time << "ms total work time (10000 opers)" << endl;
	cout << total_time / timers.size() << "ms on 1000 opers" << endl;
	cout << total_time / timers.size() / 1000 << "ms on 1 oper" << endl;
#endif

#endif


	return 0;
}