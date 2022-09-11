#define _CRT_SECURE_NO_WARNINGS
#include "BigInt.h"

#include <iostream>
#include <vector>
#include <sstream>
#include<Windows.h>

using namespace std;

constexpr int CNT_OF_REPEATS_BENCHMARKING = 50000;
constexpr int CNT_OF_ONE_BLOCK_BENCHMARKING = 1000;

//Available operations { '+', '-', '*', '/', '%' }
constexpr char oper_lst[] = { '+', '-', '*', '/', '%' };
//Available signs { 1, -1};
constexpr int sign_list[] = {1, -1};

#define CALCULATE

#ifdef CALCULATE
#define TEST_RUN
#include <sys/timeb.h>
typedef _timeb sys_time_t;
inline long long time_to_msec(const sys_time_t& t) {
	return t.time * 1000LL + t.millitm;
}

sys_time_t T_st, T_end;
vector<long long> timers;
#define runTIMED(a) {_ftime(&T_st); \
					a;\
					_ftime(&T_end);\
					timers.push_back(time_to_msec(T_end) - time_to_msec(T_st)); }

#endif


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
		break;
	case('%'):
		correct_ans = (long long)*a % (long long)*b;
		my_ans = *a % *b;
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

	if (CNT_OF_ONE_BLOCK_BENCHMARKING > CNT_OF_REPEATS_BENCHMARKING) {
		throw invalid_argument("WRONG ATRIBUTES");
	}

	srand(time(NULL));

	bool is_correct = true;

	size_t test_num = 0;

#ifdef TEST_RUN
	do {
		runTIMED(
			for (size_t block_num = 0; block_num <= CNT_OF_ONE_BLOCK_BENCHMARKING && is_correct; block_num++) {
				if (test_num == CNT_OF_REPEATS_BENCHMARKING) {
					is_correct = false;
					break;
				}

				cout << "(" << test_num << ") ";

				stringstream expr_s;

				char oper = oper_lst[rand() % (sizeof(oper_lst) / sizeof(*oper_lst))];

				int fst_num = ((int)rand() + ((int)rand() << 16)) * (sign_list[rand() % (sizeof(sign_list) / sizeof(*sign_list))]);
				int snd_num = ((int)rand() + 1  /*+ ((int)rand() << 16)*/) * (sign_list[rand() % (sizeof(sign_list) / sizeof(*sign_list))]);

				expr_s << fst_num << ' ' << oper << ' ' << snd_num;

				is_correct = test_two(expr_s.str());

				test_num++;
			});

	} while (is_correct);

#ifdef CALCULATE

	WORD total_time = 0;
	for (auto i : timers) {
		total_time += i;
	}

	//Mixed (pos/neg)
	//24277ms total work time(50000 operations)
	//485ms(1000 operations)
	//0ms on 1 operations

	//Add (only positive)
	//35048ms total work time(50000 operations)
	//700ms(1000 operations)
	//0ms on 1 operations

	//Sub (only positive)
	//35200ms total work time(50000 operations)
	//704ms(1000 operations)
	//0ms on 1 operations

	//Multiplication (pos/neg)
	//61413ms total work time(50000 operations)
	//1228ms(1000 operations)
	//1ms on 1 operations

	//Division (pos/neg)
	//16941ms total work time(50000 operations)
	//338ms(1000 operations)
	//0ms on 1 operations

	//Mod (pos/neg)
	//11526ms total work time(50000 operations)
	//230ms(1000 operations)
	//0ms on 1 operations

	cout << total_time << "ms total work time (" << CNT_OF_REPEATS_BENCHMARKING << " operations)" << endl;
	cout << total_time / timers.size() << "ms (" << CNT_OF_ONE_BLOCK_BENCHMARKING << " operations)" << endl;
	cout << total_time / timers.size() / CNT_OF_ONE_BLOCK_BENCHMARKING << "ms on 1 operations" << endl;
#endif

#endif


	return 0;
}